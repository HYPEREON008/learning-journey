#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int timeDelay = 2000;
const int DHT22Pin = 33;
float Humidity, Temperature;

DHT MyDHT(DHT22Pin, DHT22);

void setup() {

  Serial.begin(115200);
  MyDHT.begin();
  Wire.begin(21, 22); // SDA, SCL

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true); // Stop while OLED not found
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("DHT22 Sensor Test");
  display.display(); // Send to OLED
  delay(timeDelay);
}

void loop() {
  Humidity = MyDHT.readHumidity();
  Temperature = MyDHT.readTemperature();

  if (isnan(Humidity)||isnan(Temperature)) {
    Serial.println("Reading Failed");
  }
  else {
    Serial.print(Humidity);
    Serial.println(Temperature);

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.print("Humidity: ");
    display.print(Humidity);
    display.println(" %");
    display.print("Temperature: ");
    display.print(Temperature);
    display.println(" C");
    display.display(); // Send to OLED
  }
  delay(timeDelay);
}
