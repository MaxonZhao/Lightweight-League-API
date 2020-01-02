#ifndef MOTOR_H
#define MOTOR_H

#include <Wire.h>
#include "Value.h"
#include <Math.h>
#include "Sensor.h"

//variable declearation

#define STOP 360
#define MAX_SPEED 89

static int PWM[5] = {0,9,10,11,12};// pin number of motor 1,2,3,4's pwm
static int DIR[5] = {0,25,26,27,28};// pin number of motor 1,2,3,4's direction
static int motor_dir[5] = {0,MOTOR_1_DIR,MOTOR_2_DIR,MOTOR_3_DIR,MOTOR_4_DIR};

// P1 : black 9
// D1 : Red 25
// P2 : White 10 
// D2 : Yellow 26 
// GND: Green 2




int getTarget();
void setTarget(int newTarget);
int getSpeed();
void setSpeed(int newSpeed);
int getDir();
void setDir(int newDirection);
void setAngleThres(int t);

void move();
int sinLaw(int degree1,int degree2,int speed2);
int getAngleDif(int target);
void setMotor(int which,int motorSpeed);
void setMotors(int speed1, int speed2, int speed3, int speed4);
void setupMotors();
double toRadian(int);
void motorTest();

#endif
