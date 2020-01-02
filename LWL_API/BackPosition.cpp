#include "Backposition.h"

#define AREA1 135
#define AREA2 180
#define AREA3 225
#define AREA4 90
#define AREA5 STOP
#define AREA6 270
#define AREA7 45
#define AREA8 0
#define AREA9 315


void backPosition() 
{
  setAngleThres(24);
  setTarget(0);
	int uLeft = getLeftDistanceCM();
	int uRight = getRightDistanceCM();
	int uFront = getFrontDistanceCM();
	int uBack = getBackDistanceCM();
  Serial.println(uLeft+uRight);
  /*
  Serial.print("RAW: ");
  Serial.println(getRawLeftDistance());
  Serial.print("CM: ");
  Serial.println(uLeft);*/
  
	if(( uLeft + uRight > HORIZONTAL_BLOCK_RANGE ) && ( uFront + uBack > 100 )) 
	{
		// Non-block
	 	
	 	backPosition1();
		//backPosition2();

	} 
	else 
	{
		//Block
		blocked();

	}
}

void blocked() 
{
  int uLeft = getLeftDistanceCM();
  int uRight = getRightDistanceCM();
  int uFront = getFrontDistanceCM();
  int uBack = getBackDistanceCM();
  int dir = STOP;
  if( uLeft + uRight > HORIZONTAL_BLOCK_RANGE){
    if(uLeft<uRight){//using left
      if( uLeft < HARIZONTAL_CLOSER_RANGE) dir = AREA4;
      else if(uLeft <HARIZONTAL_FURTHER_RANGE) dir = AREA5;
      else dir = AREA6;
    }
    else{//using right
      if( uRight < HARIZONTAL_CLOSER_RANGE) dir = AREA6;
      else if(uRight <HARIZONTAL_FURTHER_RANGE) dir = AREA5;
      else dir = AREA4;
    }
  }
  else if(uFront + uBack > 100 ){
    if(uBack > VERTICAL_FURTHER_RANGE ) 
      {
        dir = AREA2;
      }
      //Area 8
      else if( uBack < VERTICAL_CLOSER_RANGE )
      {
        dir = AREA8;
      }
      //Area 5
      else 
      {
        dir = AREA5;      
      }
  }
  setDir(dir);
}

void backPosition1() 
{
	int uLeft = getLeftDistanceCM();
	int uRight = getRightDistanceCM();
	int uFront = getFrontDistanceCM();
	int uBack = getBackDistanceCM();
	int dir = STOP;

	// AREA 1,4,7
  if(uLeft<uRight){//using left
  	if( uLeft < HARIZONTAL_CLOSER_RANGE) 
  	{
  		//Area 1
  		if(uBack > VERTICAL_FURTHER_RANGE ) 
  		{
  			dir = AREA1;
  		}
  		//Area 7
  		else if( uBack < VERTICAL_CLOSER_RANGE )
  		{
  			dir = AREA7;
  		}
  		//Area 4
  		else 
  		{
  			dir = AREA4;			
  		}
  
  	} 
  	// AREA 2,5,8
  	else if( uLeft < HARIZONTAL_FURTHER_RANGE )
  	{
      //Area 2
      if(uBack > VERTICAL_FURTHER_RANGE ) 
      {
        dir = AREA2;
      }
      //Area 8
      else if( uBack < VERTICAL_CLOSER_RANGE )
      {
        dir = AREA8;
      }
      //Area 5
      else 
      {
        dir = AREA5;      
      }
  	}
  	// AREA 3,6,9
  	else 
  	{
      //Area 3
      if(uBack > VERTICAL_FURTHER_RANGE ) 
      {
        dir = AREA3;
      }
      //Area 9
      else if( uBack < VERTICAL_CLOSER_RANGE )
      {
        dir = AREA9;
      }
      //Area 6
      else 
      {
        dir = AREA6;      
      }
  	}
  }
  //using right
  else{
    // AREA 3,6,9
    if( uRight < HARIZONTAL_CLOSER_RANGE) 
    {
      //Area 3
      if(uBack > VERTICAL_FURTHER_RANGE ) 
      {
        dir = AREA3;
      }
      //Area 9
      else if( uBack < VERTICAL_CLOSER_RANGE )
      {
        dir = AREA9;
      }
      //Area 6
      else 
      {
        dir = AREA6;      
      }
  
    } 
    // AREA 2,5,8
    else if( uRight < HARIZONTAL_FURTHER_RANGE )
    {
      //Area 2
      if(uBack > VERTICAL_FURTHER_RANGE ) 
      {
        dir = AREA2;
      }
      //Area 8
      else if( uBack < VERTICAL_CLOSER_RANGE )
      {
        dir = AREA8;
      }
      //Area 5
      else 
      {
        dir = AREA5;      
      }
    }
    // AREA 1,4,6
    else 
    {
      //Area 1
      if(uBack > VERTICAL_FURTHER_RANGE ) 
      {
        dir = AREA1;
      }
      //Area 6
      else if( uBack < VERTICAL_CLOSER_RANGE )
      {
        dir = AREA6;
      }
      //Area 4
      else 
      {
        dir = AREA4;      
      }
    }
  }

	setDir(dir);
	setSpeed(BACK_POSITION_SPEED);

}
