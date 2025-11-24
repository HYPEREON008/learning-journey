const int trigPin = 3; //trigger pin
const int echoPin = 2; //echo pin

const int enPin = 9;   // (with PWM) enable pin on L293D
const int in1Pin = 8;  // input 1 to rotate in one direction
const int in2Pin = 7;  // input 2 to rotate in opposite direction

const float TARGET_CM = 100.0;

const int PWM_FORWARD = 200; // 0-255. Adjust to give desired "positive RPM"
const int PWM_REVERSE = 200; // magnitude for reverse (same magnitude but opposite direction)
const int LOOP_INTERVAL = 80; // delay between measurements (ms)

void setup() {
  Serial.begin(9600); //sets baud(symbol changes per sec(~bps))
  //setup all pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(enPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);

  // motor off
  analogWrite(enPin, 0);
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);

  Serial.println("One-wheel standoff - bang-bang control");
}

float readDistanceCM() {
  // send 10us pulse
  digitalWrite(trigPin, LOW); //start with trigger off
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //keep trigger pin on for 10us initiates the distance measuement process
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 30000UL); //the echo pin is set to HIGH it then waits for the echo of the light wave and when it receives it the pin is set back to LOW
  //the duration for which it was HIGH is measured with pulseIn (30ms timeout in case no echo received)
  if (duration == 0) {
    // no echo received (out of range or timeout)
    return -1.0; // indicate invalid
  }
  // distance in cm = duration / 58.0 (approx)(from speed of light)
  float dist = duration / 58.0;
  return dist;
}

void setMotorForward(int pwm) {
  //robot is too far so move fwd (behind required zone)
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  analogWrite(enPin, constrain(pwm, 0, 255));
}

void setMotorReverse(int pwm) {
  //robot is too close so move bck (crossed required zone)
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  analogWrite(enPin, constrain(pwm, 0, 255));
}

void stopMotor() {
  //when exactly at correct distance(say somehow happens) or error is distance measurement
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  analogWrite(enPin, 0);
}

void loop() {
  float d = readDistanceCM();
  if (d < 0) {
    Serial.println("Distance: out of range");
  }
  else {
    Serial.print("Distance (cm): ");
    Serial.println(d, 2);
  }



  if (d < 0) {
    // sensor error: stop for safety
    stopMotor();
  }
    // If distance > 100 => constant positive RPM (forward)
  else if (d > TARGET_CM) {
    setMotorForward(PWM_FORWARD);
  }
    // If distance < 100 => constant negative RPM (reverse)
  else if (d < TARGET_CM) {
    setMotorReverse(PWM_REVERSE);
  } 
  else {
    // exactly equal - not likely; keep stopped
    stopMotor();
  }

  delay(LOOP_INTERVAL);
}