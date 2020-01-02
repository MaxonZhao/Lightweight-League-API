#include "Motor.h"

//----------------------------------------------------------------Motion functions

int angleThres = 40;

//struct
struct moveType{
  int speed;
  int direction;
  int target;
};
moveType motion;

int getTarget() {
  return motion.target;
}
void setTarget(int newTarget){
  motion.target = newTarget;
}

int getSpeed() {
  return motion.speed;
}

void setSpeed(int newSpeed){
  motion.speed = newSpeed;
}

int getDir() {
  return motion.direction;
}

void setDir(int newDirection){
  motion.direction = newDirection;
}

void setAngleThres(int t){
  angleThres = t;
}


//----------------------------------------------------------------motors

#define alpha 50
void move(){
  int d = motion.direction;
  int s = motion.speed;
  int targetAngle = motion.target;
  int degree1;
  int degree2;
  int slowerSpeed = s;
  int speed1;
  int speed2;
  int speed3;
  int speed4;
  int angleDif = getAngleDif(targetAngle);

    float u1 = (cos(toRadian(d))/(2*cos(toRadian(alpha))) - sin(toRadian(d))/(2*sin(toRadian(alpha))))*s;
    float u2 = (sin(toRadian(d))/(2*sin(toRadian(alpha))) + cos(toRadian(d))/(2*cos(toRadian(alpha))))*s;
    float ratio = 0; 
    if (u1 == 0 && u2 == 0) {
        u1 = 0;
        u2 = 0;
    } else if (u1 == 0 && u2 != 0) {
        u2 = s;
    } else if (u1 != 0 && u2 == 0) {
       u1 = s; 
    } else if (abs(u1) > abs(u2) ) {
      ratio = abs(u2/u1);
      u1 = s*abs(u1)/u1;
      u2 = s*ratio*abs(u2)/u2; 
    } else {
      ratio = abs(u1/u2);
      u2 = s*abs(u2)/u2;
      u1 = s*ratio*abs(u1)/u1; 
    }
    speed1 = u1;
    speed2 = u2;
    speed3 = -u1;
    speed4 = -u2; 

//    Serial.print("--------------  ");
//    Serial.print("direction: ");
//    Serial.print(d);
//    Serial.println("  --------------");
//    Serial.println();
//    Serial.println("v1  |  v2  |  v3  |  v4  ");
//    Serial.print(speed1);
//    Serial.print("  |  ");
//    Serial.print(speed2);
//    Serial.print("  |  ");
//    Serial.print(speed3);
//    Serial.print("  |  ");
//    Serial.println(speed4);
    
  if (abs(angleDif)>angleThres){//have to turn
    if (angleDif<0){
      //turn clockwise
      speed1=TURNING_SPEED;
      speed2=TURNING_SPEED;
      speed3=TURNING_SPEED;
      speed4=TURNING_SPEED;
    }
    else {
      //turn counter-clockwise
      speed1=-TURNING_SPEED;
      speed2=-TURNING_SPEED;
      speed3=-TURNING_SPEED;
      speed4=-TURNING_SPEED;
    }
  }
  else if (abs(angleDif)>13){
    if(d==STOP){
      if (angleDif<0){
        speed1 = 15;
        speed2 = 15;
        speed3 = 15;
        speed4 = 15;
      }
      else{
        speed1 = -15;
        speed2 = -15;
        speed3 = -15;
        speed4 = -15;
      }
    }
    else{
      //correction without turning
      speed1-=2*angleDif;
      speed2-=2*angleDif;
      speed3-=2*angleDif;
      speed4-=2*angleDif;
    }
  }
  if (d == 360) {
     setMotors(0,0,0,0);
  } else setMotors(speed1,speed2,speed3,speed4);

}


//----------------------------------------------------------------Move helper

double toRadian(int degree){
  /*intake a degree;
   *return the degree in radian;
   */
  return degree*3.1415926/180;
}

int sinLaw(int degree1,int degree2,int speed2){
  /*intake both angle and one of the length
   *output the other length
  */
    double radian1 = toRadian(degree1);
    double radian2 = toRadian(degree2);
    return (sin(radian1)*speed2)/sin(radian2);
}


int getAngleDif(int target){
  int output = 0;
  int current = getCompass();
  if(target<180){
    if(current>target+180){
      output = -360+current-target;
    }
    else{
      output = current-target;
    }
  }
  else{
    if(current>target-180){
      output = current-target;
    }
    else{
      output = 360-target+current;
    }
  }

  return output;
}

void setMotor(int which,int motorSpeed){
  //set one motor
  //do not make any modification!!!

  motorSpeed*=motor_dir[which];


  //protect the motor not to over-speed
  if(motorSpeed>MAX_SPEED){
    motorSpeed = MAX_SPEED;
  }
  else if(motorSpeed<-MAX_SPEED){
    motorSpeed = -MAX_SPEED;
  }

  digitalWrite(DIR[which],motorSpeed>=0?LOW:HIGH);//
  analogWrite(PWM[which],motorSpeed>=0?motorSpeed*255/100:255+motorSpeed*255/100);
}

void setMotors(int speed1, int speed2, int speed3, int speed4){
  setMotor(1,speed1);
  setMotor(2,speed2);
  setMotor(3,speed3);
  setMotor(4,speed4);
}


void STOPNOW(){
  setMotors(0,0,0,0);
}



void setupMotors(){
  //do not make any modification!!!
  //setup the pin of the motor
  pinMode(PWM[1],OUTPUT);
  pinMode(PWM[2],OUTPUT);
  pinMode(DIR[1],OUTPUT);
  pinMode(DIR[2],OUTPUT);
  pinMode(PWM[3],OUTPUT);
  pinMode(PWM[4],OUTPUT);
  pinMode(DIR[3],OUTPUT);
  pinMode(DIR[4],OUTPUT);
  TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
  TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
}

void motorTest() {
    for(int i = 0; i <= 30; ++i) {
       setMotors(i,i,i,i);
       delay(50);
    }
    for(int i = 30; i >= 0; --i) {
       setMotors(i,i,i,i);
       delay(50);
    }
    for(int i = 0; i >= -30; --i) {
       setMotors(i,i,i,i);
       delay(50);
    }
    for(int i = -30; i <= 0; ++i) {
       setMotors(i,i,i,i);
       delay(50);
    }
}
