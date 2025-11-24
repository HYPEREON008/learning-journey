#include <Wire.h>

byte receivedData = 0;
int brightness = 0;
int ledPin = 10;

void setup() {
  Wire.begin(8);  // join I2C bus with address #8
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("Slave ready");
}

void loop() {
  delay(50);
}

void receiveEvent(int bytes) {
  if (Wire.available()) {
    receivedData = Wire.read();
    Serial.print("Received from master: ");
    Serial.println(receivedData);
    brightness = receivedData;
  	analogWrite(ledPin, brightness);
  }
}
