#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include "Hardware.h"
#include "Value.h"

#define ANALOG 998
#define JM 999
#define TCAADDR 0x70

//DISTANCE SENSOR
int getRawLeftDistance();
int getRawRightDistance();
int getRawFrontDistance();
int getRawBackDistance();

int getLeftDistanceCM();// centimetre distance
int getRightDistanceCM();
int getFrontDistanceCM();
int getBackDistanceCM();

//EYE
void setupEye();
int getEyeValue();
int getEyePort();

//COMPASS
int getCompass();
int getCompassRawValue();

//LIGHT
void getLightThres();
bool whiteDetected();
int getLightValue(int which);
int getLightValue1();
int getLightValue2();
int getLightValue3();
int getLightValue4();
int getLightValue5();
int getLightValue6();
int getLightValue7();
int getLightValue8();
int getLightValue9();

//TCA
void tcaselect(uint8_t i);



#endif
