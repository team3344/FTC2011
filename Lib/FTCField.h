


#ifndef _FTCField_
#define _FTCField_



#ifndef _Map_
#include "Map.h"
#endif





typedef enum {
	FTCTeamRed,
	FTCTeamBlue
} FTCTeam;

void FTCTeamSetCurrent(FTCTeam team);
FTCTeam FTCTeamGetCurrent();



typedef enum {
	FTCStartPositionLeft,
	FTCStartPositionRight
} FTCStartPosition;

void FTCFieldSetStartPosition(FTCStartPosition pos);
FTCStartPosition FTCFieldGetStartPosition();








//	field coordinates are in inches
//	the origin is at the corner on the red side

/************************************************
 *			*						 *(144, 144)*
 *			*						 *			*
 *	 BLUE	*						 *	 BLUE	*
 *			*						 *			*
 *			*						 *			*
 ************						 ************
 *												*
 *												*
 *												*
 *												*
 *												*
 ************************************************
 *												*
 *												*
 *												*
 *												*
 *												*
 ************						*************
 *			*						*			*
 *			*						*			*
 *	 RED	*						*	 RED	*
 *			*						*			*
 * (0,0)	*						*			*
 ************************************************/




/*
 *	A tunnel is just a place where turning is bad.
 *	For example: the top of the mountain.  The robot should
 *	only try to go over it perpindicular to the base otherwise
 *	bad things will happen.
 */






typedef enum {
	PathSegmentFlagBridgeEntrance,
	PathSegment
} PathSegmentFlags;


typedef struct {
	bool hasTunnel;
	float tunnelAngle;
	bool atBridgeEntrance;


	//	FIXME: white line???????????????????????????????????????????????????????
} KeyPointInfo;











typedef enum {
	KeyPointIDZero = 0,


	//	start squares	//
	KeyPointIDRedStartSquareLeft,
	KeyPointIDRedStartSquareRight,

	KeyPointIDBlueStartSquareLeft,
	KeyPointIDBlueStartSquareRight,



	//	dispensers	//
	KeyPointIDBlueDispenserLeft,
	KeyPointIDBlueDispenserCenter,
	KeyPointIDBlueDispenserRight,

	KeyPointIDRedDispenserLeft,
	KeyPointIDRedDispenserCenter,
	KeyPointIDRedDispenserRight,



	//	bridges	//
	KeyPointIDBlueBridgeTop,
	KeyPointIDBlueBridgeCenter,
	KeyPointIDBlueBridgeBottom,

	KeyPointIDRedBridgeTop,
	KeyPointIDRedBridgeCenter,
	KeyPointIDRedBridgeBottom,



	//	mountain	//
	KeyPointIDMountainCenterTopEdge,
	KeyPointIDMountainCenterPeak,
	KeyPointIDMountainCenterBottomEdge,



	//	pit goals	//
	KeyPointIDRedPitCenter,
	KeyPointIDBluePitCenter,



	//	white lines	//
	KeyPointIDLine1Top,
	KeyPointIDLine1Bottom,

	KeyPointIDLine2Top,
	KeyPointIDLine2Bottom,

	KeyPointIDLine3Top,
	KeyPointIDLine3Bottom,

	KeyPointIDLine4Top,
	KeyPointIDLine4Bottom,

	KeyPointIDLine5Top,
	KeyPointIDLine5Bottom,

	KeyPointIDLine6Top,
	KeyPointIDLine6Bottom

} KeyPointID;







void FTCFieldGetInfoForKeyPoint(KeyPointID kp, KeyPointInfo& kpiOut);
void FTCFieldSetInfoForKeyPoint(KeyPointID kp, KeyPointInfo& kpi);


bool WhiteLineConnectsKeyPoints(KeyPointID kp1, KeyPointID kp2);


bool TunnelExistsAtKeyPoint(KeyPointID kp);
float TunnelAngleAtKeyPoint(KeyPointID kp);











void FTCFieldInit();

void FTCFieldSetTargetKeyPoint(KeyPointID kp);
KeyPointID FTCFieldGetTargetKeyPoint();

void FTCFieldSetCurrentKeyPoint(KeyPointID kp);

void FTCFieldGetLocationOfKeyPoint(KeyPointID kp, Vector& locOut);
void FTCFieldGetNameOfKeyPoint(KeyPointID kp, string& nameOut);



KeyPointID FTCFieldGetNextKeyPoint();
KeyPointID FTCFieldGetPreviousKeyPoint();


KeyPointID FTCFieldAdvance();	//	says "hey we got to our segment goal key point, where's the next one
KeyPointID FTCFieldRetract();	//	same thing as above, but for going backwards








KeyPointID FTCFieldGetKeyPointOfBridgeForTeam(FTCTeam team);
KeyPointID FTCFieldGetKeyPointOfCenterDispenserForTeam(FTCTeam team);








#endif
