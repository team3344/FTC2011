/*
 *  Vector.h
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */


#ifndef _Vector_
#define _Vector_






typedef struct {
	float x, y, z;
} Vector;


static inline Vector VectorMake(float x, float y, float z, Vector& v)
{
	v.x = x;
	v.y = y;
	v.z = z;
}

static inline Vector Vector2DMake(float x, float y, Vector& v)
{
	VectorMake(x, y, 0, v);
}




float VectorGetMagnitude(Vector& v);
float VectorGetAngle(Vector& v);		//	angle is in radians.  note: this ignores the z component

void VectorAdd(Vector& v1, Vector& v2, Vector& result);
void VectorSubtract(Vector& v1, Vector& v2, Vector& result);	//	returns v1 - v2






#endif
