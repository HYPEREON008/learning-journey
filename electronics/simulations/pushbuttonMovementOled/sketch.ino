#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int buttonPins[4] = {16,17,18,19};  // N, E, S, W
const char directions[4] = {'N', 'E', 'S', 'W'};


// starting position (center)
int x = SCREEN_WIDTH / 2;
int y = SCREEN_HEIGHT / 2;

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true); // Stop if OLED not found
  }

  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  Wire.begin(21, 22); // SDA, SCL
  display.clearDisplay();
  display.fillCircle(x, y, 3, SSD1306_WHITE);
  display.display();

  
}

void loop() {
      if(digitalRead(buttonPins[0]) == LOW) y -= 2; // N
      if(digitalRead(buttonPins[1]) == LOW) x += 2; // E
      if(digitalRead(buttonPins[2]) == LOW) y += 2; // S
      if(digitalRead(buttonPins[3]) == LOW) x -= 2; // W

      // check boundaries
      if(x < 0) x = 0;
      if(x > SCREEN_WIDTH-1) x = SCREEN_WIDTH-1;
      if(y < 0) y = 0;
      if(y > SCREEN_HEIGHT-1) y = SCREEN_HEIGHT-1;


      // Draw circle at new position
      display.fillCircle(x, y, 3, SSD1306_WHITE);
      display.display();

      delay(50); // small delay smh makes stuff smoother maybe debouncing
 }