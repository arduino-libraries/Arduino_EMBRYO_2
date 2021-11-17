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

#include <Arduino.h>
#include "Arduino_Embryo.h"
// Interrupt
StepMotor* StepMotor::_thisMotor = 0;

StepMotor::StepMotor(uint8_t id, uint8_t enablePin, uint8_t directionPin, uint8_t pulsePin, uint8_t homePin, uint8_t farPin, uint8_t btnForward, uint8_t btnBackward, uint8_t btnInit, uint8_t btnEmergencyStop)
{
  /* Identification */
  _id = id;
  /* Inputs */
  _btnForward = btnForward;
  _btnBackward = btnBackward;
  _endstopHome = homePin;
  _endstopFar = farPin;
  _btnInit = btnInit;
  _btnEmergencyStop = btnEmergencyStop;
  /* Outputs */
  _enable_pin = enablePin;
  _direction_pin = directionPin;
  _pulse_pin = pulsePin;

  // Interrupt
  _thisMotor = this;
}

void StepMotor::begin(void){
  uint8_t _inputPins[6] = {_btnForward, _btnBackward, _btnInit, _btnEmergencyStop, _endstopHome, _endstopFar};
  uint8_t _outputPins[3] = {_enable_pin, _direction_pin, _pulse_pin};
  uint8_t _numPinsInput = sizeof(_inputPins) / sizeof(_inputPins[0]);
  uint8_t _numPinsOutput = sizeof(_outputPins) / sizeof(_outputPins[0]);
  // Declare inputs and outputs as such
  for(int _i = 0; _i < _numPinsInput; _i++)
    pinMode(_inputPins[_i], INPUT);
    
  for(int _i = 0; _i < _numPinsOutput; _i++)
    pinMode(_outputPins[_i], OUTPUT);

  disableMotor();

  //Configure Interruptions
  attachInterrupt(digitalPinToInterrupt(_btnInit), initISR, RISING);
  attachInterrupt(digitalPinToInterrupt(_btnEmergencyStop), stopISR, RISING);

  Serial.println("Motor " + String(_id) + " is ON!");
}

void StepMotor::init(void){
  _ready = true;
  start();
  _ready = homing();
}

void StepMotor::initWithoutHoming(void){
  _ready = true;
  start();
}

void StepMotor::end(void){
  disableMotor();
  Serial.println("Stopped axis " + String(_id));
  _ready = false;
}


void StepMotor::start(void){
  if(!_ready)  Serial.println("Motor is not initialized");
  else enableMotor();
}

void StepMotor::stop(void){
  disableMotor();
}

bool StepMotor::homing(void){
  Serial.println ("Homing axis " + String(_id));
//  enableMotor();
  setFarDirection();
  while(!readEndstopFar()){
    pulseMotor();
  }
  Serial.println("Axis " + String (_id) + " - Endstop Far was found.");
  _totalSteps = 0;

  setHomeDirection();
  while(!readEndstopHome()){
    pulseMotor();
    _totalSteps++;
  } 
  Serial.println("Axis " + String (_id) + " - Endstop Home was found.");
  Serial.println("Axis " + String(_id) + " - Total steps = " + String(_totalSteps));

  _currentStep = 0;
  _homingOK = true;
  return _homingOK;
}

bool StepMotor::ready(void) const{
  return _ready;
}

void StepMotor::enableInterrupt(void){
  attachInterrupt(digitalPinToInterrupt(_btnInit), initISR, RISING);
  attachInterrupt(digitalPinToInterrupt(_btnEmergencyStop), stopISR, RISING);
}

void StepMotor::disableInterrupt(void){
  detachInterrupt(digitalPinToInterrupt(_btnEmergencyStop));
  detachInterrupt(digitalPinToInterrupt(_btnInit));
}

void StepMotor::initISR(void){
  if(_thisMotor != 0)
    _thisMotor->init();
}

void StepMotor::stopISR(void){
  Serial.println("Emergency!");
    _thisMotor->end();
}

void StepMotor::enableMotor(void){
  digitalWrite(_enable_pin, LOW);  // Enable Motors
}

void StepMotor::disableMotor(void){
  digitalWrite(_enable_pin, HIGH);  // disable Motors
}

void StepMotor::pulseMotor(void){
  // These three lines result in 1/2 step:
  _currentMicro = micros();
  if (_currentMicro - _previousMicro >= _timerSpeed){
    _previousMicro = _currentMicro;
    _motorPulseState = !_motorPulseState;
    digitalWrite(_pulse_pin, _motorPulseState);
  }
}

void StepMotor::moveForward(void){
  if(!_ready) return;
  setFarDirection();
  if(!readEndstopFar()){
    pulseMotor();
    _currentStep++;
  } else {
    Serial.println("Axis " + String (_id) + " - Endstop Far was found.");
    _currentStep = _totalSteps;
  }
}

void StepMotor::moveBackward(void){
  if(!_ready) return;
  setHomeDirection();
  if(!readEndstopHome()){
    pulseMotor();
    _currentStep--;
  } else {
    Serial.println("Axis " + String (_id) + " - Endstop Home was found");
    _currentStep = 0;
  }
}

void StepMotor::moveSteps(int32_t numSteps){
  int32_t _absSteps = numSteps >= 0 ? numSteps : -(numSteps);
  if (_currentStep + numSteps >= 0 && numSteps + _currentStep <= _totalSteps) {
    for(uint32_t _st = 0; _st < _absSteps; _st++){
      if(numSteps > 0 && !readEndstopFar()) moveForward();
      if(numSteps < 0 && !readEndstopHome()) moveBackward();
    } 
  } else Serial.println("Value is out of range!");
}

void StepMotor::moveDistance(int32_t distance){
  uint32_t _step = map(distance, 0, _maxLength, 0, _totalSteps);
  moveSteps(_step);
}

void StepMotor::setStep(int32_t step){
  if (step >= 0 && step <= _totalSteps) {
    moveSteps(step - _currentStep); 
  } else Serial.println("Value is out of range!");
}

void StepMotor::setPosition(int32_t position){
  uint32_t _step = map(position, 0, _maxLength, 0, _totalSteps);
  setStep(_step);
}

void StepMotor::setSpeed(int32_t speed = 200){
  if(speed >= _maxSpeed || speed >= _minSpeed ) _timerSpeed = speed;
  else if(speed <= _maxSpeed) _timerSpeed = _maxSpeed;
  else if(speed >= _minSpeed) _timerSpeed = _minSpeed;
}

uint32_t StepMotor::getStep(void){
  return _currentStep;
}

uint32_t StepMotor::getPosition(void){
  float _position = ((float)_maxLength*getStep()/(float)_totalSteps)+0.5;
  return _position;
}

void StepMotor::setHomeDirection(void){
  digitalWrite(_direction_pin, _homeDir); // Set up home direction
}

void StepMotor::setFarDirection(void){
  digitalWrite(_direction_pin, _farDir); // Set up far from home direction
}

bool StepMotor::readBtnForward(void){
  return digitalRead(_btnForward);
}

bool StepMotor::readBtnBackward(void){
  return digitalRead(_btnBackward);
}

bool StepMotor::readBtnInit(void){
  return digitalRead(_btnInit);
}

bool StepMotor::readBtnEmergencyStop(void){
  return digitalRead(_btnEmergencyStop);
}

bool StepMotor::readEndstopHome(void){
  return digitalRead(_endstopHome);
}

bool StepMotor::readEndstopFar(void){
  return digitalRead(_endstopFar);
}

uint32_t StepMotor::getTotalSteps(void){
  return _totalSteps;
}

bool StepMotor::setTotalSteps(uint32_t totalSteps){
  _totalSteps = totalSteps;
}

void StepMotor::setLength(uint8_t maxLength){
  _maxLength = maxLength;
}

void StepMotor::checkInputs(void){
  // Default logic of the inputs
  uint8_t _defaultHomePress = 1;
  uint8_t _defaultFarPress = 1;
  uint8_t _defaultForwardPress = 1;
  uint8_t _defaultBackwardPress = 1;
  
  Serial.println();
  Serial.println("Make sure that all inputs are connected.");
  Serial.println("You don't need to press any button.");
  Serial.println("Please wait, I will check the machine inputs form axis " + String(_id));
  Serial.println(" -----------------------------------------------");
  Serial.println("|\t\tEndstop Home\t|  Endstop Far\t|");
  Serial.println("| Not Pressed:\t\t" + String(readEndstopHome()) + "\t|\t" + String(readEndstopFar()) + "\t|");
  Serial.println("| Pressed:\t\t" + String(!readEndstopHome()) + "\t|\t" + String(!readEndstopFar()) + "\t|");
  Serial.println(" -----------------------------------------------");
  uint8_t _currentHomePress = !readEndstopHome();
  uint8_t _currentFarPress = !readEndstopFar();
  
  Serial.println("In common inputs:");
  Serial.println(" ----------------------------------------------------------------------------------");
  Serial.println("|\t\tForward Button\t| Backward Button | Init Button\t| Emergency Button |");
  Serial.println("| Not Pressed:\t\t" + String(readBtnForward()) + "\t|\t " + String(readBtnBackward()) + "\t  |\t " + String(readBtnInit()) + "\t|\t " + String(readBtnEmergencyStop()) + "\t   |");
  Serial.println("| Pressed:\t\t" + String(!readBtnForward()) + "\t|\t " + String(!readBtnBackward()) + "\t  |\t "  + String(!readBtnInit()) + "\t|\t " + String(!readBtnEmergencyStop()) + "\t   |");
  Serial.println(" ----------------------------------------------------------------------------------");
  Serial.println("Press Enter to continue ...");
  uint8_t _currentForwardPress = !readBtnForward();
  uint8_t _currentBackwardPress = !readBtnBackward();
  uint8_t _key = '0';
  do{
    Serial.available() > 0 ? _key = Serial.read() : _key = '0';
  }while(_key != '\n');
  Serial.println("==============================");
  if(_currentHomePress != _defaultHomePress){
    Serial.println("The boolean values of ENDSTOP HOME are different from the expected values.");
    Serial.println("Your robot won't work properly :( ");
  } else Serial.println("ENDSTOP HOME is OK.");
  if(_currentFarPress != _defaultFarPress){
    Serial.println("The boolean values of ENDSTOP FAR are different from the expected values.");
    Serial.println("Your robot won't work properly :( ");
  } else Serial.println("ENDSTOP FAR is OK.");
  if(_currentForwardPress != _defaultForwardPress){
    Serial.println("The boolean values of FORWARD BUTTON are different from the expected values.");
    Serial.println("Your robot won't work properly :( ");
  } else Serial.println("FORWARD BUTTON is OK.");
  if(_currentBackwardPress != _defaultBackwardPress){
    Serial.println("The boolean values of BACKWARD BUTTON are different from the expected values.");
    Serial.println("Your robot won't work properly :( ");
  } else Serial.println("BACKWARD BUTTON is OK.");
}
