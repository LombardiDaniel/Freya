[![MIT License](https://img.shields.io/github/license/LombardiDaniel/Freya.svg?style=flat-square)](LICENSE)
[![Tag](https://img.shields.io/github/tag/LombardiDaniel/Freya.svg?style=flat-square)](https://github.com/LombardiDaniel/Freya/tags)
[![Contributors](https://img.shields.io/github/contributors/LombardiDaniel/Freya.svg?style=flat-square)](https://github.com/LombardiDaniel/Freya/graphs/contributors)
[![LinkedIn](https://camo.githubusercontent.com/c456ce1e22c379a6ff198bbb3a2d96f24fc94408/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f2d4c696e6b6564496e2d626c61636b2e7376673f7374796c653d666c61742d737175617265266c6f676f3d6c696e6b6564696e26636f6c6f72423d353535)](https://www.linkedin.com/in/daniel-lombardi-95b372147/)

## COVID-19 ANNOUNCMENT:

I plan to make some changes to `Freya`, the data-logging will be changed, and a web-app developed
to help manage it, also, I am currently in the state of re-building the garden and will update as possible. The construction of the garden will be documented as well, along with a [instructables](https://www.instructables.com) tutorial in how everything was built. Things should start updating in july.

# Freya

<br />
<p align="center">
  <a href="https://github.com/LombardiDaniel/Freya/">
    <img src="LOGO.jpg" alt="Logo" width="200" height="200">
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


## Table of Contents

* [About the Project](#about-the-project)
* [Getting Started](#getting-started)
    * [Prerequisites](#prerequisites)
    * [Installation](#installation)
    * [Running the tests](#running-the-tests)
* [Deployment](#deployment)
* [Built With](#built-with)
* [Versioning](#versioning)
* [Authors](#authors)
* [License](#license)
* [Acknowledgements](#acknowledgements)

## About the Project

Freya is an autonomous garden built on the Arduino platform, it is capable of a few basic functions and data logging. Built mainly for indoor or outdoor apartment use.

The name was inspired by the Titanic Keeper Freya, that resides in the Temple of Life in Northrend, a continent in Azeroth, from the lore of the game World of Warcraft.

## Getting Started

Everything needed to build Freya using an Arduino Nano can be found in the Circuit.png file, it was built using the open-source software, Fritzing.
About the very own garden structure, it is completely up to the user, pretty much any design will work, as long as the watering tube is capable of delivering water to the soil and the sensors are fitted in it.
On one of my designs, the servo motor used to open/close the hatch is stuck to the side, so it only needs to rotate 180º to completely control the hatch. As for the LEDs, I used a simple, cheap LED strip, to be controlled by a mosfet connected to a digital port on the arduino.

### Prerequisites

All libraries I used are open-source and can be found at:

* [DallasTemperature.h](https://github.com/milesburton/Arduino-Temperature-Control-Library)
* [DS3231.h](http://www.rinkydinkelectronics.com/library.php?id=73)
* [OneWire.h](https://github.com/PaulStoffregen/OneWire)

*All other libraries used come pre-installed with the Arduino IDE*

### Installation

The repository can be cloned via:

```sh
git clone https://github.com/LombardiDaniel/Freya.git
```

After that, just open the code on the [Arduino IDE](https://www.arduino.cc/en/main/software), compile and upload it, making sure that the pins are correctly connected.

The exported files to the SD card will be named as:

```C++
"Freya_data_" + CURRENT DATE + ".txt"
```

and will have the following organization:
```C++
"TIME,HATCH_STATE,LIGHT,SOIL_TEMPERATURE,SOIL_MOISTURE"
```

However, if you are not using the exact same sensors as me, you should make sure that the readings are still correct. Keep in mind that the 'LIGHT' data point is, as of now, just a value, that isn't in any specific unit measure.

### Running the tests

#### If you decide to use a hatch mechanism:

You must be careful as to how the hatch system is built, as most servos can only rotate 180º, that must be taken into consideration, the 'extreme' rotation values (0 and 180) must be aligned to the CLOSED and OPEN position, respectively.
When you run the program, however, the current position does not matter, as it will be set to the open position on system startup (setup phase).
As in lines 63 to 67:

```C++
for (int pos = 0; pos <= 180; pos++)
{
    hatch.write(pos);
    delay(50);
}
hatch_state = "open";
```

## Deployment

Freya is intended to be a cheap autonomous garden, used primarily in apartment verandas. It is not intended to be used on any sort of commercial level. Thus, it was designed to be cheap and easy to build. There is no Soil Acidity sensor because they can be quite expensive, and therefore, are over the desired budget. It needs one power source (a simple 110V power outlet will do) but needs to be stepped down to 9-12V, to be suitable to the Arduino.

## Built With

* [Atom](http://atom.io/) - The text editor used
* [Arduino IDE](https://www.arduino.cc/en/main/software) - Compile and upload software used
* Various other softwares were used, such as Atom Packages, Github itself and others, they are listed on [Acknowledgements](#acknowledgements)

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/LombardiDaniel/Freya/).

## Authors

* **Daniel Lombardi** - *Initial work* - [LombardiDaniel](https://github.com/LombardiDaniel)

See also the list of [contributors](https://github.com/LombardiDaniel/Freya/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

* [Atom](https://atom.io) <3
* Hat tip to anyone whose code was used
