#include "Embryo_II.h"
/******* I N I T I A L    D E F I N E S ********/
#define X_AXIS        1
#define MIN_SPEED 25000
#define MAX_SPEED   200

/*C O N S T A N T S   A N D   V A R I A B L E S*/
const int enablePin = A5;      // Enable Pin
const int DirPin = 5;          // Direction Pin X-axis
const int PulPin = 6;          // Step Pin X-axis
const int BackwardPin = A1;    // Backward Button X-axis
const int ForwardPin  = A2;    // Forward Button X-axis
const int startPin = 2;        // Start Button
const int emergencyPin  = 12;  // Emergency Stop Button
const int HomeEndstop = 3;     // Home endstop X-axis
const int FarEndstop = 4;      // Far From Home endstop X-axis
long steps = 0;

int analogPin = A0;            // Potentiometer pin
int speedMotor = 200;          // Intial speed (Max speed = 200 and Min speed = 25000)

// Construct object, Embryo(Axis, Enable Pin, Direction Pin, Pulse Pin, Endstop Home, Endstop Far, Forward Button, Backward Button, Start Button, Emergency Stop Button)
StepMotor motor(X_AXIS,
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
  Serial.begin(115200);       // Configure and start Serial Communication
  while (!Serial) {};         // Wait to open the serial monitor
  motor.begin();              // Configure inputs pins, outputs pins and interuptions pins
  motor.startWithoutHoming(); // Initialize the motor without homing procedure, detached
                              // interruptions pins and configures endstops as OUTPUT
                              // Use this function only with the motor outside the axis
  
  Serial.println("To start, send any key to serial port ...");
  // Without this instruction the motor will move after the upload (It is dangerous)
  while((Serial.available() <= 0)){};
  Serial.println("Use the potentiometer to control the speed.");
}
void loop() {
  speedMotor = analogRead(analogPin);  // read the input pin
  speedMotor = map(speedMotor, 0, 1023, MIN_SPEED, MAX_SPEED);
  Serial.println(speedMotor);          // debug value
  motor.setSpeed(speedMotor);          // Define the motor speed
  // Verifies if the forward button is pressed
  if(motor.readBtnForward() == HIGH)
    motor.moveForward();  // Motor rotates clockwise
}
