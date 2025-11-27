Brief explanation:



Libraries:



Keypad.h→ Handles reading key presses.



LiquidCrystal\_I2C.h→ Controls the LCD via I2C (address 0x27).



Setup:



Row pins →10,9,8,7



Col pins → 6,5,4,3



16×2 LCD initialized at address 0x27.



Calculator Interface:



num1 and num2 indicate which number is being entered.



Pressing an operator switches interface from num1 input mode to num2 input mode



Operators:



A = Add



B = Subtract



C = Multiply



D = Divide



Press \\\* → Clear



Press # → Calculate and show answer



Program Flow:



LCD "Enter num1".



Type digits → stored in inputNum1.



Press operator (A-D) → LCD "Enter num2".



Type digits → stored in inputNum2.



Press # → result shown on LCD.



Also, protection against div by zero by resetting calc, and exiting that void loop.

