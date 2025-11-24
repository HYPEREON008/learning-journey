#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

//MCP-based modules sometimes require special initialization 
//code or a different library, while PCF8574
//is supported by the standard LiquidCrystal_I2C library.
//so using PCF based lcd


const int rows = 4;
const int cols = 4;
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowpins[rows] = {10,9,8,7};
byte colpins[cols] = {6,5,4,3};

Keypad keypad = Keypad(makeKeymap(keys), rowpins, colpins, rows, cols);
LiquidCrystal_I2C lcd(0x27,16,2);

unsigned long inputNum1;
unsigned long inputNum2;

bool num1;
bool num2;

char operationChar = '\0';  //null char in a diff way to prevent error
//for assigning null to char data type

void resetCalculator() {
  inputNum1 = 0;
  inputNum2 = 0;
  num1 = true;
  num2 = false;
  operationChar = '\0';
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter num1:");
  lcd.setCursor(0,1);
  }
void setup() {
  lcd.init();
  lcd.backlight();
  
  resetCalculator();
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    if ((key >= '0') && (key <= '9')) {
      if (num1==true) {
        inputNum1 = 10*inputNum1 + (key-'0'); //this converts the string key to its numeric value
        lcd.print(key);
      }
      if (num2==true) {
        inputNum2 = 10*inputNum2 + (key-'0');
        lcd.print(key);
      
      }
    }
    
    else if (key == '*') {
      resetCalculator();
    }

    else if (key == '#') {
      long ans;
      if (operationChar == 'A') ans = inputNum1 + inputNum2;
	  if (operationChar == 'B') ans = inputNum1 - inputNum2;
	  if (operationChar == 'C') ans = inputNum1 * inputNum2;
      if (operationChar == 'D') {
        if (inputNum2 == 0) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Error");
          delay(300);
          resetCalculator();
          return;
        }
        ans = inputNum1 / inputNum2;
      }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(String(ans));
      
    }
    else {
      num1 = false;
      num2 = true;
      operationChar = key;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter num2:");
      lcd.setCursor(0,1);
      
    }  
  }
}