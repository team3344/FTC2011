/*
 *  Geometry.h
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */

#import "Geometry.h"





Vector VectorMake(float x, float y);


typedef Point Vector;


float VectorGetMagnitude(Vector v);
float VectorGetAngle(Vector v);		//	angle is in radians

Vector VectorAdd(Vector v1, Vector v2);
Vector VectorSubtract(Vector v1, Vector v2);	//	returns v1 - v2

float VectorScalarMultiply(Vector v, float value);
float VectorDotProduct(Vector v1, Vector v2);


Vector VectorGetDisplacementFromPointToPoint(Point from, Point to);


