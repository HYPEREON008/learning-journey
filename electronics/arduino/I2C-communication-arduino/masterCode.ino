#include <Wire.h>

int potPin = A3;       // Analog pin A3
int potValue = 0;

void setup() {
  Wire.begin();          // join I2C bus as master
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  potValue = analogRead(potPin);
  
  byte dataToSend = (byte)(potValue/4);
  //integer division truncates decimals back to int
  Serial.println("Master sending data...");
  
  Wire.beginTransmission(8);  // address of slave
  Wire.write(dataToSend);
  Wire.endTransmission();

  delay(50);
}