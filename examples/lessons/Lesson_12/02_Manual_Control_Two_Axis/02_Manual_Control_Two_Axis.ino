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

// Construct object, StepMotor(Axis, Enable Pin, Direction Pin, Pulse Pin, Endstop Home, Endstop Far, Forward Button, Backward Button, Start Button, Emergency Stop Button)
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

Embryo robot(axisX, axisY);

void setup() {
  Serial.begin(115200);
  while (!Serial) {};
  axisX.begin();
  axisY.begin();
  Serial.println("Send any key to serial ...");
  while((Serial.available() <= 0)){};
  axisX.start();
  axisY.start();
}
void loop() {
  // put your main code here, to run repeatedly:
  // Check the forward button signal
  if(axisX.readBtnForward() == HIGH)
    axisX.moveForward();
  
  // Check the forward button signal
  if(axisY.readBtnForward() == HIGH)
    axisY.moveForward();

  // Check the forward button signal
  if(axisX.readBtnBackward() == HIGH)
    axisX.moveBackward();

  // Check the forward button signal
  if(axisY.readBtnBackward() == HIGH)
    axisY.moveBackward();
}
