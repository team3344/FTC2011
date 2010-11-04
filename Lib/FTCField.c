

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












static KeyPointInfo _infoForKeyPoints[kNodeCount];







void FTCFieldGetInfoForKeyPoint(KeyPointID kp, KeyPointInfo& kpiOut)
{
	memcpy(kpiOut, _infoForKeyPoints[kp], sizeof(KeyPointInfo));
}

void FTCFieldSetInfoForKeyPoint(KeyPointID kp, KeyPointInfo& kpi)
{
	memcpy(_infoForKeyPoints[kp], kpi, sizeof(KeyPointInfo);
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
	Vector2DMake(kFieldSize - kBridgeDistanceFromSide, (kFieldSize / 2) + (kBridgeLength / 2), location);
	MapSetNodeInfoForID(KeyPointIDRedBridgeTop, "R bridge top", location);
	
	VectorMake(kFieldSize - kBridgeDistanceFromSide, kFieldSize / 2, kBridgeHeight, location);
	MapSetNodeInfoForID(KeyPointIDRedBridgeCenter, "R bridge cntr", location);
	
	Vector2DMake(kFieldSize - kBridgeDistanceFromSide, (kFieldSize / 2) - (kBridgeLength / 2), location);
	MapSetNodeInfoForID(KeyPointIDRedBridgeBottom, "R bridge btm", location);
	
	Vector2DMake(kBridgeDistanceFromSide, (kFieldSize / 2) + (kBridgeLength / 2), location);
	MapSetNodeInfoForID(KeyPointIDBlueBridgeTop, "B bridge top", location);
	
	
	VectorMake(kBridgeDistanceFromSide, kFieldSize / 2, kBridgeHeight, location);
	MapSetNodeInfoForID(KeyPointIDBlueBridgeCenter, "B bridge cntr", location);
	
	Vector2DMake(kBridgeDistanceFromSide, (kFieldSize / 2) - (kBridgeLength / 2), location);
	MapSetNodeInfoForID(KeyPointIDBlueBridgeBottom, "B bridge btm", location);
	
	
	
	/**********		Pit Goals		**********/
	Vector2DMake(kFieldSize - (kPitWidth / 2), (kFieldSize / 2) - (kPitLength / 2), location);
	MapSetNodeInfoForID(KeyPointIDRedPitCenter, "R pit goal cntr", location);
	
	Vector2DMake(kPitWidth / 2, (kFieldSize / 2) + (kPitLength / 2), location);
	MapSetNodeInfoForID(KeyPointIDBluePitCenter, "B pit goal cntr", location);
	
	
	/**********		Mountain		**********/
	Vector2DMake(kFieldSize / 2, (kFieldSize / 2) + (kMountainLength / 2), location);
	MapSetNodeInfoForID(KeyPointIDMountainCenterTopEdge, "mntn cntr top edge", location);
	
	VectorMake(kFieldSize / 2, kFieldSize / 2, kMountainHeight, location);
	MapSetNodeInfoForID(KeyPointIDMountainCenterPeak, "mntn cntr peak", location);
	
	Vector2DMake(kFieldSize / 2, (kFieldSize / 2) - (kMountainLength / 2), location);
	MapSetNodeInfoForID(KeyPointIDMountainCenterBottomEdge, "mntn cntr btm edge", location);
	


	#define kLightSensorSeparation 5		//	FIXME: get legit value!!!!!!!!!!!!!!!!
	
	/**********		White Lines	**********/
	Vector2DMake(kLineDistanceFromFieldSide, kLineDistanceFromEdge + kLightSensorSeparation, location);
MapSetNodeInfoForID(KeyPointIDLine1Bottom, "ln1 bottom", location);

Vector2DMake(kLineDistanceFromFieldSide, ((kFieldSize  - kBridgeLength) / 2) - kRobotRadius, location);
MapSetNodeInfoForID(KeyPointIDLine1Top, "ln1 top", location);


Vector2DMake(kFieldSize - kLineDistanceFromFieldSide, 

	
	//	FIXME: add the white line stuff here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	
	
	/******************************		Connections between Nodes ******************************/
	
	
	/**********		Start Squares **********/
	
	MapConnectNodesAutomatically(KeyPointIDRedStartSquareLeft, KeyPointIDBlueDispenserLeft);
	MapConnectNodesAutomatically(KeyPointIDRedStartSquareLeft, KeyPointIDBlueDispenserCenter);
	
	MapConnectNodesAutomatically(KeyPointIDRedStartSquareRight, KeyPointIDBlueDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDRedStartSquareRight, KeyPointIDBlueDispenserRight);
	
	
	MapConnectNodesAutomatically(KeyPointIDBlueStartSquareLeft, KeyPointIDRedDispenserLeft);
	MapConnectNodesAutomatically(KeyPointIDBlueStartSquareLeft, KeyPointIDRedDispenserCenter);
	
	MapConnectNodesAutomatically(KeyPointIDBlueStartSquareRight, KeyPointIDRedDispenserCenter);
	MapConnectNodesAutomatically(KeyPointIDBlueStartSquareRight, KeyPointIDRedDispenserRight);
	
	
	/**********		Bridge Centers		**********/
	MapConnectNodesAutomatically(KeyPointIDRedBridgeCenter, KeyPointIDRedBridgeTop);
	MapConnectNodesAutomatically(KeyPointIDRedBridgeCenter, KeyPointIDRedBridgeBottom);
	
	MapConnectNodesAutomatically(KeyPointIDBlueBridgeCenter, KeyPointIDBlueBridgeTop);
	MapConnectNodesAutomatically(KeyPointIDBlueBridgeCenter, KeyPointIDBlueBridgeBottom);
	
	
	/**********		Mountain	**********/
	MapConnectNodesAutomatically(KeyPointIDMountainCenterPeak, KeyPointIDMountainCenterTopEdge);
	MapConnectNodesAutomatically(KeyPointIDMountainCenterPeak, KeyPointIDMountainCenterBottomEdge);
	
	
	/**********		Pits	**********/
	MapConnectNodesAutomatically(KeyPointIDRedPitCenter, KeyPointIDBlueDispenserRight);
	
	MapConnectNodesAutomatically(KeyPointIDBluePitCenter, KeyPointIDRedDispenserLeft);
	
	

	


	



	
	
	//	trash //////////////////////////////////
	
	
	
	
	//	FIXME: finish implementation
}
