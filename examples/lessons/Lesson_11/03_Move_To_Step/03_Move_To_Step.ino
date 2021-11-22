#include "Embryo_II.h"
/******* I N I T I A L    D E F I N E S ********/
#define X_AXIS      1

/*C O N S T A N T S   A N D   V A R I A B L E S*/
const int enablePin = A5;      // Enable Pin
const int DirPin = 5;          // Direction Pin X-axis
const int PulPin = 6;          // Step Pin X-axis
const int BackwardPin = A1;    // Backward Button X-axis
const int ForwardPin  = A2;    // Forward Button X-axis
const int startPin = 2;        // Start Button
const int emergencyPin  = 12;  // Emergency Button
const int HomeEndstop = 3;     // Home endstop X-axis
const int FarEndstop = 4;      // Far From Home endstop X-axis
long stepNum = 0;

// Construct object, Embryo(Axis, Enable Pin, Direction Pin, Pulse Pin, Endstop Home, Endstop Far, Forward Button, Backward Button, Start Button, Emergency Stop Button)
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
  Serial.begin(115200);
  while (!Serial) {};
  axis.begin();
  Serial.println("Press the Start Button to start the machine.");
  while(!axis.ready());  // Wait for Start button to be pressed
                         // The start button is attached to the interrupt
                         // service routine that enables the motor and runs
                         // the homing procedure
  Serial.println("Move the axis between to minimum step (zero, 0) and the total step (" + String(String(axis.getTotalSteps())) + ")");
}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Enter the number of the step: ");
  while((Serial.available() <= 0)){};
  stepNum = Serial.parseInt();
  Serial.println("Current step before: " + String(axis.getStep()));
  axis.toStep(stepNum);
  Serial.println("Current steps after: " + String(axis.getStep()));
}