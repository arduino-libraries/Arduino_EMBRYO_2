<!-- [![Compiling](https://github.com/arduino-libraries/Arduino_Embryo/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_Embryo/actions/workflows/compile-examples.yml) -->

# Arduino EMBRYO 2

## Description

This library enables the user to program a state machine for EIT Manufacturing's EMBRYO 2 educational modular machine. This library contains the code to control one to several axis of the modular machine.

The assembly instructions and lasercut .dxf files can be found [here]().

This library accompanies 5 free Arduino lessons available at [skills.move](https://www.skillsmove.eu/). The lessons are written for pupils in the ages of 14-16, and aims to introduce them to manufacturing by building their own modular machine.

**Note:** This library will only be maintained by its users and not by Arduino from January 2022.

## Installation 

1. Navigate to the latest Release page: https://github.com/arduino-libraries/Arduino_Embryo/releases/latest
2. Download the library from the "**Source code (zip)**" link.
3. Extract the zip file in the `libraries` folder of your Arduino Sketchbook
4. In the Arduino IDE, navigate to File > Sketchbook > EMBRYO-X.Y.Z

## Features

- ### Easy to use

    It is simple, basic and very easy to understand. Just import the code collection in your Sketchbook and try out the different examples.

- ### Complete package for the EMBRYO 2 modular machine

    Learn how to use the machine from scratch and step by step build a reliable state machine that will give you access to all of its capabilities.

- ### Give back

    EMBRYO is free for everyone. Everyone can download and use it in their projects, assignments or anywhere for free.

## Components and functions

This is an example of how code can be built iteratively around a certain machine but slowly adding improvements to the core software. Here a list of components of the code

  - ### Architecture
    Includes information about the system itself, the pinouts to the connected sensors and actuators, and constructs to navigate through them

  - ### Comm Functions
    Functions dedicated to send and receive information via Serial port

  - ### Data Functions
    Handling of the information from sensors, arranging into easy to compare arrays, etc

  - ### States
    Definitions of names of states to make the code easier to read

## General Code Structure

There are many examples implemented in this repository. Below are shown some of the examples.

``` C++

```

## Versions

### v0.1 (current Stable Version)

### Codename: Emmaboda

#### December, 2021

## Contributing

If you want to contribute to this project:

- Create issues and pull requests
- Tell others about this code
- Contribute new protocols

Please read [CONTRIBUTING.md](https://github.com/arduino/EduIntro/blob/master/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Credits

Created by F. Esquirio Torres, Malmö, 2021

With the assistance of

- P. Martinez, Malmö, 2021

The modular machine design and lessons are based on the work previously done by [Nadya Peek & James Coleman](http://infosyncratic.nl/peek-making-machines.pdf).

## License

Copyright (c) 2020 Arduino SA. All rights reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA