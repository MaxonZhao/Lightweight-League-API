#include "Player.h"

void player(){
  while(1){
    int eyeValue = getEyeValue();
    
    if(eyeValue>20){
      int eyePort = getEyePort();
      int aroundSpeed = 85;
      if(eyePort<8){
        eyePort--;
      }
      else{
        eyePort-=2;
      }
      eyePort%=12;
      int minBallRange=20;
      //robot1: 250, robot2: 230
      int maxBallRange=230;
      double minShift = 5;
      double maxShift = 60;
      double finalShift;
      int ballRange = eyeValue;
      int ballDirection=eyePort*30;
      int d;
      int uBack = getBackDistanceCM();
      finalShift = (ballRange-minBallRange)*(maxShift)/(maxBallRange-minBallRange)+minShift;
      finalShift = constrain(finalShift,0,90);
      if(ballDirection<=180){
        finalShift=finalShift*constrain(ballDirection,0,90)/90;
        d=(int)(ballDirection+finalShift)%360;
        if(uBack<30){
          d = constrain(d,0,130);
        }
        else if (uBack<40) aroundSpeed = 60;

      }
      else{
        finalShift=finalShift*constrain(360-ballDirection,0,90)/90;
        d=(int)(ballDirection-finalShift)%360;
        if(uBack<30){
          d = constrain(d,290,359);
        }
        else if (uBack<40) aroundSpeed = 60;
      }

      targetStrategy(ballDirection);
      setDir(d);
      setSpeed(85);
    }
    else{
      
      backPosition();
    }
    whiteLine();
    Serial.println(getRightDistanceCM());
    move();
  }
}

void targetStrategy(int ballDir){
  int uLeft = getLeftDistanceCM();
  int uRight = getRightDistanceCM();
  int uBack = getBackDistanceCM();
  if((ballDir<100||ballDir>260)&&getTarget()==0&&uLeft+uRight>HORIZONTAL_BLOCK_RANGE&&uBack>50){
    if(uLeft<uRight){//using Left
      if(uLeft<60){
        setTarget(30);
        setAngleThres(60);
      }
      
    }
    else{//using right
      if(uRight<60){
        setTarget(330);
        setAngleThres(60);
      }
    }
  }
}

long lastWhiteTime = -5000;
int whiteTime = 400;
void whiteLine(){
  if(whiteDetected()){
    lastWhiteTime=millis();
  }
  if(millis()-lastWhiteTime<whiteTime){
    backPosition();
  }
}

void setupPlayer(){
  Serial.begin(9600);
  setupMotors();
  setupEye();
  getLightThres();
}
