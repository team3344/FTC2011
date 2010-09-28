/*
 *  Map.c
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */

#include "Map.h"



float VectorGetMagnitude(Vector v)
{
	return sqrt( powf(v.x, 2), powf(v.y, 2) );
}

float VectorGetAngle(Vector v)
{
	float angle = atanf(v.y / v.x);
	if ( v.x > 0 && v.y > 0 ) angle += M_PI;
	return angle;
}

Vector VectorAdd(Vector v1, Vector v2)
{
	Vector result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return result;
}

Vector VectorSubtract(Vector v1, Vector v2)	//	returns v1 - v2
{
	Vector result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	return result;
}

float VectorScalarMultiply(Vector v, float value)
{
	Vector result;
	result.x = v.x * value;
	result.y = v.y * value;
	return result;
}

float VectorDotProduct(Vector v1, Vector v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}


Vector VectorGetDisplacementFromPointToPoint(Point from, Point to)
{
	return VectorSubtract(to, from);
}



















const Node NodeZero = {-1, -1};










