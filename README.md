<!-- [![Compiling](https://github.com/arduino-libraries/Arduino_Embryo/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/arduino-libraries/Arduino_Embryo/actions/workflows/compile-examples.yml) -->

# Arduino EMBRYO 2

## Description

This library enables the user to program a state machine for EIT Manufacturing's EMBRYO 2 educational modular machine. This library contains the code to control one to several axis of the modular machine.

The assembly instructions and lasercut .dxf files can be found [here]().

This library accompanies 5 free Arduino lessons available at [skills.move](https://www.skillsmove.eu/). The lessons are written for pupils in the ages of 14-16, and aims to introduce them to manufacturing by building their own modular machine.

To find the lessons, navigate to [skills.move](https://www.skillsmove.eu/) and search for "Arduino". The lessons for this library are called:

* Introduction to sensors and their principles
* Motion control + Arduino programming I
* Motion control + Arduino programming II
* Practicum 4: Single motor programming
* Practicum 5: Multi motor programming

**Note:** This library will only be maintained by its users and not by Arduino from January 2022.

## Installation 

1. Navigate to the latest Release page: https://github.com/arduino-libraries/Arduino_Embryo/releases/latest
2. Download the library from the "**Source code (zip)**" link.
3. In the Arduino Offline IDE, navigate to Sketch > Include Library > Add .ZIP Library. At the top of the drop down list, select the option to "Add .ZIP Library".
4. The Library will be available to use in sketches and will be exposed in the File > Examples > Arduino_EMBRYO_2

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

In this first example, the motor should move a specific amount of steps (20000), stop, then move again for 15000 steps.

```arduino
#include "Arduino_EMBRYO_2.h"

/* I N I T I A L   D E F I N I T I O N S */
#define motor01      1

/* C O N S T A N T S   A N D   V A R I A B L E S */
const int enablePin = A5;      // Enable Pin
const int DirPin = 12;         // Direction Pin for motor01
const int PulPin = A4;         // Step Pin for motor01
const int ForwardPin  = A2;    // Forward Button for motor01
const int BackwardPin = A1;    // Backward Button for motor01

const int startPin = 2;        // Start Button
const int emergencyPin  = 5;   // Emergency Button
const int HomeEndstop = 3;     // Home endstop
const int FarEndstop = 4;      // Far From Home endstop

long steps = 0;

/* Construct object, Embryo(Axis, Enable Pin, Direction Pin, Pulse Pin, Endstop Home, Endstop Far, Forward Button, Backward Button, Start Button, Emergency) */
StepMotor motor(motor01,
                enablePin,
                DirPin,
                PulPin,
                HomeEndstop,
                FarEndstop,
                ForwardPin,
                BackwardPin,
                startPin,
                emergencyPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);         // Configure and start Serial Communication
  while (!Serial) {};         // Wait to open the serial monitor

  motor.begin();              // Configure inputs pins, outputs pins and interruptions pins
  motor.startWithoutHoming(); // Initialize the motor separately without being part of an axis

  Serial.println("To start, send any key to serial ...");

  // Without this instruction the motor will move after the upload (It is dangerous)
  while((Serial.available() <= 0)){};

  motor.setTotalSteps(50000); // Set the max step of the motor
  Serial.println("Motor moves.");
  motor.moveSteps(20000);     // Motor moves

  motor.pause();              // Pause the motor
  Serial.println("Motor does not move.");
  motor.moveSteps(50);        // Motor does not move
  delay(2000);
  
  motor.play();               // Enable motor
  Serial.println("Motor moves.");
  motor.moveSteps(15000);     // Motor moves again
}
void loop() {}
```

In this second example, it is possible to control the motor's direction of spinning using two of the buttons that we connected earlier.

```arduino
#include "Arduino_EMBRYO_2.h"

/* I N I T I A L   D E F I N I T I O N S */
#define motor01      1

/* C O N S T A N T S   A N D   V A R I A B L E S */
const int enablePin = A5;      // Enable Pin
const int DirPin = 12;         // Direction Pin for motor01
const int PulPin = A4;         // Step Pin for motor01
const int ForwardPin  = A2;    // Forward Button for motor01
const int BackwardPin = A1;    // Backward Button for motor01

const int startPin = 2;        // Start Button
const int emergencyPin  = 5;   // Emergency Button
const int HomeEndstop = 3;     // Home endstop
const int FarEndstop = 4;      // Far From Home endstop

long steps = 0;

/* Construct object, Embryo(Axis, Enable Pin, Direction Pin, Pulse Pin, Endstop Home, Endstop Far, Forward Button, Backward Button, Start Button, Emergency) */
StepMotor motor(motor01,
                enablePin,
                DirPin,
                PulPin,
                HomeEndstop,
                FarEndstop,
                ForwardPin,
                BackwardPin,
                startPin,
                emergencyPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);          // Configure and start Serial Communication
  while (!Serial) {};          // Wait to open the serial monitor
  
  motor.begin();               // Configure inputs pins, outputs pins and interruptions pins
  motor.startWithoutHoming();  // Initialize the motor without homing procedure, detached
                               // interruptions pins and configures endstops as OUTPUT
                               // Use this function only with the motor outside the axis
} 

void loop() {
  // put your main code here, to run repeatedly:
  // Check the forward button signal
  if(motor.readBtnForward() == HIGH)
    motor.moveForward();        // Motor rotates clockwise

  // Check the backward button signal
  if(motor.readBtnBackward() == HIGH)
    motor.moveBackward();       // Motor rotates anticlockwise
}
```

In the last example, you have to press the start button to start the homing procedure. This allows the machine to send the carriage first to the end point and back to "home" position, then calculate the number of steps it took to determine the length of the axis.

```arduino
#include "Arduino_EMBRYO_2.h"
/* I N I T I A L    D E F I N E S */
#define X_AXIS      1

/*C O N S T A N T S   A N D   V A R I A B L E S*/
const int enablePin = A5;       // Enable Pin
const int DirPin = 5;           // Direction Pin X-axis
const int PulPin = 6;           // Step Pin X-axis
const int BackwardPin = A1;     // Backward Button X-axis
const int ForwardPin  = A2;     // Forward Button X-axis
const int startPin = 2;         // Start Button
const int emergencyPin  = 5;    // Emergency Button
const int HomeEndstop = 3;      // Home endstop X-axis
const int FarEndstop = 4;       // Far From Home endstop X-axis

/* Construct object, StepMotor(Axis, Enable Pin, Direction Pin, Pulse Pin, Endstop Home, Endstop Far, Forward Button, Backward Button, Start Button, Emergency Stop Button) */
StepMotor axis(X_AXIS,
                enablePin,
                DirPin,
                PulPin,
                HomeEndstop,
                FarEndstop,
                ForwardPin,
                BackwardPin,
                startPin,
                emergencyPin);

void setup() {
  Serial.begin(9600);           // Configure and start Serial Communication
  while (!Serial) {};           // Wait to open the serial monitor

  axis.begin();                 // Configure inputs pins, outputs pins and interruptions pins
  
  Serial.println("Press the Start Button to start the machine");
  while(!axis.ready());         // Wait for Start button to be pressed
                                // The start button is attached to the interrupt
                                // service routine that enables the motor and runs
                                // the homing procedure
}
void loop() {
  // put your main code here, to run repeatedly:
  // Check the forward button signal
  if(axis.readBtnForward() == HIGH)
    axis.moveForward();  // Motor rotates clockwise

  // Check the backward button signal
  if(axis.readBtnBackward() == HIGH)
    axis.moveBackward(); // Motor rotates anticlockwise
}
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

- P. Marquínez, Malmö, 2021

The modular machine design and lessons are based on the work previously done by [Nadya Peek & James Coleman]().

## License

### GNU Lesser General Public License v2.1

Primarily used for software libraries, the GNU LGPL requires that derived works be licensed under the same license, but works that only link to it do not fall under this restriction. There are two commonly used versions of the GNU LGPL.

Read more in the LICENSE file.
