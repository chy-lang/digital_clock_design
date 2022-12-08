# digital_clock_design
In this project, I utilized STM32 microcontroller to develop a digital clock, which contains following functions: 
• Obtain the current temperature and humidity via a sensor module with I2C interface;
• Obtain the current date, specific time and other information via an ESP-8266 WIFI module; 
• Display all the information collected on the LCD screen;
• Achieve the function of “inquiry” based on interrupt
The code is based on the template provided by "正点原子". A great amount of modifications were made from the orginal template, due to the incompatibility of hardware equipment with the template and the extensive usage of devices. 

![image](https://user-images.githubusercontent.com/79852857/206415002-848a8741-c219-45bb-8f76-6e860c0c8e15.png)

System initialization

![image](https://user-images.githubusercontent.com/79852857/206415359-a5bf0444-0964-4c8e-8e21-5bef2c8201b4.png)

Waiting for command

![image](https://user-images.githubusercontent.com/79852857/206415433-f22ac166-ad91-49a0-8d06-6b9ac9b69dec.png)

Enter interrupt
