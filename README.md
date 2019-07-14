**AS THE BRANCH NAME SUGGESTS, THIS IS STILL IN ITS TESTING FASE, AND THEREFORE,  THE CODE IS NOT FINISHED AND THERE ARE STILL ADJUSTMENTS NEEDED**

# Freya

[![MIT License](https://img.shields.io/github/license/LombardiDaniel/Freya.svg?style=flat-square)](LICENSE)
[![Tag](https://img.shields.io/github/tag/LombardiDaniel/Freya.svg?style=flat-square)](https://github.com/LombardiDaniel/Freya/tags)
[![Contributors](https://img.shields.io/github/contributors/LombardiDaniel/Freya.svg?style=flat-square)](https://github.com/LombardiDaniel/Freya/graphs/contributors)
[![LinkedIn](https://camo.githubusercontent.com/c456ce1e22c379a6ff198bbb3a2d96f24fc94408/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d4c696e6b6564496e2d626c61636b2e7376673f7374796c653d666c61742d737175617265266c6f676f3d6c696e6b6564696e26636f6c6f72423d353535)](https://www.linkedin.com/in/daniel-lombardi-de-oliveira-95b372147/)

<br />
<p align="center">
  <a href="https://github.com/LombardiDaniel/Freya/">
    <img src="LOGO.jpg" alt="Logo" width="80" height="80">
  </a>

  <p align="center">
    Freya
    <br />
    <br />
    .
    <a href="https://github.com/LombardiDaniel/Freya/issues">Report Bug</a>
    ·
    <a href="https://github.com/LombardiDaniel/Freya/issues">Request Feature</a>
  </p>
</p>


Freya is an autonomous garden built on the Arduino platform, it is capable of a few basic functions and data logging. Built mainly for indoor or outdoor apartment use. The name was inspired by the Titanic Keeper Freya, that resides in the Temple of Life in Northrend, a continent in Azeroth, from the lore of World of Warcraft.

## Getting Started

Everything needed to build Freya using an Arduino Nano can be found in the Circuit.png file, it was built using the open-source software, Fritzing.
About the very own garden structure, it is completely up to the user, pretty much any design will work, as long as the watering tube is capable of delivering water to the soil and the sensors are fitted in it.
On one of my designs, the servo motor used to open/close the hatch is stuck to the side, so it only needs to rotate 180º to completely control the hatch. As for the LEDs, I used a simple, cheap LED strip, to be controlled by a N-channel mosfet.

### Prerequisites

All libraries I used are open-source and can be downloaded free of charge.
```C++
<DallasTemperature.h>
<DS3231.h>
<OneWire.h>
```
They can be found at:

* [DallasTemperature.h](https://github.com/milesburton/Arduino-Temperature-Control-Library)
* [DS3231.h](http://www.rinkydinkelectronics.com/library.php?id=73)
* [OneWire.h](https://github.com/PaulStoffregen/OneWire)

*All other libraries used come pre-installed with the Arduino IDE*

### Installing

Freya does not need any other program to work. Yet, it is recommended (as for data analysis) that you have some sort of spreadsheet software, such as Apple Numbers ou Microsoft Excel, in order to organize graphs and files. Or any other will do i.e. Python Math, R etc.

The exported files to the SD card will be named as:

```C++
"Freya_data_" + CURRENT DATE + ".txt"
```

and will have the following organization:
```C++
"TIME,LIGHT,SOIL_TEMPERATURE,SOIL_MOISTURE"
```

## Running the tests

There are no needed tests needed for Freya to work.

However, if you are not using the exact same sensors as me, you should make sure that the readings are still correct.

### Break down into end to end tests

You must be careful as to how the hatch system is built, as most servos can only rotate 180º, that must be taken into consideration, the 'extreme' rotation values (0 and 180) must be aligned to the CLOSED and OPEN position, respectively.
When you run the program, however, the current position does not matter, as it will be rotated on system begin, to open position.
As in:

```C++
for (int pos = 0; pos <= 180; pos++) {
  hatch.write(pos);
  delay(50);
}
hatch_state = "open";
```

## Deployment

Freya is intended to be a cheap autonomous garden, used primarily on apartment verandas. The software is written in C++ Arduino, and has a few sensors in it, that can be used and combined to measure/do what ever the user feels like. There is no Soil Acidity sensor because they can be quite expensive, and therefore, are over the desired budget. It need one power source (a simple 110V power outlet will do) but needs to be stepped down to 9-12V, to be suitable to the Arduino.

## Built With

* [Atom](http://atom.io/) - The text editor used
* [Arduino IDE](https://www.arduino.cc/en/main/software) - Compile and upload software used
*Various other softwares were used, such as Atom Packages, Github itself and others, they are listed on [Acknowledgements](#acknowledgements).*

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/LombardiDaniel/Freya/).

## Authors

* **Daniel Lombardi** - *Initial work* - [LombardiDaniel](https://github.com/LombardiDaniel)

See also the list of [contributors](https://github.com/LombardiDaniel/Freya/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* [language-arduino](https://atom.io/packages/language-arduino)
* [arduino-upload](https://atom.io/packages/arduino-upload)
* Hat tip to anyone whose code was used
