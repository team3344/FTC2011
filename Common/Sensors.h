/*
 *  Sensors.h
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/12/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */



#ifndef _Sensors_
#define _Sensors_




/*
 *	Sensor Names:
 *	FloorLightSensor
 *	CartridgeMagneticSensor
 *	IRSensor
 *	FrontBumperTouchSensor
 */

//  FIXME: these #defines are all crap!!!!
#define FloorLightSensor 1
#define CartridgeMagneticSensor 2
#define IRSensor 3
#define FrontBumperTouchSensor 5
#define LeftMotor motorA
#define RightMotor motorC


float IRSeekerGetAngleToBeacon();	//	returns value in radians representing the angle from straight ahead to the beacon.  Straight ahead is 0.  Left is pi/2, right is -pi/2.






#endif
