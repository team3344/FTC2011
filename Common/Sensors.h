/*
 *  Sensors.h
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/12/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */





typedef unsigned int SensorPort;




bool MagneticSensorFieldIsPresent(SensorPort port);
//	float MagneticSensorFieldStrength();







bool TouchSensorIsPressed(SensorPort port);





float IRSeekerGetAngleToBeacon(SensorPort);	//	returns value in radians representing the angle from straight ahead to the beacon.  Straight ahead is 0.  Left is pi/2, right is -pi/2.

