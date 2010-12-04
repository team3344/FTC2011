/*
 *  Vector.c
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */

#ifndef _Vector_
#include "Vector.h"
#endif

#ifndef _Defines_
#include "Defines.h"
#endif




void VectorMake(float x, float y, float z, Vector& v)
{
	v.x = x;
	v.y = y;
	v.z = z;
}


void Vector2DMake(float x, float y, Vector& v)
{
	VectorMake(x, y, 0, v);
}





float VectorGetMagnitude(Vector& v)
{
	return sqrt( powf(abs(v.x), 2) + powf(abs(v.y), 2) + powf(abs(v.z), 2) );
}

float VectorGetAngle(Vector& v)	//	note: ignores the z component
{
	float angle = atan(v.y / v.x);

	if ( v.x == 0 )
	{
	  angle = PI / 2.0;
	  if ( v.y < 0 ) angle = (3.0 * PI) / 2.0;
	}
	else if ( v.x < 0 ) angle += PI;
	return angle;
}

void VectorAdd(Vector& v1, Vector& v2, Vector& result)
{
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
}

void VectorSubtract(Vector& v1, Vector& v2, Vector& result)	//	returns v1 - v2
{
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
}




void VectorScalarMultiply(Vector& vector, float factor, Vector& vOut)
{
	vOut.x = vector.x * factor;
	vOut.y = vector.y * factor;
	vOut.z = vector.z * factor;
}
