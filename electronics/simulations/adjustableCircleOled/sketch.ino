#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int potPin = 34;
int radius = 0;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// position (center)
int x = SCREEN_WIDTH / 2;
int y = SCREEN_HEIGHT / 2;

void setup() {
  Wire.begin(21, 22); // SDA, SCL

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true); // Stop if OLED not found
  }

  display.clearDisplay();
  display.display(); // Send to OLED
}

void loop() {
  radius = analogRead(potPin)/128;  //map 0-4095 to 0-32 since that is max radius

  display.clearDisplay();
  display.drawCircle(x,y, radius, SSD1306_WHITE);
  display.display(); // Send to OLED

  delay(10);

}