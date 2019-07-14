# Freya

**AS THE BRANCH NAME SUGGESTS, THIS IS STILL IN ITS TESTING FASE**

Freya is an autonomous garden built on the Arduino platform, it is capable of a few basic functions and data logging. Built mainly for indoor or outdoor apartment use. The name was inspired by the Titanic Keeper Freya, that resides in the Temple of Life in Northrend, a continent in Azeroth, from the lore of World of Warcraft.

## Getting Started

Everything needed to build Freya using an Arduino Nano can be found in the Circuit.png file, it was built using the open-source software, Fritzing.
About the very own garden structure, it is completely up to the user, pretty much any design will work, as long as the watering tube is capable of delivering water to the soil and the sensors are fitted in it.
On one of my designs, the servo motor used to open/close the hatch is stuck to the side, so it only needs to rotate 180º to completely control the hatch. As for the LEDs, I used a simple, cheap LED strip, to be controlled by a N-channel mosfet.

### Prerequisites

All libraries I used are open-source and can be downloaded free of charge.
```
<DallasTemperature.h>
<DS3231.h>
<OneWire.h>
```
They can be found at:
```
https://github.com/milesburton/Arduino-Temperature-Control-Library
http://www.rinkydinkelectronics.com/library.php?id=73
https://github.com/PaulStoffregen/OneWire
```
The other libraries are pre-intalled with the Arduino IDE

### Installing

Freya does not need any other program to work. Yet, it is recommended (as for data analysis) that you have some sort of spreadsheet software, such as Apple Numbers ou Microsoft Excel, in order to organize graphs and files. Or any other will do i.e. Python Math, R etc.

The exported files to the SD card will start as:

```
"Freya_data_" + current date + ".txt"
```

and will have the following organization:
```
"TIME,LIGHT,SOIL_TEMPERATURE,SOIL_MOISTURE"
```

## Running the tests

There are no needed tests needed for Freya to work.

However, if you are not using the exact same sensors as me, you should make sure that the readings are still correct.
