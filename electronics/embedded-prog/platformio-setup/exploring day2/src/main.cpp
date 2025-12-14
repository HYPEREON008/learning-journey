#include <Arduino.h>
int pin = 37;
void setup() {
    Serial.begin(115200);
    Serial.println("Hello, Arduino!");
    pinMode(pin, OUTPUT);
}
void loop() {
    // put your main code here, to run repeatedly:
    digitalWrite(pin, HIGH);
    delay(50);
    digitalWrite(pin, LOW);
    delay(50);
}
