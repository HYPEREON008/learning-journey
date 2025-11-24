
const int trigPin = 3; //trigger pin
const int echoPin = 2; //echo pin

const int enPin = 9;   // (with PWM) enable pin on L293D
const int in1Pin = 8;  // input 1 to rotate in one direction
const int in2Pin = 7;  // input 2 to rotate in opposite direction

unsigned long lastTime = 0; //last time when the loop run and actuating signal was passed
const float target_CM = 100.0; //target var(commanded)
const float LOOP_INTERVAL = 80.0; //loop time

//constants to be configured with testing
float Kp = 2.0;
float Ki = 0.05;
float Kd = 0.4;

float integration = 0.0; //integration of e(t) (error) wrt t from t=0 to current time
float lastError = 0.0; //needed when calculating derivative of e(t) wrt t

const float integration_max = 1000.0; //in case it accumulates excessive error...it would affect the overall controller a lot more than we want
//reduce the effectiveness of P and D terms
const float integration_min = -1000.0;
const float pwm_max = 220; //safety cap 
const int DEADZONE = 3;     // small control(output) zone = motor OFF




void setup()
{

  Serial.begin(9600); //sets baud(symbol changes per sec(~bps))
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(enPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  //motor off
  analogWrite(enPin, 0); //disable at start
  Serial.println("Distance control starts...");
}

float readDistance() {
  // send 10us pulse
  digitalWrite(trigPin, LOW); //start with trigger off
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); //keep trigger pin on for 10us initiates the distance measuement process
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 30000UL); //the echo pin is set to HIGH it then waits for the echo of the light wave and when it receives it the pin is set back to LOW
  //the duration for which it was HIGH is measured with pulseIn (30ms timeout in case no echo received) 30000us
  if (duration == 0) {
    return -1; //invalid
  }
  return duration/58.0; //distance in cm(from speed of light)
}

void setMotor(float control) {
  //deadzone to turn off motor when control output is tiny
  if (abs(control)<DEADZONE) {
    analogWrite(enPin,0);
    digitalWrite(in1Pin,LOW);
    digitalWrite(in2Pin,LOW);
    return;
  }
  int pwm = constrain(fabs(control), 0, pwm_max);

  if (control > 0) {
    //robot is too far so move fwd (behind required zone)
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
    analogWrite(enPin, pwm);
  
  }
  else {
    //robot is too close so move bck (crossed required zone)
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    analogWrite(enPin, pwm);
  }
}

void loop() {
  unsigned long now = millis();
  if ((now - lastTime)<LOOP_INTERVAL) { //not yet time
    return;
  }
  float dt = (now-lastTime)/1000.0; //convert to seconds
  if (dt > 1.0){
    dt = 1.0; // safety clamp to 1s if loop by chance skips
  }
  lastTime = now;
  
  //read the distance
  float distance = readDistance();
  if (distance < 0) {
    Serial.println("no distance reading");
    setMotor(0);
    return;

  }
  //proper case
  //compute error
  float error = distance-target_CM;

  //update integral term
  integration += error*dt;
  integration = constrain(integration, integration_min, integration_max);

  //calculate derivative
  float derivative = (error-lastError)/dt;

  //compute total pid control output
  float output = Kp*error + Ki*integration + Kd*derivative;
  lastError = error;
  
  //print info
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Error: ");
  Serial.print(error);
  Serial.print(" cm | Control: ");
  Serial.println(output);

  //apply motor Command
  setMotor(output);
}
