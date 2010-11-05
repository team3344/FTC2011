

#ifndef _FTCField_
#include "FTCField.h"
#endif





//		Teams
//========================================================================================================================

static FTCTeam _currentTeam;

void FTCTeamSetCurrent(FTCTeam team)
{
	_currentTeam = team;
}

FTCTeam FTCTeamGetCurrent()
{
	return _currentTeam;
}



//		Start Position
//========================================================================================================================

static FTCStartPosition _startPosition;

void FTCFieldSetStartPosition(FTCStartPosition pos)
{
	_startPosition = pos;
	//	FIXME: set current location & key point
}

FTCStartPosition FTCFieldGetStartPosition()
{
	return _startPosition;
}






//		Key Point Flags
//========================================================================================================================

PathSegmentFlags _pathSegmentFlags[kNodeCount][kNodeCount];


bool FTCFieldPathSegmentHasWhiteConnectingLine(PathSegment segment)
{
	return _pathSegmentFlags[segment.source][segment.destination] & PathSegmentFlagWhiteConnectingLine;
}

void FTCFieldAddWhiteLineBetweenKeyPoints(KeyPointID kp1, KeyPointID kp2)
{
	_pathSegmentFlags[kp1][kp2] |= PathSegmentFlagWhiteConnectingLine;
	_pathSegmentFlags[kp2][kp1] |= PathSegmentFlagWhiteConnectingLine;
}

void FTCFieldAddBridgeEntranceFromKeyPointToKeyPoint(KeyPointID src, KeyPointID dest)
{
	_pathSegmentFlags[src][dest] |= PathSegmentFlagBridgeEntrance;
}

bool FTCFieldBridgeEntranceIsFromKeyPointToKeyPoint(KeyPointID src, KeyPointID dest)
{
	return _pathSegmentFlags[src][dest] & PathSegmentFlagBridgeEntrance;
}


PathSegmentFlags FTCFieldGetFlagsForPathSegment(PathSegment segment)
{
	return _pathSegmentFlags[segment.source][segment.destination];
}













//		Map Setup
//========================================================================================================================




//	note: width is the dimension that runs along the x-axis, and length runs along the y-axis


#define kFieldSize 144


#define kDispenserPerpendicularDistance 10	//	distance from a dispenser to its corresponding node
#define kSideDispenserDistanceFromFieldEnd 25  //  //

#define kStartSquareWidth 18  //  //


#define kBridgeDistanceFromSide 44  //  //

#define kBridgeHeight 6  //  //
#define kBridgeWidth 20  //  //
#define kBridgeLength 36  //  //


#define kPitWidth 20  //  //
#define kPitLength 20  //  //


#define kMountainHeight 6  //  //
#define kMountainLength 12  //  //
#define kMountainWidth 50  //  //

#define kLineDistanceFromFieldEnd 50	//	//
#define kLineDistanceFromFieldSide ((kBridgeWidth / 2) + kBridgeDistanceFromSide)



void FTCFieldInit()		//	sets values specific to our field.
{
	MapReset(); //	clear old values
	
	Vector location;
	
	/**********		Start Squares		**********/
	Vector2DMake(kStartSquareWidth / 2, kStartSquareWidth / 2, location);
	MapSetNodeInfoForID(KeyPointIDRedStartSquareLeft, "R left start sqr", location);
	
	Vector2DMake(kFieldSize - (kStartSquareWidth / 2), kStartSquareWidth / 2, location);
	MapSetNodeInfoForID(KeyPointIDRedStartSquareRight, "R right start sqr", location);
	
	Vector2DMake(kStartSquareWidth / 2, kFieldSize - (kStartSquareWidth / 2), location);
	MapSetNodeInfoForID(KeyPointIDBlueStartSquareLeft, "B left start sqr", location);
	
	Vector2DMake(kFieldSize - (kStartSquareWidth / 2), kFieldSize - (kStartSquareWidth / 2), location);
	MapSetNodeInfoForID(KeyPointIDBlueStartSquareRight, "B right start sqr", location);
	
	
	/**********		Dispensers		**********/
	Vector2DMake(kDispenserPerpendicularDistance, kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(KeyPointIDRedDispenserLeft, "R left dispenser", location);
	
	Vector2DMake(kFieldSize / 2, kFieldSize - kDispenserPerpendicularDistance, location);
	MapSetNodeInfoForID(KeyPointIDRedDispenserCenter, "R cntr dispenser", location);
	
	Vector2DMake(kFieldSize - kDispenserPerpendicularDistance, kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(KeyPointIDRedDispenserRight, "R right dispenser", location);
	
	Vector2DMake(kDispenserPerpendicularDistance, kFieldSize - kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(KeyPointIDBlueDispenserLeft, "B left dispenser", location);
	
	Vector2DMake(kFieldSize / 2, kDispenserPerpendicularDistance, location);
	MapSetNodeInfoForID(KeyPointIDBlueDispenserCenter, "B cntr dispenser", location);
	
	Vector2DMake(kFieldSize - kDispenserPerpendicularDistance, kFieldSize - kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(KeyPointIDBlueDispenserRight, "B right dispenser", location);
	
	
	
	/**********		Bridges		**********/
	//Vector2DMake(kFieldSize - kBridgeDistanceFromSide, (kFieldSize / 2) + (kBridgeLength / 2), location);
	//MapSetNodeInfoForID(KeyPointIDRedBridgeTop, "R bridge top", location);
	
	VectorMake(kFieldSize - kBridgeDistanceFromSide, kFieldSize / 2, kBridgeHeight, location);
	MapSetNodeInfoForID(KeyPointIDRedBridgeCenter, "R bridge cntr", location);
	
	//Vector2DMake(kFieldSize - kBridgeDistanceFromSide, (kFieldSize / 2) - (kBridgeLength / 2), location);
	//MapSetNodeInfoForID(KeyPointIDRedBridgeBottom, "R bridge btm", location);
	
	//Vector2DMake(kBridgeDistanceFromSide, (kFieldSize / 2) + (kBridgeLength / 2), location);
	//MapSetNodeInfoForID(KeyPointIDBlueBridgeTop, "B bridge top", location);
	
	
	VectorMake(kBridgeDistanceFromSide, kFieldSize / 2, kBridgeHeight, location);
	MapSetNodeInfoForID(KeyPointIDBlueBridgeCenter, "B bridge cntr", location);
	
	//Vector2DMake(kBridgeDistanceFromSide, (kFieldSize / 2) - (kBridgeLength / 2), location);
	//MapSetNodeInfoForID(KeyPointIDBlueBridgeBottom, "B bridge btm", location);
	
	
	
	/**********		Pit Goals		**********/
	//Vector2DMake(kFieldSize - (kPitWidth / 2), (kFieldSize / 2) - (kPitLength / 2), location);
	//MapSetNodeInfoForID(KeyPointIDRedPitCenter, "R pit goal cntr", location);
	
	//Vector2DMake(kPitWidth / 2, (kFieldSize / 2) + (kPitLength / 2), location);
	//MapSetNodeInfoForID(KeyPointIDBluePitCenter, "B pit goal cntr", location);
	
	
	/**********		Mountain		**********/
	//Vector2DMake(kFieldSize / 2, (kFieldSize / 2) + (kMountainLength / 2), location);
	//MapSetNodeInfoForID(KeyPointIDMountainCenterTopEdge, "mntn cntr top edge", location);
	
	//VectorMake(kFieldSize / 2, kFieldSize / 2, kMountainHeight, location);
	//MapSetNodeInfoForID(KeyPointIDMountainCenterPeak, "mntn cntr peak", location);
	
	//Vector2DMake(kFieldSize / 2, (kFieldSize / 2) - (kMountainLength / 2), location);
	//MapSetNodeInfoForID(KeyPointIDMountainCenterBottomEdge, "mntn cntr btm edge", location);
	




	
	/**********		White Lines		**********/
	Vector2DMake(kLineDistanceFromFieldSide, kLineDistanceFromEdge + kLightSensorDistanceFromCenter, location);
	MapSetNodeInfoForID(KeyPointIDLine1Bottom, "ln1 bottom", location);
	
	Vector2DMake(kLineDistanceFromFieldSide, ((kFieldSize  - kBridgeLength) / 2) - kRobotRadius, location);
	MapSetNodeInfoForID(KeyPointIDLine1Top, "ln1 top", location);
	
	
	
	Vector2DMake(kFieldSize / 2, kLineDistanceFromEdge + kLightSensorDistanceFromCenter, location);
	MapSetNodeInfoForID(KeyPointIDLine2Bottom, "ln2 bottom", location);
	
	Vector2DMake(kFieldSize / 2, ((kFieldSize - kMountainLength) / 2) - kRobotRadius, location);
	MapSetNodeInfoForID(KeyPointIDLine2Top, "ln2 top", location);
	
	
	
	Vector2DMake(kFieldSize - kLineDistanceFromFieldSide, kLineDistanceFromEdge + kLightSensorDistanceFromCenter, location);
	MapSetNodeInfoForID(KeyPointIDLine3Bottom, "ln3 bottom", location);
	
	Vector2DMake(kFieldSize - kLineDistanceFromFieldSide, ((kFieldSize  - kBridgeLength) / 2) - kRobotRadius, location);
	MapSetNodeInfoForID(KeyPointIDLine3Top, "ln3 top", location);
	
	
	
	Vector2DMake(kLineDistanceFromFieldSide, ((kFieldSize + kBridgeLength) / 2) + kRobotRadius, location);
	MapSetNodeInfoForID(KeyPointIDLine4Bottom, "ln4 bottom", location);
	
	Vector2DMake(kLineDistanceFromFieldSide, kFieldSize - (kLineDistanceFromEdge + kLightSensorDistanceFromCenter), location);
	MapSetNodeInfoForID(KeyPointIDLine4Top, "ln4 top", location);
	
	
	
	Vector2DMake(kFieldSize / 2, ((kFieldSize + kMountainLength) / 2) + kRobotRadius, location);
	MapSetNodeInfoForID(KeyPointIDLine5Bottom, "ln5 bottom", location);
	
	Vector2DMake(kFieldSize / 2, kFieldSize - (kLineDistanceFromEdge + kLightSensorDistanceFromCenter), location);
	MapSetNodeInfoForID(KeyPointIDLine5Top, "ln5 top", location);
	
	
	
	Vector2DMake(kFieldSize - kLineDistanceFromFieldSide, ((kFieldSize + kBridgeLength) / 2) + kRobotRadius, location);
	MapSetNodeInfoForID(KeyPointIDLine6Bottom, "ln6 bottom", location);
	
	Vector2DMake(kFieldSize - kLineDistanceFromFieldSide, kFieldSize - (kLineDistanceFromEdge + kLightSensorDistanceFromCenter), location);
	MapSetNodeInfoForID(KeyPointIDLine6Top, "ln6 top", location);
	
	
	
	
	//	Tell it where the white lines are
	FTCFieldAddWhiteLineBetweenKeyPoints(KeyPointIDLine1Bottom, KeyPointIDLine1Top);	//	line 1
	FTCFieldAddWhiteLineBetweenKeyPoints(KeyPointIDLine2Bottom, KeyPointIDLine2Top);	//	line 2
	FTCFieldAddWhiteLineBetweenKeyPoints(KeyPointIDLine3Bottom, KeyPointIDLine3Top);	//	line 3
	FTCFieldAddWhiteLineBetweenKeyPoints(KeyPointIDLine4Bottom, KeyPointIDLine4Top);	//	line 4
	FTCFieldAddWhiteLineBetweenKeyPoints(KeyPointIDLine5Bottom, KeyPointIDLine5Top);	//	line 5
	FTCFieldAddWhiteLineBetweenKeyPoints(KeyPointIDLine6Bottom, KeyPointIDLine6Top);	//	line 6
	
	
	
	
	
	//	Tell it where the bridge entrances are
	FTCFieldAddBridgeEntranceFromKeyPointToKeyPoint(KeyPointIDLine1Top, KeyPointIDBlueBridgeCenter);	//	Blue bridge
	FTCFieldAddBridgeEntranceFromKeyPointToKeyPoint(KeyPointIDLine4Bottom, KeyPointIDBlueBridgeCenter);	//
	
	FTCFieldAddBridgeEntranceFromKeyPointToKeyPoint(KeyPointIDLine3Top, KeyPointIDRedBridgeCenter);		//	Red bridge
	FTCFieldAddBridgeEntranceFromKeyPointToKeyPoint(KeyPointIDLine6Bottom, KeyPointIDRedBridgeCenter);	//
	
	
	
	
	
	
	/******************************		Connections between Nodes ******************************/
	
	
	/**********		Start Squares **********/
	
	MapConnectNodesAutomatically(KeyPointIDRedStartSquareLeft, KeyPointIDBlueDispenserLeft);
	MapConnectNodesAutomatically(KeyPointIDRedStartSquareLeft, KeyPointIDBlueDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDRedStartSquareLeft, KeyPointIDLine1Bottom);
	
	MapConnectNodesAutomatically(KeyPointIDRedStartSquareRight, KeyPointIDBlueDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDRedStartSquareRight, KeyPointIDBlueDispenserRight);
	MapConnectNodesAutomatically(KeyPointIDRedStartSquareRight, KeyPointIDLine3Bottom);
	
	
	MapConnectNodesAutomatically(KeyPointIDBlueStartSquareLeft, KeyPointIDRedDispenserLeft);
	MapConnectNodesAutomatically(KeyPointIDBlueStartSquareLeft, KeyPointIDRedDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDBlueStartSquareLeft, KeyPointIDLine4Top);
	
	MapConnectNodesAutomatically(KeyPointIDBlueStartSquareRight, KeyPointIDRedDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDBlueStartSquareRight, KeyPointIDRedDispenserRight);
	MapConnectNodesAutomatically(KeyPointIDBlueStartSquareRight, KeyPointIDLine6Top);
	
	
	/**********		Bridge Centers		**********/
	MapConnectNodesAutomatically(KeyPointIDRedBridgeCenter, KeyPointIDLine4Bottom);
	MapConnectNodesAutomatically(KeyPointIDRedBridgeCenter, KeyPointIDLine1Top);
	
	MapConnectNodesAutomatically(KeyPointIDBlueBridgeCenter, KeyPointIDLine6Bottom);
	MapConnectNodesAutomatically(KeyPointIDBlueBridgeCenter, KeyPointIDLine3Top);
	
	
	/**********		Mountain	**********/
	//MapConnectNodesAutomatically(KeyPointIDMountainCenterPeak, KeyPointIDMountainCenterTopEdge);
	//MapConnectNodesAutomatically(KeyPointIDMountainCenterPeak, KeyPointIDMountainCenterBottomEdge);
	
	
	/**********		Pits	**********/
	//MapConnectNodesAutomatically(KeyPointIDRedPitCenter, KeyPointIDBlueDispenserRight);
	//MapConnectNodesAutomatically(KeyPointIDBluePitCenter, KeyPointIDRedDispenserLeft);
	
	
	/**********		White Lines	**********/
	MapConnectNodesAutomatically(KeyPointIDLine1Bottom, KeyPointIDLine1Top);
	MapConnectNodesAutomatically(KeyPointIDLine1Bottom, KeyPointIDBlueDispenserLeft);
	MapConnectNodesAutomatically(KeyPointIDLine1Bottom, KeyPointIDLine2Bottom);
	MapConnectNodesAutomatically(KeyPointIDLine1Bottom, KeyPointIDBlueDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDLine1Top, KeyPointIDBlueDispenserLeft);
	
	MapConnectNodesAutomatically(KeyPointIDLine2Bottom, KeyPointIDLine2Top);
	MapConnectNodesAutomatically(KeyPointIDLine2Bottom, KeyPointIDBlueDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDLine2Bottom, KeyPointIDLine1Top);
	MapConnectNodesAutomatically(KeyPointIDLine2Bottom, KeyPointIDLine3Top);
	
	MapConnectNodesAutomatically(KeyPointIDLine3Bottom, KeyPointIDLine3Top);
	MapConnectNodesAutomatically(KeyPointIDLine3Bottom, KeyPointIDBlueDispenserRight);
	MapConnectNodesAutomatically(KeyPointIDLine3Bottom, KeyPointIDLine2Bottom);
	MapConnectNodesAutomatically(KeyPointIDLine3Bottom, KeyPointIDBlueDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDLine3Top, KeyPointIDBlueDispenserRight);
	
	
	MapConnectNodesAutomatically(KeyPointIDLine4Top, KeyPointIDLine4Bottom);
	MapConnectNodesAutomatically(KeyPointIDLine4Top, KeyPointIDRedDispenserLeft);
	MapConnectNodesAutomatically(KeyPointIDLine4Top, KeyPointIDLine5Top);
	MapConnectNodesAutomatically(KeyPointIDLine4Top, KeyPointIDRedDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDLine4Bottom, KeyPointIDRedDispenserLeft);

	MapConnectNodesAutomatically(KeyPointIDLine5Top, KeyPointIDLine5Bottom);
	MapConnectNodesAutomatically(KeyPointIDLine5Top, KeyPointIDRedDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDLine5Top, KeyPointIDLine4Bottom);
	MapConnectNodesAutomatically(KeyPointIDLine5Top, KeyPointIDLine6Bottom);
	
	MapConnectNodesAutomatically(KeyPointIDLine6Top, KeyPointIDLine6Bottom);
	MapConnectNodesAutomatically(KeyPointIDLine6Top, KeyPointIDRedDispenserRight);
	MapConnectNodesAutomatically(KeyPointIDLine6Top, KeyPointIDLine5Top);
	MapConnectNodesAutomatically(KeyPointIDLine6Top, KeyPointIDRedDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDLine6Bottom, KeyPointIDRedDispenserRight);
}
