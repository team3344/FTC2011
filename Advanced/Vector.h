/*
 *  Geometry.h
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */

#import <math.h>




typedef struct {
	float x, y, z;
} Vector;




static inline Vector VectorMake(float x, float y, float z)
{
	Vector v;
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}



float VectorGetMagnitude(Vector v);
float VectorGetAngle(Vector v);		//	angle is in radians.  note: this ignores the z component

Vector VectorAdd(Vector v1, Vector v2);
Vector VectorSubtract(Vector v1, Vector v2);	//	returns v1 - v2

//	FIXME: are the below functions even necessary???
//Vector VectorScalarMultiply(Vector v, float value);
//float VectorDotProduct(Vector v1, Vector v2);

