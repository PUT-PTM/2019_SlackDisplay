# 2019_SlackDisplay
## Overview
This project is an app displaying messages from Slack on microcontroller.

## Description
App is divided into two parts.

One of them is Slack-Bot that is a server side of an app. Slack-Bot is written in Python with SlackAPI and launched on PC. It downloads channels and messages from Slack (using API) and sends it to microcontroller via USB. It also checks in another thread if some new message or channel hasn’t appeared.

The other one is microcontroller written in C. Microcontroller gets messages from Slack-Bot and shows them on LCD 16x2 display connected via I2C bus. There is implemented navigation with four buttons: up, down, ok, main menu.

## Tools  
1. STM32CubeMX v4.27.0 
2. System Workbench for STM32 (Neon.3 Release v4.6.3) 
3. JetBrains PyCharm 2018.2.4
4. JetBrains CLion 2018.2.6

## Hardware
* Display LCD 2x16 + converter I2C
* STM32F407G-DISC1  
* 2x4 matrix Button Board 
* Board with speaker and potentiometer

## How to connect peripheral devices
1. LCD 16x2 with I2C module: 
* PB9 - SDA 
* PB8 - SCL
* 5V
* 3V
* GND
2. SPEAKER WITH ADC AND DAC: 
* PA4 - DAC 
* 5V
* GND

* PA6 - ADC
* 3V
* GND
3. BUTTONS: 
* PB15 - GPIO_EXTI
* PB14 - GPIO_EXTI
* PB13 - GPIO_EXTI
* PB12 - GPIO_EXTI
* GND
 
## How to compile & run
Firstly open the vcom-test.ioc file with STM32CubeMX and generate code. Connect microcontroller and PC with Windows using miniUSB-B and microUSB-B cables. Then use IDE to send code to microcontroller via miniUSB-B cable using ST-Link firmware. Then launch server with command:

 ```python slackbot.py```
 
 
## Future improvements
* better (bigger) display
* sending messages to the slack
* wireless connection with server
* notification LED
 
## Attributions  
The code which we used in the project was from: 
* [Display library](https://www.youtube.com/watch?v=Vqa32DgDxF0)
* [SlackAPI](https://api.slack.com)
* [Vcom port](https://forbot.pl/blog/kurs-stm32-f4-11-komunikacja-przez-usb-id13477?fbclid=IwAR2L2-Rs2Af_UM4WdGpiWiXak3IGdXg6epEbEE-lRZCrZeGnMHm4bnhpGDE)
* [Lab materials from 3rd term](https://drive.google.com/drive/folders/0B7GyMR8rCWn4OUJHOVZHYXhNZ2M)

## License
MIT 
## Credits: 
[Mateusz Ostrowski](https://github.com/matostr98)  
[Adam Przywuski](https://github.com/adamprzywuski)  
The project was conducted during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology. 
Supervisor: Tomasz Mańkowski 

![61930626_2346513172289692_3868206769805197312_n](https://user-images.githubusercontent.com/34038750/58832754-ef7d1080-864f-11e9-9ed0-93c2de0e7a2c.jpg)
