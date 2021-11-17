#include "Embryo_II.h"
/******* I N I T I A L    D E F I N E S ********/
#define X_AXIS      1

/*C O N S T A N T S   A N D   V A R I A B L E S*/
const int enablePin = A5;       // Enable Pin
const int DirPin = 5;          // Direction Pin X-axis
const int PulPin = 6;          // Step Pin X-axis
const int BackwardPin = A1;    // Backward Button X-axis
const int ForwardPin  = A2;    // Forward Button X-axis
const int initPin = 2;         // Init Button
const int emergencyPin  = 12;  // Emergency Button
const int HomeEndstop = 3;     // Home endstop X-axis
const int FarEndstop = 4;      // Far From Home endstop X-axis
long steps = 0;

// Construct object, Embryo(Axis, Enable Pin, Direction Pin, Pulse Pin, Endstop Home, Endstop Far, Forward Button, Backward Button, Init Button, Emergency)
StepMotor motor(X_AXIS,
                enablePin,
                DirPin,
                PulPin,
                HomeEndstop,
                FarEndstop,
                ForwardPin,
                BackwardPin,
                initPin,
                emergencyPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);       // Configure and start Serial Communication
  while (!Serial) {};         // Wait to open the serial monitor
  motor.begin();              // Configure inputs pins, outputs pins and interuptions pins
  motor.startWithoutHoming(); // Initialize the motor without homing procedure, detached
                              // interruptions pins and configures endstops as OUTPUT
                              // Use this function only with the motor outside the axis
  
  Serial.println("To start, send any key to serial ...");
  // Without this instruction the motor will move after the upload (It is dangerous)
  while((Serial.available() <= 0)){};
  motor.setTotalSteps(50000); // Set the max step of the motor
  Serial.println("Motor moves.");
  motor.moveSteps(20000); // Motor moves
  motor.pause();          // Pause the motor
  Serial.println("Motor does not move.");
  motor.moveSteps(50); // Motor does not move
  delay(2000);
  motor.play();       // Enable motor
  Serial.println("Motor moves.");
  motor.moveSteps(-15000); // Motor moves again
}
void loop() {}
