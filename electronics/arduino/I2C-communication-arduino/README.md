Brief explanation:



Wire.h → for I2C communication between the 2 boards



Master working:



The master reads a potentiometer value (0-1023).



Divides it by 4 to map it to (0-255).



Sends it via I2C to the slave at address 8 every 50 ms.



The Wire library handles the I2C protocol automatically



Slave working:



The slave has address 8, the same as used by the master.



receiveEvent() is automatically called when data arrives.



It reads the byte, prints it, and uses it to set LED brightness (PWM pin 10).



So, rotating the potentiometer on the master smoothly controls LED brightness on the slave.





