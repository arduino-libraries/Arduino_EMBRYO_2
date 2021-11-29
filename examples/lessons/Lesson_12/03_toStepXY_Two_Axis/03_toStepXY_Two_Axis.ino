#include "Arduino_Embryo.h"
/******* I N I T I A L    D E F I N E S ********/
#define X_AXIS      1
#define Y_AXIS      2

/*C O N S T A N T S   A N D   V A R I A B L E S*/
const int enablePin = A5;      // Enable Pin
const int DirPinX = 5;         // Direction Pin X-axis
const int PulPinX = 6;         // Step Pin X-axis
const int HomeEndstopX = 3;    // Home endstop X-axis
const int FarEndstopX = 4;     // Far From Home endstop X-axis
const int BackwardPinX = A1;   // Backward Button X-axis
const int ForwardPinX  = A2;   // Forward Button X-axis

const int DirPinY = 10;        // Direction Pin Y-axis
const int PulPinY = 11;        // Step Pin Y-axis
const int HomeEndstopY = 8;    // Home endstop Y-axis
const int FarEndstopY = 9;     // Far From Home endstop Y-axis
const int BackwardPinY = A3;   // Backward Button Y-axis
const int ForwardPinY  = A4;   // Forward Button Y-axis

const int startPin = 2;        // Start Button
const int emergencyPin  = 12;  // Emergency Button

unsigned long stepNumX = 0, stepNumY = 0;

// Construct object, Embryo(Axis, Enable Pin, Direction Pin, Pulse Pin, Endstop Home, Endstop Far, Forward Button, Backward Button, Start Button, Emergency Stop Button)
StepMotor axisX(X_AXIS,
                enablePin,
                DirPinX,
                PulPinX,
                HomeEndstopX,
                FarEndstopX,
                ForwardPinX,
                BackwardPinX,
                startPin,
                emergencyPin);

StepMotor axisY(Y_AXIS,
                enablePin,
                DirPinY,
                PulPinY,
                HomeEndstopY,
                FarEndstopY,
                ForwardPinY,
                BackwardPinY,
                startPin,
                emergencyPin);

Embryo robot(&axisX, &axisY, startPin, emergencyPin);

void setup() {
  Serial.begin(115200);
  while (!Serial){};
  robot.begin();
  Serial.println("Press the Start Button to start the machine");
  while(!robot.ready()); // Wait for Start button to be pressed
                         // The start button is attached to the interrupt
                         // service routine that enables the motor and runs
                         // the homing procedure
}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Enter the number of the step for X-axis: ");
  while((Serial.available() <= 0)){};
  stepNumX = Serial.parseInt();
  Serial.println("Enter the number of the step for Y-axis: ");
  while((Serial.available() <= 0)){};
  stepNumY = Serial.parseInt();
  Serial.println("Current step before - X-axis: " + String(axisX.getStep()));
  Serial.println("Current step before - Y-axis: " + String(axisY.getStep()));
  robot.toStepXY(stepNumX, stepNumY);
  Serial.println("Current steps after - X-axis: " + String(axisX.getStep()));
  Serial.println("Current steps after - Y-axis: " + String(axisY.getStep()));
}
