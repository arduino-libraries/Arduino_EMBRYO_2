#include "Embryo_II.h"
/******* I N I T I A L    D E F I N E S ********/
#define X_AXIS      1

/*C O N S T A N T S   A N D   V A R I A B L E S*/
const int enablePin = A5;      // Enable Pin
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
StepMotor axis(X_AXIS,
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
  // Configure and start Serial Communication
  Serial.begin(115200); 
  while (!Serial) {};
  axis.begin(); // Configure inputs pins, outputs pins and interuptions pins
  axis.checkInputs(); // Verify the boolean value of the axis inputs and print in the serial monitor
} 

void loop() {
  // put your main code here, to run repeatedly:
  if(axis.readBtnForward() == 1)
    Serial.println("Forward Button was pressed!");
  if(axis.readBtnBackward() == 1)
    Serial.println("Backward Button was pressed!");
  if(axis.readEndstopHome() == 1)
    Serial.println("Endstop Home was pressed!");
  if(axis.readEndstopFar() == 1)
    Serial.println("Endstop Far was pressed!");
  if(axis.readBtnEmergencyStop() == 0)
    // The emergency stop buuton is attached in the interrupt service routine
    // So when you clik the button, you will the Emergency message will be printed too
    Serial.println("Emergency Stop Button was pressed!");
  if(axis.readBtnInit() == 1)
    Serial.println("Init Button was pressed!");
}
