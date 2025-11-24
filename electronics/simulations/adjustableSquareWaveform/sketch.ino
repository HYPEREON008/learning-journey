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
int halfPeriod;

int highY;   // Y position of HIGH level
int lowY;   // Y position of LOW level


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
  cycles = map(rawF, 0, 4095, 0, 10);
  if(cycles < 1) {
    cycles = 1; // minimum 1 cycle (div by zero error)
  }
  display.clearDisplay();

  int highY = SCREEN_HEIGHT/2 - amplitude; 
  int lowY = SCREEN_HEIGHT/2 + amplitude;  
  halfPeriod = SCREEN_WIDTH/cycles/2;  // width in pixels for one high or low

  int x = 0;
  while(x < SCREEN_WIDTH) {
    // High level
    //x0,yo x1, 
    display.drawLine(x, highY, x + halfPeriod - 1, highY, SSD1306_WHITE);
    // Vertical drop to low
    display.drawLine(x + halfPeriod - 1, highY, x + halfPeriod - 1, lowY, SSD1306_WHITE);
    // Low level
    display.drawLine(x + halfPeriod - 1, lowY, x + 2*halfPeriod - 1, lowY, SSD1306_WHITE);
    // Vertical rise back to high
    display.drawLine(x + 2*halfPeriod - 1, lowY, x + 2*halfPeriod - 1, highY, SSD1306_WHITE);

    x += 2 * halfPeriod;
  }

  display.display();
}
