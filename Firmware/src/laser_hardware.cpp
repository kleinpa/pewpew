#include <Arduino.h>
#include <Servo.h>

#include "laser_hardware.h"

// Pin configuration
const int pinServoR = 4;
const int pinServoI = 13;
const int pinServoEnable = 14;
const int pinLaser = 12;

int rRangeMin = -9000;
int rRangeMax = 9000;

int iRangeMin = -9000;
int iRangeMax = 9000;

int rServoMin = 600;
int rServoMax = 2500;

int iServoMin = 2200;
int iServoMax = 550;

Servo servoR;
Servo servoI;

void LaserHardware::begin() {
  servoR.attach(pinServoR);
  servoI.attach(pinServoI);
  pinMode(pinLaser, OUTPUT);
  pinMode(pinServoEnable, OUTPUT);
  digitalWrite(pinServoEnable, HIGH);
}

void LaserHardware::update() {
  digitalWrite(pinServoEnable, millis() < this->previousPositionTime + 400);
}

void LaserHardware::setPosition(int r, int i){
  int rr = map(r, rRangeMin, rRangeMax, rServoMin, rServoMax);
  int ii = map(i, iRangeMin, iRangeMax, iServoMin, iServoMax);

  servoR.writeMicroseconds(rr);
  servoI.writeMicroseconds(ii);

  if(rr != this->previousPositionR || ii != this->previousPositionI) {
    digitalWrite(pinServoEnable, HIGH);
    this->previousPositionTime = millis();
    this->previousPositionR = rr;
    this->previousPositionI = ii;
  }
}

void LaserHardware::setPower(int p) {
  analogWrite(pinLaser, constrain(p, 0, 256));
}
