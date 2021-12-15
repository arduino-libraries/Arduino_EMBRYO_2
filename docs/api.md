# Embryo II library

## Methods

### `StepMotor(uint8_t id, uint8_t enablePin, uint8_t directionPin, uint8_t pulsePin, uint8_t homePin, uint8_t farPin, uint8_t forwardPin, uint8_t backwardPin, uint8_t startPin, uint8_t emergencyStopPin)`

Attaches the motor and controls buttons to the pins.

#### Syntax

```
StepMotor axis(AXIS_ID,
               enablePin,
               directionPin,
               pulsePin,
               homePin,
               farPin,
               forwardPin,
               backwardPin,
               startPin,
               emergencyStopPin);
```

#### Parameters

-   AXIS_ID: motor unique ID (numeric)
-   enablePin: Pin connected to motor enable pin
-   directionPin: Pin connected to motor direction pin
-   pulsePin: Pin connected to motor pulse pin
-   homePin: Pin connected to home position endstop switch
-   farPin: Pin connected to far from home endstop switch
-   forwardPin: Pin connected to forward button
-   backwardPin: Pin connected to backward button
-   startPin: Pin connected to initialization button
-   emergencyStopPin: Pin connected to emergency stop button

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);


void setup() {}
void loop() {}
```

#### See also

-   [begin()](#begin)
-   [start()](#start)
-   [checkInputs()](#checkInputs)
-   [end()](#end)

### `begin()`

Configures inputs pins, outputs pins and interuptions pins.

#### Syntax

```
axis.begin()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();   // Configure inputs pins, outputs pins and interuptions pins
}
void loop() {}
```

#### See also

-   [end()](#end)
-   [play()](#play)
-   [pause()](#pause)
-   [prepareInterrupt()](#prepareInterrupt)
-   [start()](#start)

### `start()`

Initializes the motor.

Enables and starts the motor, then the motor is set as ready and does the homing procedure. This function is associated with the Start Button ISR.

#### Syntax

```
axis.start()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  axis.start();  // Initialize motor and run the homing procedure
}
void loop() {}
```

#### See also

-   [end()](#end)
-   [homing()](#homing)
-   [pause()](#pause)
-   [play()](#play)
-   [ready()](#ready)
-   [startWithoutHoming()](#startWithoutHoming)

### `startWithoutHoming()`

Initializes the motor.

Enables and starts the motor, then the motor is set as ready but it doesn't run the homing procedure. Use this function only with the motor outside the axis.

#### Syntax

```
axis.startWithoutHoming()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  axis.startWithoutHoming();  // Initialize motor without homing procedure
  axis.homing();              // Run the home procedure
}
void loop() {}
```

#### See also

-   [end()](#end)
-   [homing()](#homing)
-   [play()](#play)
-   [pause()](#pause)
-   [ready()](#ready)
-   [start()](#start)
-   [terminateInterrupt()](#terminateInterrupt)

### `end()`

Disables the motor and sets it as not ready. This function is associated with the Emergency Stop Button ISR.

#### Syntax

```
axis.end()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  axis.start();
  axis.end();
}
void loop() {}
```

#### See also

-   [play()](#play)
-   [pause()](#pause)
-   [ready()](#ready)
-   [start()](#start)

### `play()`

Enables the motor if the motor is initialized.

#### Syntax

```
axis.play()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  axis.start();
  delay(500);
  axis.moveSteps(50);  // Motor moves
  axis.pause();        // Disable motor
  axis.moveSteps(50);  // Motor does not move
  delay(500);
  axis.play();         // Enable motor
  axis.moveSteps(50);  // Motor moves again
}
void loop() {}
```

#### See also

-   [end()](#end)
-   [moveSteps()](#moveSteps)
-   [pause()](#pause)
-   [start()](#start)

### `pause()`

Disables the motor.

#### Syntax

```
axis.pause()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  axis.start();
  delay(500);
  axis.moveSteps(50);  // Motor moves
  axis.pause();        // Disable motor
  axis.moveSteps(50);  // Motor does not move
  delay(500);
  axis.play();         // Enable motor
  axis.moveSteps(50);  // Motor moves again
}
void loop() {}
```

#### See also

-   [end()](#end)
-   [moveSteps()](#moveSteps)
-   [play()](#play)
-   [start()](#start)

### `homing()`

Executes the homing procedure, but it doesn't set the motor as ready.

#### Syntax

```
axis.homing()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  axis.startWithoutHoming();  // Initialize motor without homing procedure
  axis.homing();              // Run the home procedure
}
void loop() {}
```

#### See also

-   [end()](#end)
-   [readEndstopFar()](#readEndstopFar)
-   [readEndstopHome()](#readEndstopHome)
-   [start()](#start)
-   [startWithoutHoming()](#startWithoutHoming)

### `ready()`

Returns a boolean value that indicates if the motor is ready.

#### Syntax

```
axis.ready()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press the Start Button to start the machine");
  while(!axis.ready());  // Wait for Start button to be pressed
                         // The start button is attached to the interrupt
                         // service routine that enables the motor and runs
                         // the homing procedure
  axis.moveSteps(50);    // Motor 50 steps
}
void loop() {}
```

#### See also

-   [begin()](#begin)
-   [end()](#end)
-   [moveStep()](#moveStep)
-   [start()](#start)

### `prepareInterrupt()`

Attaches to interrupt pins of the start and emergency stop buttons.

#### Syntax

```
axis.prepareInterrupt()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  terminateInterrupt();  // Detach the interrupt pins
  prepareInterrupt();  // Attach the interrupt pins
}
void loop() {
  if(axis.readBtnForward()) axis.moveForward();
  if(axis.readBtnBackward()) axis.moveBackward();
}
```

#### See also

-   [begin()](#begin)
-   [prepareInterrupt()](#prepareInterrupt)
-   [teminateInterrupt()](#teminateInterrupt)

### `terminateInterrupt()`

Detaches to interrupt pins of the start and emergency stop buttons.

#### Syntax

```
axis.terminateInterrupt()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  terminateInterrupt();  // Detach the interrupt pins
  prepareInterrupt();  // Attach the interrupt pins
}
void loop() {
  if(axis.readBtnForward()) axis.moveForward();
  if(axis.readBtnBackward()) axis.moveBackward();
}
```

#### See also

-   [begin()](#begin)
-   [prepareInterrupt()](#prepareInterrupt)
-   [teminateInterrupt()](#teminateInterrupt)

### `moveForward()`

Rotates motor in clockwise direction and pulses the motor one half step. Moves the robot carriage farther from motor home.

#### Syntax

```
axis.moveForward()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press Init Button to start the machine");
  while(!axis.ready()); // Wait for Init button to be pressed
}
void loop() {
  if(axis.readBtnForward()) axis.moveForward();
  if(axis.readBtnBackward()) axis.moveBackward();
}
```

#### See also

-   [moveBackward()](#moveBackward)
-   [readBtnBackward()](#readBtnBackward)
-   [readBtnForward()](#readBtnForward)
-   [readEndstopFar()](#readEndstopFar)
-   [ready()](#ready)

### `moveBackward()`

Rotates motor in anticlockwise direction and pulses the motor one half step. Moves the robot carriage closer to motor home.

#### Syntax

```
axis.moveBackward()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press the Start Button to start the machine");
  while(!axis.ready()); // Wait for Start button to be pressed
}
void loop() {
  if(axis.readBtnForward()) axis.moveForward();
  if(axis.readBtnBackward()) axis.moveBackward();
}
```

#### See also

-   [moveForward()](#moveForward)
-   [readBtnBackward()](#readBtnBackward)
-   [readBtnForward()](#readBtnForward)
-   [readEndstopHome()](#readEndstopHome)
-   [ready()](#ready)

### `moveSteps()`

Rotates the motor a specified number of steps. Positive step rotates the motor in clockwise direction and moves the robot carriage farther from motor home. Negative step rotates the motor in anticlockwise direction and moves the robot carriage closer to motor home.

#### Syntax

```
axis.moveSteps(numSteps)
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press the Start Button to start the machine");
  while(!axis.ready()); // Wait for Start button to be pressed
}
void loop() {
  if(axis.readBtnForward()) axis.moveSteps(50);
  if(axis.readBtnBackward()) axis.moveSteps(-50);
}
```

#### See also

-   [moveBackward()](#moveBackward)
-   [moveForward()](#moveForward)
-   [readBtnBackward()](#readBtnBackward)
-   [readBtnForward()](#readBtnForward)
-   [ready()](#ready)
-   [toStep()](#toStep)

### `moveDistance()`

Rotates the motor and move the robot carriage a specified distance in centimeters. Positive distance moves the robot carriage farther from motor home. Negative distance moves the robot carriage closer to motor home.

#### Syntax

```
axis.moveDistance(distance)
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press the Start Button to start the machine");
  while(!axis.ready()); // Wait for Start button to be pressed
}
void loop() {
  if(axis.readBtnForward()) axis.moveDistance(5);
  if(axis.readBtnBackward()) axis.moveDistance(-5);
}
```

#### See also

-   [moveSteps()](#moveSteps)
-   [readBtnBackward()](#readBtnBackward)
-   [readBtnForward()](#readBtnForward)
-   [ready()](#ready)
-   [toPosition()](#toPosition)

### `toStep()`

Moves the robot carriage to a specified step count. Zero is the motor home position and max number of steps is the axis end far from the motor home.

#### Syntax

```
axis.toStep(step)
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press the Start Button to start the machine");
  while(!axis.ready()); // Wait for Start button to be pressed
  Serial.println("Current step: " + String(axis.getStep()));
  delay(1000);
  axis.toStep(1000);
  Serial.println("Current step: " + String(axis.getStep()));
}
void loop() {}
```

#### See also

-   [getStep()](#getStep)
-   [moveSteps()](#moveSteps)
-   [ready()](#ready)
-   [toPosition()](#toPosition)

### `toPosition()`

Moves the robot carriage to a specified position in centimeters along the robot axis. Zero is the motor home position and max position is in the axis end far from the motor home and is equal to the length of the axis.

#### Syntax

```
axis.toPosition(position)
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press the Start Button to start the machine");
  while(!axis.ready()); // Wait for Start button to be pressed
  Serial.println("Initial position: " + String(axis.getPosition()));
  delay(1000);
  axis.toPosition(15);
  Serial.println("Final position: " + String(axis.getPosition()));
}
void loop() {}
```

#### See also

-   [getPosition()](#getPosition)
-   [moveDistance()](#moveDistance)
-   [ready()](#ready)
-   [setLength()](#setLength)
-   [toStep()](#toStep)

### `setSpeed()`

Sets the motor's speed, in milliseconds, according to the time between pulses. The maximum speed is 200 milliseconds and the minimum speed is 25000 milliseconds. The default speed value is 200 milliseconds.

#### Syntax

```
axis.setSpeed(speed)
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  axis.startWithoutHomming();  // Initialize the motor without homing procedure
  axis.setSpeed(7000); // The motor moves slower
  for (int i = 0; i < 20000; i++)axis.moveForward();
  delay(1000);
  axis.setSpeed(); // The motor moves in the default speed, 200 milliseconds
  for (int i = 0; i < 20000; i++)axis.moveBackward();
  delay(1000);
  axis.stop();
}
void loop() {}
```

#### See also

-   [getPosition()](#getPosition)
-   [moveDistance()](#moveDistance)
-   [moveSteps()](#moveSteps)
-   [ready()](#ready)
-   [toStep()](#toStep)

### `getStep()`

Returns the current step count of the motor.

#### Syntax

```
axis.getStep()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press the Start Button to start the machine");
  while(!axis.ready()); // Wait for Start button to be pressed
  Serial.println("Current step: " + String(axis.getStep()));
  delay(1000);
  axis.toStep(1000);
  Serial.println("Current step: " + String(axis.getStep()));
}
void loop() {}
```

#### See also

-   [moveSteps()](#moveSteps)
-   [ready()](#ready)
-   [toStep()](#toStep)

### `getPosition()`

Returns the current position of the robot carriage in centimeters.

#### Syntax

```
axis.getPosition()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press the Start Button to start the machine");
  while(!axis.ready()); // Wait for start button to be pressed
  delay(1000);
  Serial.println("Initial position: " + String(axis.getPosition()));
  delay(1000);
  axis.setPosition(15);
  Serial.println("Final position: " + String(axis.getPosition()));
}
void loop() {}
```

#### See also

-   [getStep()](#getStep)
-   [moveDistance()](#moveDistance)
-   [ready()](#ready)
-   [setLength()](#setLength)
-   [toPosition()](#toPosition)

### `readBtnForward()`

Returns the boolean value in the pin connected to the Forward Button.

#### Syntax

```
axis.readBtnForward()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press the Start Button to start the machine");
  while(!axis.ready()); // Wait for Start button to be pressed
}
void loop() {
  if(axis.readBtnForward()) axis.moveForward();
  if(axis.readBtnBackward()) axis.moveBackward();
}
```

#### See also

-   [moveBackward()](#moveBackward)
-   [moveForward()](#moveForward)
-   [readBtnBackward()](#readBtnBackward)

### `readBtnBackward()`

Returns the boolean value in the pin connected to the Backward Button.

#### Syntax

```
axis.readBtnBackward()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press the Start Button to start the machine");
  while(!axis.ready()); // Wait for Start button to be pressed
}
void loop() {
  if(axis.readBtnForward()) axis.moveForward();
  if(axis.readBtnBackward()) axis.moveBackward();
}
```

#### See also

-   [moveBackward()](#moveBackward)
-   [moveForward()](#moveForward)
-   [readBtnForward()](#readBtnForward)

### `readBtnStart()`

Returns the boolean value in the pin connected to the Start Button. This button invokes the initialization ISR and the start() method.

#### Syntax

```
axis.readBtnStart()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Start button logic");
  Serial.println("Not pressed: " + String(axis.readBtnStart()));
  Serial.println("Pressed: " + String(!axis.readBtnStart()));
}
void loop() {}
```

#### See also

-   [start()](#start)
-   [ready()](#ready)

### `readBtnEmergencyStop()`

Returns the boolean value in the pin connected to the Emergency Stop Button. This button invokes the emergency stop ISR and the end() method.

#### Syntax

```
axis.readBtnEmergencyStop()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Emergency Stop button logic");
  Serial.println("Not pressed: " + String(axis.readBtnEmergencyStop()));
  Serial.println("Pressed: " + String(!axis.readBtnEmergencyStop()));
}
void loop() {}
```

#### See also

-   [end()](#end)
-   [ready()](#ready)

### `readEndstopHome()`

Returns the boolean value in the pin connected to the Endstop switch in the motor home.

#### Syntax

```
axis.readEndstopHome()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Endstop Home logic");
  Serial.println("Not pressed: " + String(axis.readEndstopHome()));
  Serial.println("Pressed: " + String(!axis.readEndstopHome()));
}
void loop() {}
```

#### See also

-   [homing()](#homing)
-   [moveBackward()](#moveBackward)
-   [readEndstopFar()](#readEndstopFar)

### `readEndstopFar()`

Returns the boolean value in the pin connected to the Endstop switch far from the motor home.

#### Syntax

```
axis.readEndstopFar()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Endstop Far logic");
  Serial.println("Not pressed: " + String(axis.readEndstopFar()));
  Serial.println("Pressed: " + String(!axis.readEndstopFar()));
}
void loop() {}
```

#### See also

-   [homing()](#homing)
-   [moveForward()](#moveForward)
-   [readEndstopHome()](#readEndstopHome)

### `setTotalSteps()`

Sets the total steps count of the motor. The total steps is initialized with 0 and assigned with the correct number of steps during the homing procedure. But, using this function, is possible to set the total steps count without the homing procedure .

#### Syntax

```
axis.setTotalSteps()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  motor.init(false);  // Initialize the motor without homing procedure
  motor.setTotalSteps(50000); // Set the maximum steps of the motor
}
void loop() {}
```

#### See also

-   [homing()](#homing)
-   [getStep()](#getStep)
-   [getTotalSteps()](#getTotalSteps)

### `getTotalSteps()`

Returns the total steps count of the motor in the robot axis. The total steps is initialized with 0 and assigned with the correct number of steps during the homing procedure.

#### Syntax

```
axis.getTotalSteps()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  Serial.println("Total steps initial: " + String(axis.getTotalSteps()));
  axis.homing();
  Serial.println("Total steps after homing procedure: " + String(axis.getTotalSteps()));
}
void loop() {}
```

#### See also

-   [homing()](#homing)
-   [getStep()](#getStep)
-   [setTotalSteps()](#setTotalSteps)

### `setLength()`

Sets the length of the robot axis in centimeters.

#### Syntax

```
axis.setLength()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.setLenght(45);
}
void loop() {}
```

#### See also

-   [moveDistance()](#moveDistance)
-   [setPosition()](#setPosition)

### `checkInputs()`

Verifies and print the current boolean values of the inputs.

#### Syntax

```
axis.checkInputs()
```

#### Example

```
#include <Embryo_II.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();
  axis.checkInputs();
}
void loop() {}
```

#### See also

-   [readBtnBackward()](#readBtnBackward)
-   [readBtnEmergencyStop()](#readBtnEmergencyStop)
-   [readBtnForward()](#readBtnForward)
-   [readBtnStart()](#readBtnStart)
-   [readEndstopFar()](#readEndstopFar)
-   [readEndstopHome()](#readEndstopHome)
