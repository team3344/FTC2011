

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





void FTCFieldInit()		//	sets values specific to our field.
{
	MapReset(); //	clear old values
	
	Vector location;
	
	/**********		Start Squares		**********/
	Vector2DMake(kStartSquareWidth / 2, kStartSquareWidth / 2, location);
	MapSetNodeInfoForID(NodeIDRedStartSquareLeft, "R left start sqr", location);
	
	Vector2DMake(kFieldSize - (kStartSquareWidth / 2), kStartSquareWidth / 2, location);
	MapSetNodeInfoForID(NodeIDRedStartSquareRight, "R right start sqr", location);
	
	Vector2DMake(kStartSquareWidth / 2, kFieldSize - (kStartSquareWidth / 2), location);
	MapSetNodeInfoForID(NodeIDBlueStartSquareLeft, "B left start sqr", location);
	
	Vector2DMake(kFieldSize - (kStartSquareWidth / 2), kFieldSize - (kStartSquareWidth / 2), location);
	MapSetNodeInfoForID(NodeIDBlueStartSquareRight, "B right start sqr", location);
	
	
	/**********		Dispensers		**********/
	Vector2DMake(kDispenserPerpendicularDistance, kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(NodeIDRedDispenserLeft, "R left dispenser", location);
	
	Vector2DMake(kFieldSize / 2, kFieldSize - kDispenserPerpendicularDistance, location);
	MapSetNodeInfoForID(NodeIDRedDispenserCenter, "R cntr dispenser", location);
	
	Vector2DMake(kFieldSize - kDispenserPerpendicularDistance, kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(NodeIDRedDispenserRight, "R right dispenser", location);
	
	Vector2DMake(kDispenserPerpendicularDistance, kFieldSize - kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(NodeIDBlueDispenserLeft, "B left dispenser", location);
	
	Vector2DMake(kFieldSize / 2, kDispenserPerpendicularDistance, location);
	MapSetNodeInfoForID(NodeIDBlueDispenserCenter, "B cntr dispenser", location);
	
	Vector2DMake(kFieldSize - kDispenserPerpendicularDistance, kFieldSize - kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(NodeIDBlueDispenserRight, "B right dispenser", location);
	
	
	
	/**********		Bridges		**********/
	Vector2DMake(kFieldSize - kBridgeDistanceFromSide, (kFieldSize / 2) + (kBridgeLength / 2), location);
	MapSetNodeInfoForID(NodeIDRedBridgeTop, "R bridge top", location);
	
	VectorMake(kFieldSize - kBridgeDistanceFromSide, kFieldSize / 2, kBridgeHeight, location);
	MapSetNodeInfoForID(NodeIDRedBridgeCenter, "R bridge cntr", location);
	
	Vector2DMake(kFieldSize - kBridgeDistanceFromSide, (kFieldSize / 2) - (kBridgeLength / 2), location);
	MapSetNodeInfoForID(NodeIDRedBridgeBottom, "R bridge btm", location);
	
	Vector2DMake(kBridgeDistanceFromSide, (kFieldSize / 2) + (kBridgeLength / 2), location);
	MapSetNodeInfoForID(NodeIDBlueBridgeTop, "B bridge top", location);
	
	
	VectorMake(kBridgeDistanceFromSide, kFieldSize / 2, kBridgeHeight, location);
	MapSetNodeInfoForID(NodeIDBlueBridgeCenter, "B bridge cntr", location);
	
	Vector2DMake(kBridgeDistanceFromSide, (kFieldSize / 2) - (kBridgeLength / 2), location);
	MapSetNodeInfoForID(NodeIDBlueBridgeBottom, "B bridge btm", location);
	
	
	
	/**********		Pit Goals		**********/
	Vector2DMake(kFieldSize - (kPitWidth / 2), (kFieldSize / 2) - (kPitLength / 2), location);
	MapSetNodeInfoForID(NodeIDRedPitCenter, "R pit goal cntr", location);
	
	Vector2DMake(kPitWidth / 2, (kFieldSize / 2) + (kPitLength / 2), location);
	MapSetNodeInfoForID(NodeIDBluePitCenter, "B pit goal cntr", location);
	
	
	/**********		Mountain		**********/
	Vector2DMake(kFieldSize / 2, (kFieldSize / 2) + (kMountainLength / 2), location);
	MapSetNodeInfoForID(NodeIDMountainCenterTopEdge, "mntn cntr top edge", location);
	
	VectorMake(kFieldSize / 2, kFieldSize / 2, kMountainHeight, location);
	MapSetNodeInfoForID(NodeIDMountainCenterPeak, "mntn cntr peak", location);
	
	Vector2DMake(kFieldSize / 2, (kFieldSize / 2) - (kMountainLength / 2), location);
	MapSetNodeInfoForID(NodeIDMountainCenterBottomEdge, "mntn cntr btm edge", location);
	
	
	
	
	/******************************		Connections between Nodes ******************************/
	
	
	/**********		Start Squares **********/
	
	MapConnectNodesAutomatically(NodeIDRedStartSquareLeft, NodeIDBlueDispenserLeft);
	MapConnectNodesAutomatically(NodeIDRedStartSquareLeft, NodeIDBlueDispenserCenter);
	
	MapConnectNodesAutomatically(NodeIDRedStartSquareRight, NodeIDBlueDispenserCenter);
	MapConnectNodesAutomatically(NodeIDRedStartSquareRight, NodeIDBlueDispenserRight);
	
	
	MapConnectNodesAutomatically(NodeIDBlueStartSquareLeft, NodeIDRedDispenserLeft);
	MapConnectNodesAutomatically(NodeIDBlueStartSquareLeft, NodeIDRedDispenserCenter);
	
	MapConnectNodesAutomatically(NodeIDBlueStartSquareRight, NodeIDRedDispenserCenter);
	MapConnectNodesAutomatically(NodeIDBlueStartSquareRight, NodeIDRedDispenserRight);
	
	
	/**********		Bridge Centers		**********/
	MapConnectNodesAutomatically(NodeIDRedBridgeCenter, NodeIDRedBridgeTop);
	MapConnectNodesAutomatically(NodeIDRedBridgeCenter, NodeIDRedBridgeBottom);
	
	MapConnectNodesAutomatically(NodeIDBlueBridgeCenter, NodeIDBlueBridgeTop);
	MapConnectNodesAutomatically(NodeIDBlueBridgeCenter, NodeIDBlueBridgeBottom);
	
	
	/**********		Mountain	**********/
	MapConnectNodesAutomatically(NodeIDMountainCenterPeak, NodeIDMountainCenterTopEdge);
	MapConnectNodesAutomatically(NodeIDMountainCenterPeak, NodeIDMountainCenterBottomEdge);
	
	
	/**********		Pits	**********/
	MapConnectNodesAutomatically(NodeIDRedPitCenter, NodeIDBlueDispenserRight);
	
	MapConnectNodesAutomatically(NodeIDBluePitCenter, NodeIDRedDispenserLeft);
	
	
	
	
	//	trash //////////////////////////////////
	
	
	
	
	//	FIXME: finish implementation
}
