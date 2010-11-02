/*
 *  RobotC_Defines.h
 *  RoboMapTest
 *
 *  Created by Justin Buchanan on 10/5/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */

/*
 *	This defines robotc stuff so the compiler won't complain when testing stuff on a real computer
 */


#import <stdio.h>
#import <stdlib.h>
#import <string.h>



typedef _Bool bool;
typedef char string[20];
typedef void task;



#define true (bool)1
#define false (bool)0



static int motor[100];
static int SensorValue[100];





#define PC_DEBUG_STRING(string str) printf(str)





#define FloorLightSensor 0


#define LeftMotor 0
#define RightMotor 1


