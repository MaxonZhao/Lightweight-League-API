#include "Sensor.h"

// ============================================================ Ultrasonic

// ----------------------- Raw Ultrasonic Value


int eyeType = ANALOG;
int eyePortThres[14] = {27,54,82,108,136,163,191,220,248,275,303,330,360,385};


int getRawLeftDistance() 
{
	return analogRead(LEFT_DISTANCE_PIN);
}


int getRawRightDistance() 
{
	return analogRead(RIGHT_DISTANCE_PIN);
}

int getRawFrontDistance() 
{
	return analogRead(FRONT_DISTANCE_PIN);
}

int getRawBackDistance() 
{
	return analogRead(BACK_DISTANCE_PIN);

}

// ----------------------- Ultrasonic Value in centimeter

int getLeftDistanceCM() 
{
	return getRawLeftDistance()*LEFT_DISTANCE_CONVERT_RATIO;
}

int getRightDistanceCM()
{
  return getRawRightDistance()*RIGHT_DISTANCE_CONVERT_RATIO;
}

int getFrontDistanceCM()
{
	  return getRawFrontDistance()*FRONT_DISTANCE_CONVERT_RATIO;

}

int getBackDistanceCM()
{
	  return getRawBackDistance()*BACK_DISTANCE_CONVERT_RATIO;

}

// ============================================================ Compass
int getCompassRawValue()
{
	return analogRead(COMPASS_PIN);
}

// ----------------------- Return Comapss value in range (0,359)
int getCompass()
{
	return getCompassRawValue()*360.0/COMPASS_MAX_VALUE;
}

// ============================================================ Flame

int getLeftFlame()
{
	// TODO
	return 0;
} 

int getRightFlame()
{
	// TODO
	return 0;
}

// ----------------------- Return true if flame detects the ball

bool leftFlameHasBall()
{
	return getLeftFlame() > LEFT_FLAME_VALUE;
}

bool rightFlameHasBall()
{
	// todo
	return false;
}


//EYE

void initializeJMEye(int which)
{
  tcaselect(which);
  int i;
  Wire.begin();
  Wire.beginTransmission(0x01);
  Wire.write(0x0e);
  Wire.endTransmission();
  while(Wire.available() > 0)
    i = Wire.read();
    Serial.println("reading");
    Serial.println(i);
}

void setupEye(){
  if(eyeType==JM){
    initializeJMEye(0);
    initializeJMEye(1);
  }
}

// ============================================================ Eye
// Get eye port
// Output 1-14 (Degree 0 is 1, clockwise)
int JMEyeValue(int which){
  tcaselect(which);
  Wire.begin();
  Wire.beginTransmission(0x01);
  Wire.write(0x09);
  Wire.endTransmission();
  Wire.requestFrom(0x01,1);
  while(Wire.available()){
    int i = Wire.read();
    return i;
  }
}


int JMEyePort(int which){
  tcaselect(which);
  Wire.begin();
  Wire.beginTransmission(0x01);//address for compound eye
  Wire.write(0x08);
  Wire.endTransmission();
  Wire.requestFrom(0x01,1);
  while(Wire.available()){
    int i = Wire.read();
    return i;
  }
}

int getEyePort()
{
  if(eyeType==JM){
  	int leftValue = JMEyeValue(0);
  	int rightValue = JMEyeValue(1);
  
  	if( leftValue>rightValue ) 
  	{
  		return JMEyePort(1) + 7;
  	}
  	else 
  	{
  		return JMEyePort(0);
  	}
  }
  else{
    int portValue = analogRead(EYE_PORT_PIN);
    int port = -1;
    if(portValue<(eyePortThres[0]+eyePortThres[1])/2) port = 1;
    else if(portValue<(eyePortThres[1]+eyePortThres[2])/2) port = 2;
    else if(portValue<(eyePortThres[2]+eyePortThres[3])/2) port = 3;
    else if(portValue<(eyePortThres[3]+eyePortThres[4])/2) port = 4;
    else if(portValue<(eyePortThres[4]+eyePortThres[5])/2) port = 5;
    else if(portValue<(eyePortThres[5]+eyePortThres[6])/2) port = 6;
    else if(portValue<(eyePortThres[6]+eyePortThres[7])/2) port = 7;
    else if(portValue<(eyePortThres[7]+eyePortThres[8])/2) port = 8;
    else if(portValue<(eyePortThres[8]+eyePortThres[9])/2) port = 9;
    else if(portValue<(eyePortThres[9]+eyePortThres[10])/2) port = 10;
    else if(portValue<(eyePortThres[10]+eyePortThres[11])/2) port = 11;
    else if(portValue<(eyePortThres[11]+eyePortThres[12])/2) port = 12;
    else if(portValue<(eyePortThres[12]+eyePortThres[13])/2) port = 13;
    else port = 14;

    return (port+6)%14+1;
  }

}


void tcaselect(uint8_t i) {
  if (i > 7) return;
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

// Get eye port
// Return max value among two eye values
int getEyeValue()
{
  if(eyeType == JM){
  	int leftValue = JMEyeValue(0);
  	int rightValue = JMEyeValue(1);
  
  	if( leftValue>rightValue ) 
  	{
  		return leftValue;
  	}
  	else 
  	{
  		return rightValue;
  	}
  }
  else if(eyeType == ANALOG){
    return analogRead(EYE_VALUE_PIN);
  }
}

//LIGHT

const int LIGHT_PINS[9] = {LIGHT_PIN_1,LIGHT_PIN_2,LIGHT_PIN_3,LIGHT_PIN_4,LIGHT_PIN_5,LIGHT_PIN_6
,LIGHT_PIN_7,LIGHT_PIN_8,LIGHT_PIN_9};
int lightThres[LIGHT_NUM] = {140,120,140,135,145,150,160};
const int gap = 25;

bool whiteDetected(){

  for(int i=0; i<LIGHT_NUM; i++){
    int lightValue = getLightValue(i+1);
    if(lightValue<lightThres[i]) return true;
  }
  return false;
}

void getLightThres(){
  Serial.println("getting grey scale threshold...\nIt will run for 5 seconds");
  
  for(int i=0; i<LIGHT_NUM; i++){//reset threshold
      lightThres[i]=999;
  }

  delay(500);
  long startTime = millis();
  while(millis()-startTime<5000){//delete startTime portion when button is installed
    
    for(int i=0; i<LIGHT_NUM; i++){
      int lightValue = getLightValue(i+1);
      if(lightValue<lightThres[i]){ 
        lightThres[i]=lightValue;
      }
      Serial.print(i);
      Serial.print(": ");
      Serial.println(lightValue);      
    }
    Serial.println();
  }

  
  Serial.println("\nthresholds:");//print out thresholds
  for(int i=0; i<LIGHT_NUM; i++){
    lightThres[i]-=gap;
    Serial.print(i);
    Serial.print(": ");
    Serial.println(lightThres[i]);
  }

  delay(1000);
}

int getLightValue(int which){//1~9
  return analogRead(LIGHT_PINS[which-1]);//0~8
}

int getLightValue1(){
  return analogRead(LIGHT_PIN_1);
}
int getLightValue2(){
  return analogRead(LIGHT_PIN_2);
}
int getLightValue3(){
  return analogRead(LIGHT_PIN_3);
}
int getLightValue4(){
  return analogRead(LIGHT_PIN_4);
}
int getLightValue5(){
  return analogRead(LIGHT_PIN_5);
}
int getLightValue6(){
  return analogRead(LIGHT_PIN_6);
}
int getLightValue7(){
  return analogRead(LIGHT_PIN_7);
}
int getLightValue8(){
  return analogRead(LIGHT_PIN_8);
}
int getLightValue9(){
  return analogRead(LIGHT_PIN_9);
}
