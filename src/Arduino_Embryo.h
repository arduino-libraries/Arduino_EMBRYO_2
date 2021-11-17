/*
  This file is part of the Embryo II library.
  Copyright (c) 2021 Arduino SA. All rights reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
    
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _Arduino_Embryo_h
#define _Arduino_Embryo_h

#include "Arduino.h"

class StepMotor {
 public:
  StepMotor(uint8_t id, uint8_t enablePin, uint8_t directionPin, uint8_t pulsePin, uint8_t homePin, uint8_t farPin, uint8_t btnForward, uint8_t btnBackward, uint8_t btnInit, uint8_t btnEmergencyStop);

  // Control motor
  void begin(void);
  void init(void);
  void initWithoutHoming(void);
  void end(void);
  void start(void);
  void stop(void);
  bool homing(void);
  bool ready(void) const;
  void enableInterrupt(void);
  void disableInterrupt(void);
  // Machine movement and commands
  void moveForward(void);
  void moveBackward(void);
  void moveSteps(int32_t numSteps);
  void moveDistance(int32_t distance);
  void setStep(int32_t step);
  void setPosition(int32_t position);
  void setSpeed(int32_t speed = 200);
  uint32_t getStep(void);
  uint32_t getPosition(void);
  // Read inputs
  bool readBtnForward(void);
  bool readBtnBackward(void);
  bool readEndstopHome(void);
  bool readEndstopFar(void);
  bool readBtnInit(void);
  bool readBtnEmergencyStop(void);
  void checkInputs(void);
  // Set and Read steps
  bool setTotalSteps(uint32_t totalSteps);
  uint32_t getTotalSteps(void);
  // Structure
  void setLength(uint8_t maxLength);

private:
  /* ID */
  uint8_t _id;
  /* Inputs */
  uint8_t _btnForward;
  uint8_t _btnBackward;
  uint8_t _endstopHome;
  uint8_t _endstopFar;
  uint8_t _btnInit;
  uint8_t _btnEmergencyStop;
  /* Outputs */
  uint8_t _enable_pin;
  uint8_t _direction_pin;
  uint8_t _pulse_pin;
  /* Defaul Structure Values */
  byte _homeDir = HIGH;    // Set home direction
  byte _farDir = LOW;      // Set far from home direction
  bool _homingOK = false;  // Flag control
  uint8_t _maxLength = 45;    // Length of the axis
  
  // Machine movement variables
  byte _motorPulseState = LOW;  // goes between HIGH and LOW every timerSpeed uS
  uint32_t _minSpeed = 25000;
  uint32_t _maxSpeed = 200;
  uint32_t _timerSpeed = 200;  // limited between _minSpeed and _maxSpeed, uSeconds
  uint32_t _previousMicro;
  uint32_t _currentMicro;
  // Steps
  uint32_t _totalSteps = 0;
  uint32_t _currentStep = 0;
  // Control initialization
  bool volatile _ready = false;

  // Motor functions
  void pulseMotor(void);
  void enableMotor(void);
  void disableMotor(void);
  void setHomeDirection(void);
  void setFarDirection(void);
  // Interrupt
  static StepMotor* _thisMotor;
  static void initISR(void);
  static void stopISR(void);
};


#endif
