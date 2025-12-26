#include <Arduino.h>
const int a = 22, b = 23, c = 17, d = 5, e = 18, f = 21, g = 19;
int Pins[] = {a, b, c, d, e, f, g};
int digit0[] = {1, 1, 1, 1, 1, 1, 0};
int digit1[] = {0, 1, 1, 0, 0, 0, 0};
int digit2[] = {1, 1, 0, 1, 1, 0, 1};
int digit3[] = {1, 1, 1, 1, 0, 0, 1};
int digit4[] = {0, 1, 1, 0, 0, 1, 1};
int digit5[] = {1, 0, 1, 1, 0, 1, 1};
int digit6[] = {1, 0, 1, 1, 1, 1, 1};
int digit7[] = {1, 1, 1, 0, 0, 0, 0};
int digit8[] = {1, 1, 1, 1, 1, 1, 1};
int digit9[] = {1, 1, 1, 1, 0, 1, 1};
int counter = 0;
  
void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(Pins[i], OUTPUT);
  }
  Serial.begin(115200);
  Serial.println("7-Segment Display Test");
}
void digitDisplay(int states[]) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(Pins[i], !states[i]);
  }
}
void loop() {
  digitDisplay(digit0);
  delay(1000);
  digitDisplay(digit1);
  delay(1000);
  digitDisplay(digit2);
  delay(1000);
  digitDisplay(digit3);
  delay(1000);
  digitDisplay(digit4);
  delay(1000);
  digitDisplay(digit5);
  delay(1000);
  digitDisplay(digit6);
  delay(1000);
  digitDisplay(digit7);
  delay(1000);
  digitDisplay(digit8);
  delay(1000);
  digitDisplay(digit9);
  delay(1000);
}
