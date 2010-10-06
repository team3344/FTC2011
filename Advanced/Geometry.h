/*
 *  Geometry.h
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */


#import "Vector.h"





typedef Vector Point;


static inline Point PointMake(float x, float y)
{
	Point p;
	p.x = x;
	p.y = y;
	return p;
}


extern const Point PointZero;




float PointGetDistanceToPoint(Point p1, Point p2);
float PointGetAngleToPoint(Point p1, Point p2);





typedef struct {
	float width, height;
} Size;

Size SizeMake(float width, float height);





typedef struct {
	Point origin;
	Size size;
} Rect;


Rect RectMake(float x, float y, float width, float height);
//bool RectContainsPoint(Rect rect, Point point);


