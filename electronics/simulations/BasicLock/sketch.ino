#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define Servo_pin 2

const int rows = 4;
const int cols = 4;
char keyss[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowpins[rows] = {10,9,8,7};
byte colpins[cols] = {6,5,4,3};

Keypad keypad = Keypad(makeKeymap(keyss), rowpins, colpins, rows, cols);
LiquidCrystal_I2C lcd(0x27,16,2);
Servo Servolock;

const int buzzer_pin = 12;
bool Unlocked = false;
String password = "1234";
String inputpassword = "";

void setup() {
  Servolock.attach(Servo_pin);
  lcd.init();
  lcd.backlight();
  Servolock.write(0); // Locked
  lcd.setCursor(0,0);
  lcd.print("Enter the password:");
  pinMode(buzzer_pin,OUTPUT);
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    // Handle number input
    if ((key >= '0') && (key <= '9')) {
      inputpassword += key;
      lcd.setCursor(0,1);
      for (int i=0; i<inputpassword.length(); i++) {
        lcd.print("*");
      }
    }

    // Clear input
    if (key == '*') {
      inputpassword = "";
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter the password:");
    }

    // Submit password
    if (key == '#') {
      if (inputpassword == password) {
        Servolock.write(90);
        Unlocked = true;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Unlocked");
        lcd.setCursor(0,1);
        lcd.print("Press C to lock");
      } else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Wrong password");
        tone(buzzer_pin, 1000);
        delay(300);
        noTone(buzzer_pin);
        delay(500);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Enter the password:");
      }
      inputpassword = "";
    }

    // Lock if 'C' is pressed
    if (key == 'C' && Unlocked) {
      Servolock.write(0);
      Unlocked = false;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Locked");
      delay(500);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter the password:");
    }
  }
}