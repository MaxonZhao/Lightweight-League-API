#ifndef PLAYER_H
#define PLAYER_H

#include "Motor.h"
#include "Sensor.h"
#include "BackPosition.h"
#include "TrackingBall.h"
#include "Display.h"

void player();
void setupPlayer();

void whiteLine();
void targetStrategy(int ballDir);

#endif
