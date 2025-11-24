#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int POT_AMPL_PIN = 26;
const int POT_FREQ_PIN = 27; 

int maxAmp = (SCREEN_HEIGHT / 2) - 2;        // leave 2 px margin
int rawA;
int rawF;

float amplitude;
float cycles;


void setup() {
  Wire.begin(21, 22); // SDA, SCL

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true); // Stop if OLED not found
  }

  display.clearDisplay();
}

void loop() {
  rawA = analogRead(POT_AMPL_PIN);
  rawF = analogRead(POT_FREQ_PIN);

  amplitude = map(rawA, 0, 4095, 0, maxAmp);
  cycles = map(rawF, 0, 4095, 0, 6);
  display.clearDisplay();

  // Draw sine wave
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    // Map x to angle in radians (0 to 2*PI for one full sine wave cycle)
    float radians = (float)x * 2 * 3.14159 / SCREEN_WIDTH * cycles;

    // Calculate y, scale amplitude to fit screen height
    int y = (int)((sin(radians) * (amplitude)) + SCREEN_HEIGHT/2);

    // Draw pixel
    display.drawPixel(x, y, SSD1306_WHITE);
  }

  display.display();
}
