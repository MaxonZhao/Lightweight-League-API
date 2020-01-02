#include "TrackingBall.h"

#define DIR0 135
#define AREA2 180
#define AREA3 225
#define AREA4 90
#define AREA5 0
#define AREA6 270
#define AREA7 45
#define AREA8 0
#define AREA9 315

void ballTracking() 
{
	int eyeValue = getEyeValue();
	if( eyeValue > TRACE_VS_AROUND_EYE_VALUE ) 
	{
		tracingTheBall1();
		//tracingTheBall2();
	}
	else 
	{
		aroundTheBall1();
		//aroundTheBall2();
	}
}

void tracingTheBall1()
{
	int eyePort = getEyePort();
	if( eyePort == 14 )  
	{
		eyePort = 0; 
	}
	else
	{
		eyePort = eyePort - 1;
	}

	setDir(eyePort *30);
	setSpeed(TRACING_BALL_SPEED);
}

void tracingTheBall2()
{
	// TODO
	int eyePort = getEyePort();
	int dir = 0;

	if( eyePort == 1 ) dir = 0;
	else if( eyePort == 2 ) dir = 30;
	else if( eyePort == 3 ) dir = 60;
	else if( eyePort == 4 ) dir = 90;
	// TODO: 5-14

	setDir(dir);
	setSpeed(TRACING_BALL_SPEED);
}


void aroundTheBall1()
{
	// TODO
	int eyePort = getEyePort();
	int dir = 0;

	if( eyePort == 1 ) dir = 0;
	else if( eyePort == 2 ) dir = 45;
	else if( eyePort == 3 ) dir = 75;
	else if( eyePort == 4 ) dir = 110;
	// TODO: 5-14

	setDir(dir);
	setSpeed(AROUND_BALL_SPEED);
}

void aroundTheBall2()
{
	int dir = 0;
	// TODO
	setDir(dir);
	setSpeed(AROUND_BALL_SPEED);
}
