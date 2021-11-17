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
  Serial.begin(115200);
  while (!Serial) {};
  motor.begin();
  Serial.println("Press Forward Button to start.");
  while(motor.readBtnForward() == 0){}
  motor.init(false);  // Initialize motor without homing procedure
  motor.homing();     // Does the home procedure
}
void loop() {
  Serial.println("Enter the number of steps: ");
  while((Serial.available() <= 0)){};
  steps = Serial.parseInt();
  Serial.println("Curentstep before: " + String(motor.getStep()));
  motor.moveSteps(steps);
  Serial.println("Curentstep after: " + String(motor.getStep()));
  Serial.read(); // Clean serial buffer  
}
