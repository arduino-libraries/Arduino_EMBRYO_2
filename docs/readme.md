# APA102 RBG LEDs library

This library allows an Arduino board to control the stepper motor of a linear axis for **Embryo II** robot. This robot axis are controlled with the motor pins and the panel buttons.

To use this library:

```
#include <Embryo.h>

StepMotor axis(AXIS_ID,
               enablePin,
               DirectionPin,
               PulsePin,
               HomeEndstop,
               FarEndstop,
               ForwardPin,
               BackwardPin,
               initPin,
               emergencyStopPin);
```

## Circuit

TODO: Draw the circuit, because it uses a lot of pins.

## Examples
