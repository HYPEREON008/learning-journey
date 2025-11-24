#include <Arduino.h>

int ledPin = 25;
int buttonPin = 2;
int ledState = HIGH;
int potPin = 34;
int brightness = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(potPin, INPUT);
}

void loop() {
  brightness = analogRead(potPin)/16;  //map 0-4095 to 0-255 for analog write

  if (digitalRead(buttonPin)==LOW) { //when button pressed connected gnd overrides pullup resistor
    ledState = !ledState;
  }
  if (ledState==LOW) {
    brightness = 0;
  }
  analogWrite(ledPin,brightness);

  while (digitalRead(buttonPin)==LOW) {
    delay(30);
  }
  delay(10);
}
