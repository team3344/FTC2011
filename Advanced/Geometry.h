/*
 *  Geometry.h
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */



typedef struct {
	float x, y;
} Point;

Point PointMake(float x, float y);





typedef struct {
	float width, height;
} Size;

Size SizeMake(float width, float height);





typedef struct {
	Point origin;
	Size size;
} Rect;


Rect RectMake(float x, float y, float width, float height);
bool RectContainsPoint(Rect rect, Point point);


