# Arduino EMBRYO 2 library

## StepMotor

### `StepMotor()`

This function creates an instance of StepMotor Class for EMBRYO 2 that represent a linear axis of the robot. Use it at the top of your sketch, above `setup()` and `loop()`.

#### Syntax

```
StepMotor(AXIS_ID,
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
#include <Arduino_EMBRYO_2.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);


void setup() {}
void loop() {}
```

#### See also

-   [begin()](#begin)
-   [checkInputs()](#checkInputs)
-   [end()](#end)
-   [start()](#start)

### `begin()`

Configures inputs pins, outputs pins and interruptions pins.

#### Syntax

```
axis.begin()
```

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.begin();   // Configure inputs pins, outputs pins and interruptions pins
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
#include <Arduino_EMBRYO_2.h>

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
#include <Arduino_EMBRYO_2.h>

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
#include <Arduino_EMBRYO_2.h>

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
#include <Arduino_EMBRYO_2.h>

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
#include <Arduino_EMBRYO_2.h>

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
#include <Arduino_EMBRYO_2.h>

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
#include <Arduino_EMBRYO_2.h>

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
#include <Arduino_EMBRYO_2.h>

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
#include <Arduino_EMBRYO_2.h>

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
#include <Arduino_EMBRYO_2.h>

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
#include <Arduino_EMBRYO_2.h>

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

#### Parameters

* _numSteps_: number of the steps

#### Example

```
#include <Arduino_EMBRYO_2.h>

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

#### Parameters

* _distance_: distance in centimeters 

#### Example

```
#include <Arduino_EMBRYO_2.h>

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

Moves the robot carriage to a specified step count. Zero is in the motor home position and max number of steps is in the axis end far from the motor home.

#### Syntax

```
axis.toStep(step)
```
#### Parameters

* _step_: position in step counts with home equals to zero

#### Example

```
#include <Arduino_EMBRYO_2.h>

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

#### Parameters

* _position_: position in centimeters with home equals to zero

#### Example

```
#include <Arduino_EMBRYO_2.h>

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

Sets the motor's speed, in milliseconds, according to the time between pulses. This value is the motor's time to make a half step. The maximum speed is 200 milliseconds and the minimum speed is 25000 milliseconds. The default speed value is 200 milliseconds.

#### Syntax

```
axis.setSpeed(speed)
```
#### Parameters

* _speed_: time in milliseconds between pulses (defaults to 200)

#### Example

```
#include <Arduino_EMBRYO_2.h>

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
#### Returns

The current step count with home equals to zero.

#### Example

```
#include <Arduino_EMBRYO_2.h>

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

#### Returns

The current distance in centimeters from motor home position.

#### Example

```
#include <Arduino_EMBRYO_2.h>

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
#### Returns

The forward button signal: LOW or HIGH.

#### Example

```
#include <Arduino_EMBRYO_2.h>

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
#### Returns

The backward button signal: LOW or HIGH.

#### Example

```
#include <Arduino_EMBRYO_2.h>

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
#### Returns

The start button signal: LOW or HIGH.

#### Example

```
#include <Arduino_EMBRYO_2.h>

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
#### Returns

The emergency stop button signal: LOW or HIGH.

#### Example

```
#include <Arduino_EMBRYO_2.h>

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
#### Returns

The signal of the endstop switch in motor home: LOW or HIGH.

#### Example

```
#include <Arduino_EMBRYO_2.h>

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

#### Returns

The signal of the endstop switch far from motor home: LOW or HIGH.

#### Syntax

```
axis.readEndstopFar()
```

#### Example

```
#include <Arduino_EMBRYO_2.h>

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
axis.setTotalSteps(totalSteps)
```

#### Parameters

* _totalSteps_: the maximum step count allowed for the motor.

#### Example

```
#include <Arduino_EMBRYO_2.h>

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

#### Returns

The maximum step count allowed for the motor.

#### Example

```
#include <Arduino_EMBRYO_2.h>

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
axis.setLength(maxLength)
```
#### Parameters

* _maxLength_: the maximum length of the linear axis in centimeters.

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.setLenght(45);
}
void loop() {}
```

#### See also

-   [getLength()](#getLength)
-   [moveDistance()](#moveDistance)
-   [setPosition()](#setPosition)

### `getLength()`

Gets the length of the robot axis in centimeters.

#### Syntax

```
axis.getLength()
```
#### Returns

The maximum length of the liner axis in centimeters.

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  axis.setLenght(45);
  int length = axis.getLenght();
  Serial.println("Length: " + String(length));
}
void loop() {}
```

#### See also

-   [moveDistance()](#moveDistance)
-   [setLength()](#setLength)
-   [setPosition()](#setPosition)

### `checkInputs()`

Verifies and print the current boolean values of the inputs.

#### Syntax

```
axis.checkInputs()
```

#### Example

```
#include <Arduino_EMBRYO_2.h>

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

## Embryo Class Methods

### `Embryo()`

This function creates an instance of Embryo Class to control two axis of EMBRYO 2. Use it at the top of your sketch, above `setup()` and `loop()` and after the two axis StepMotor instance.

#### Syntax

```
Embryo(axisX, axisY, startPin, emergencyStopPin);
```

#### Parameters

-   axisX: an object from StepMotor class
-   axisY: an object form StepMotor class
-   startPin: Pin connected to initialization button
-   emergencyStopPin: Pin connected to emergency stop button

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axisX(1, A5, 5, 6, 3, 4, A1, A2, 2, 12);
StepMotor axisY(2, A5, 10, 11, 8, 9, A3, A4, 2, 12);

Embryo robot(axisX, axisY, 2, 12);


void setup() {}
void loop() {}
```

#### See also

-   [begin()](#begin)
-   [end()](#end)
-   [start()](#start)

### `begin()`

Configures inputs pins, outputs pins, and interruptions pins of both axis.

#### Syntax

```
robot.begin()
```

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axisX(1, A5, 5, 6, 3, 4, A1, A2, 2, 12);
StepMotor axisY(2, A5, 10, 11, 8, 9, A3, A4, 2, 12);

Embryo robot(axisX, axisY, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  robot.begin();   // Configures pins of the two axis.
}
void loop() {}
```

#### See also

-   [end()](#end)
-   [start()](#start)
-   [ready()](#ready)

### `end()`

Disables both axis and sets them as not ready. This function is associated with the Emergency Stop Button ISR.

#### Syntax

```
robot.end()
```

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axisX(1, A5, 5, 6, 3, 4, A1, A2, 2, 12);
StepMotor axisY(2, A5, 10, 11, 8, 9, A3, A4, 2, 12);

Embryo robot(axisX, axisY, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  robot.begin();   // Initializes two axis and configures interruptions pins
  robot.end();     // Disable Arduino EMBRYO 2
}
void loop() {}
```

#### See also

-   [begin()](#begin)
-   [start()](#start)
-   [ready()](#ready)

### `start()`

Initializes the Arduino EMBRYO 2 with two axis. Enables and starts two motors, then the motors are set as ready and does the homing procedure of both of them. This function is associated with the Start Button ISR.

#### Syntax

```
robot.start()
```

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axisX(1, A5, 5, 6, 3, 4, A1, A2, 2, 12);
StepMotor axisY(2, A5, 10, 11, 8, 9, A3, A4, 2, 12);

Embryo robot(axisX, axisY, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  robot.begin();   // Initializes two axis and configures interruptions pins
  robot.start();   // Enable the axis and does the homing procedure
}
void loop() {}
```

#### See also

-   [begin()](#begin)
-   [end()](#end)
-   [ready()](#ready)

### `setLengthXY()`

Sets the length of bth of the robot axis in centimeters.

#### Syntax

```
robot.setLength(lengthX, lengthY)
```
#### Parameters

* _lengthX_: the maximum length of the X-axis in centimeters.
* _lengthY_: the maximum length of the Y-axis in centimeters.

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axis(1, A5, 5, 6, 3, 4, A2, A1, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};
  robot.setLenght(45, 25);
}
void loop() {}
```

#### See also

-   [toPositionXY()](#toPositionXY)

### `toPositionXY()`

Moves the robot carriages to a specified XY position in centimeters along the axis. Zero is the motor home position and max position is in the axis end far from the motor home and is equal to the length of each axis.

#### Syntax

```
robot.toPositionXY(positionX, positionY)
```

#### Parameters

* _positionX_: X-axis position in centimeters with home equals to zero
* _positionY_: Y-axis position in centimeters with home equals to zero

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axisX(1, A5, 5, 6, 3, 4, A1, A2, 2, 12);

StepMotor axisY(2, A5, 10, 11, 8, 9, A3, A4, 2, 12);

Embryo robot(axisX, axisY, 2, 12);

unsigned int positionX = 0, positionY = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  robot.begin();

  Serial.println("Press the Start Button to start the machine");
  while(!robot.ready());
}
void loop() {
  Serial.println("Enter the number of the position for X-axis: ");
  while((Serial.available() <= 0)){};
  positionX = Serial.parseInt(); 

  
  Serial.println("Enter the number of the position for Y-axis: ");
  while((Serial.available() <= 0)){};
  positionY = Serial.parseInt(); 

  robot.toPositionXY(positionX, positionY); 
}
```

#### See also

-   [setLengthXY()](#setLengthXY)
-   [toStepXY()](#toStepXY)

### `toStepXY()`

Moves the EMBRYO 2 educational modular machine the X and the Y carriages to a specified step count in each axis. Zero is in the motor home position and max number of steps is in the axis end far from the motor home.

#### Syntax

```
robot.toStepXY(stepX, stepY)
```
#### Parameters

* _stepX_: X-axis position in step counts with home equals to zero
* _stepY_: Y-axis position in step counts with home equals to zero

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axisX(1, A5, 5, 6, 3, 4, A1, A2, 2, 12);

StepMotor axisY(2, A5, 10, 11, 8, 9, A3, A4, 2, 12);

Embryo robot(axisX, axisY, 2, 12);

unsigned long stepNumX = 0, stepNumY = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  robot.begin();

  Serial.println("Press the Start Button to start the machine");
  while(!robot.ready());
}
void loop() {
  Serial.println("Enter the number of the step for X-axis: ");
  while((Serial.available() <= 0)){};
  stepNumX = Serial.parseInt(); 

  
  Serial.println("Enter the number of the step for Y-axis: ");
  while((Serial.available() <= 0)){};
  stepNumY = Serial.parseInt(); 

  robot.toStepXY(stepNumX, stepNumY);
}
```

#### See also

-   [toPositionXY()](#toPositionXY)

### `drawLine()`

Draws a line with both axis of EMBRYO 2.

#### Syntax

```
robot.drawline(initialPositionX,
               initialPositionY,
               finalPositionX,
               finalPositionY)
```
#### Parameters

* _initialPositionX_: line initial X-axis position.
* _initialPositionY_: line initial Y-axis position.
* _finalPositionX_: line final X-axis position.
* _finalPositionY_: line final Y-axis position.

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axisX(1, A5, 5, 6, 3, 4, A1, A2, 2, 12);

StepMotor axisY(2, A5, 10, 11, 8, 9, A3, A4, 2, 12);

Embryo robot(axisX, axisY, 2, 12);

void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  robot.begin();

  robot.setLengthXY(45, 38);
  
  Serial.println("Press the Start Button to start the machine");
  while(!robot.ready());
  
  Serial.println("Moving the robot to the initial XY position ...");
  
  robot.toPositionXY(5, 5);

  Serial.println("Press the forward button to continue ...");
}
void loop() {
  if(axisX.readBtnForward()){
    robot.drawLine(5,5,5,10);
  }
}
```

#### See also

-   [toStepXY()](#toStepXY)
-   [toPositionXY()](#toPositionXY)

### `drawArc()`

Draws an arc with both axis of EMBRYO 2.

#### Syntax

```
robot.drawArc(centerX,
              centerY,
              radius,
              initialAngle,
              finalAngle)
```
#### Parameters

* _centerX_: X-axis coordinates of the arc center position in centimeter.
* _centerY_: Y-axis coordinates of the arc center position in centimeter.
* _radius_: arc radius size in centimeters.
* _initialAngle_: initial angle of the arc.
* _finalAngle_: initial angle of the arc.

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axisX(1, A5, 5, 6, 3, 4, A1, A2, 2, 12);

StepMotor axisY(2, A5, 10, 11, 8, 9, A3, A4, 2, 12);

Embryo robot(axisX, axisY, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};

  robot.begin();

  robot.setLengthXY(45, 25);
  
  Serial.println("Press the Start Button to start the machine");
  while(!robot.ready()); 
  
  Serial.println("Moving the robot to the initial XY position ...");

  robot.toPositionXY(15, 15);
  
  Serial.println("Press the forward button to continue ...");
}
void loop() {
  if(axisX.readBtnForward()){
    robot.drawArc(15, 15, 5, 20, 180);
  }
}
```

#### See also

-   [toStepXY()](#toStepXY)
-   [drawCircle()](#drawCircle)

### `drawCircle()`

Draws a circle with both axis of EMBRYO 2.

#### Syntax

```
robot.drawCircle(centerX,
              centerY,
              radius)
```
#### Parameters

* _centerX_: X-axis coordinates of the circle center position in centimeter.
* _centerY_: Y-axis coordinates of the circle center position in centimeter.
* _radius_: circle radius size in centimeters.

#### Example

```
#include <Arduino_EMBRYO_2.h>

StepMotor axisX(1, A5, 5, 6, 3, 4, A1, A2, 2, 12);

StepMotor axisY(2, A5, 10, 11, 8, 9, A3, A4, 2, 12);

Embryo robot(axisX, axisY, 2, 12);

void setup() {
  Serial.begin(9600);
  while (!Serial) {};

  robot.begin();

  robot.setLengthXY(45, 25);
  
  Serial.println("Press the Start Button to start the machine");
  while(!robot.ready()); 
  
  Serial.println("Moving the robot to the initial XY position ...");

  robot.toPositionXY(15, 15);
  
  Serial.println("Press the forward button to continue ...");
}
void loop() {
  if(axisX.readBtnForward()){
    robot.drawCircle(15, 15, 5);
  }
}
```

#### See also

-   [toStepXY()](#toStepXY)
-   [drawCircle()](#drawCircle)