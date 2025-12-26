// #include <Arduino.h>

// // put function declarations here:
// int myFunction(int, int);

// void setup() {
//   // put your setup code here, to run once:
//   int result = myFunction(2, 3);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// // put function definitions here:
// int myFunction(int x, int y) {
//   return x + y;
// }
#include <Arduino.h>

int pins[] = {2, 4, 18};
const int numPins = sizeof(pins) / sizeof(pins[0]);

void setup() {
  // Set pins as output
  for (int i = 0; i < numPins; i++) {
    pinMode(pins[i], OUTPUT);
  }

  Serial.begin(115200);
  // while (!Serial) {
  //   delay(10);
  // }
  Serial.println("APP STARTED");
}

void loop() {
  // Toggle HIGH
  for (int i = 0; i < numPins; i++) {
    digitalWrite(pins[i], HIGH);
  }
  delay(500); // 0.5 sec

  // Toggle LOW
  for (int i = 0; i < numPins; i++) {
    digitalWrite(pins[i], LOW);
  }
  delay(500);
}
