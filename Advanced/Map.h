/*
 *  Map.h
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */

#define kMapResolution 50	//	width & height of map.  bigger # = more accurate, but slower




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











Vector VectorMake(float x, float y);


typedef Point Vector;


float VectorGetMagnitude(Vector v);
float VectorGetAngle(Vector v);		//	angle is in radians

Vector VectorAdd(Vector v1, Vector v2);
Vector VectorSubtract(Vector v1, Vector v2);	//	returns v1 - v2

float VectorScalarMultiply(Vector v, float value);


float VectorDotProduct(Vector v1, Vector v2);




Vector VectorGetDisplacementFromPointToPoint(Point from, Point to);







typedef enum {
	MapItemBlank = 0,
	MapItemRobot,	//	friend vs. foe????????????
	MapItemMobileGoal,
	MapItemStationaryGoal,
	MapItemBatonDispenser,
	MapItemBridge	//	ours vs. theirs????????????
} MapItem;


typedef struct {
	MapItem items[kMapResolution][kMapResolution];
} Map;



//	//////////////////////////////////////////////////////////////////////




typedef enum {
	//	dispensers
	NodeBlueLeftDispenser,
	NodeBlueCenterDispenser,
	NodeBlueRightDispenser,
	
	NodeRedLeftDispenser,
	NodeRedCenterDispenser,
	NodeRedRightDispenser,
	
	
	//	goals
	Node
	
	
	NodeWhiteLineEnd,
	
	NodeBridgeCenter,
	NodeBridgeEnd,
	
	NodeHillCenter,
	NodeHillBase,
	
	NodeFieldCorner,
	
	NodePitCenter,
	
	
} NodeType;


#define kNodeCount 30	//	FIXME: set legit




typedef struct {
	Point location;
	NodeType type;
} NodeInfo;




extern const Node NodeZero;



typedef unsigned int Node;

void MapInvalidatePath(Node n1, Node n2);

void MapSetCurrentNode(Node current);
Node MapGetCurrentNode();

void MapSetGoalNode(Node goal);

Node MapAdvance();	//	Sets current node to next node and returns the next node after that



typedef struct {
	Node cachedPath[10];
	
} Map;



















