


#ifndef _PathFollowing_
#include "PathFollowing.h"
#endif



#define kObstructedPathInvalidationTime 5000	//	5 seconds


PathSegment _currentPathSegment;







void RobotGetCurrentPathSegment(PathSegment& psOut)
{
	memcpy(psOut, _currentPathSegment, sizeof(PathSegment));
}



void RobotTravelPathSegment(PathSegment& ps)
{
	Vector startLocation, endLocation;
	
	
	
	//	FIXME: implement
	
	
	float currentAngle;
	
	KeyPointInfo srcInfo, destInfo;
	
	//	FIXME: collect info on src & dest
	
	
	
	
	
	
	
	
	
	
	
	
}

void RobotInvalidateCurrentPathSegmentForTime(float time)	//	time in seconds
{
	MapInvalidatePathBetweenNodes(_currentPathSegment.source, _currentPathSegment.destination, kObstructedPathInvalidationTime);
}

void RobotRetraceMovementToPreviousKeyPoint()
{
	//	get location of key point we're near
	//	get our location
	//	find the angle we need to be at to go to it and add pi
	//	turn to that angle
	//	find the distance between where we're at & where we wanna be and go backwards that distance
	
	
	//	FIXME: implement
	
	
	
	
	
	
	
	
	
}

void RobotTravelFromKeyPointToKeyPoint(KeyPointID src, KeyPointID dest)
{
	MapSetCurrentNodeID(src);
	MapSetGoalNodeID(dest);

	while (
	
	//	FIXME: implement
	
	
	
	
	
	
	
	
}














/*

//	Node Traveling
//===================================================================================================================


void _RobotGoFromCurrentNodeToNode(Node& current, Node& target)
{
	Vector displacement;
	VectorSubtract(&target.location, &current.location, &displacement);
	
	//printf("\ncurrentLocation = ");
	//PrintVector(current.location);
	
	//printf("\ntarget.location = ");
	//PrintVector(target.location);
	
	//printf("\nrobot move w/vector: ");
	//PrintVector(displacement);
	//printf("\n");
	
	
	RobotMoveWithVector(&displacement);	//	FIXME: only do this for things without landmarks or beacons???
	
	//	FIXME: look for landmarks???
	//	FIXME: if we hit a landmark, tell tracker we have an absolute position
	
	
	
	
	
}


void RobotGoToNode(NodeID target)
{
	MapSetGoalNodeID(target);
	
	Node previous;
	MapGetNode(MapGetCurrentNodeID(), &previous);	//	start position
	
	while ( true )
	{
		NodeID node = MapAdvance();			//	get the id of the next node along the path
		if ( node == NodeIDZero ) break;	//	if we're at the end of the path, we're done!
		
		Node segmentTarget;
		MapGetNode(node, &segmentTarget);	//	this is where we're heading
		
		_RobotGoFromCurrentNodeToNode(&previous, &segmentTarget);	//	go to the target
		
		previous = segmentTarget;	//	the node we're now heading to will be the previous node in the next iteration
	}
}







//	FIXME: below method is trash and may have been redone in OmniDrive.c





*/








