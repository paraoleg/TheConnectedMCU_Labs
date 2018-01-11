A temperature control system with IoT. 

The device consists of a chipkit WiFire board with PIC32MZ microcontroller, bluetooth module HC-05, temperature sensor DS18b20. The lamp uses the LD1 LED on the board. 

Control is carried out using the Android application on the smartphone via bluetooth. The screen displays the value of the temperature in Celcium, which is measured by the sensor. You can turn the lamp on and off with the buttons TurnON and TurnOFF. 

For programming, the Arduino IDE was used. To configure the Arduino IDE, you need to follow the instructions in the guides: https://www.youtube.com/watch?v=DOEdmc57FVU and https://chipkit.net/wiki/index.php?title=ChipKIT_core. You also need to download and connect the libraries: OneWire.h, DallasTemperature.h.