

#ifndef _PathFollowing_
#include "PathFollowing.h"
#endif



#define kObstructedPathInvalidationTime 5000	//	5 seconds


static bool _abort;

void AbortPathFollowing()
{
	_abort = true;
}





//	attempts to travel the segment.  returns success.  if successful,  to wherever it went
bool RobotTravelPathSegment(PathSegment& segment)
{
	PathSegmentFlags segmentFlags = FieldGetPathSegmentFlags(segment);
	
	bool success;
	
	
	
	if ( segmentFlags & PathSegmentFlagBridgeEntrance )
	{
		RobotApproachBridge();
		RobotLowerBridge();
	}
	
	
	
	if ( segmentFlags & PathSegmentFlagWhiteConnectingLine )
	{
		//	follow the line
		///////////////////////////
		//	FIXME: implement	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		//	?Follow for distance?
		///	Follow til end?
		
		////////////
	}
	else	//	there's no line to follow
	{
		RobotPosition startPosition;
		RobotGetCurrentPosition(startPosition);
		
		Vector destination;
		FieldGetNodeLocation(segment.destination, destination);
		
		Vector displacement;
		VectorSubtract(destination, startPosition.location, displacement);
		
		float distance, angle;
		distance = VectorGetMagnitude(displacement);
		angle = VectorGetAngle(displacement);
		
		RobotRotateToOrientation(angle);
		
		if ( !RobotMoveDistance(distance) )	//	try to travel the distance.  if it fails, go back to where we started
		{
			RobotPosition currentPosition;
			RobotGetCurrentPosition(currentPosition);
			
			VectorSubtract(startPosition.location, currentPosition.location, displacement);
			distance = VectorGetMagnitude(displacement);
			angle = VectorGetAngle(displacement);
			
			//	backup to the start location
			RobotRotateToOrientation(displacement + PI);
			RobotMoveDistance(-distance);					//	FIXME: go this time without stopping for obstructions
			
			success = false;
		}
	}
	
	
	if ( success )
	{
		FieldAdvance();	//	tell the field we made it to the next node
	}
	else	//	if we failed, invalidate the segment
	{
			FieldTemporarilyInvalidatePathBetweenNodes(segment.source, segment.destination, kObstructedPathInvalidationTime);
	}
	
	return success;
}



bool RobotTravelFromNodeToNode(Node src, Node dest)
{
	FieldSetCurrentNode(src);
	FieldSetGoalNode(dest);

	while ( _abort == false )	//	keep going as long as we're not aborted
	{
		PathSegment segment;
		segment.source = FieldGetCurrentNode();
		segment.destination = FieldGetNextNode();
		
		if ( currentNode == dest )
		{
			break;	//	we're there!!!
		}
		else if ( segmentTargetNode == NodeZero )	//	there's no path available
		{
			wait10Msec(100);		//	wait 1 second to see if a path validated
			FieldRecalculatePath();
		}
		else
		{
			RobotTravelPathSegment(segment);
		}
	}
	
	_abort = false;	//	unabort so the next task actually runs
	
	return FieldGetCurrentNode() == dest;	//	return true if we got where we were supposed to
}








/*
void RobotRetraceMovementToPreviousKeyPoint()
{
	//	get location of key point we're near
	//	get our location
	//	find the angle we need to be at to go to it and add pi
	//	turn to that angle
	//	find the distance between where we're at & where we wanna be and go backwards that distance


	//	FIXME: implement









}
*/










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
	FieldSetGoalNodeID(target);

	Node previous;
	FieldGetNode(FieldGetCurrentNodeID(), &previous);	//	start position

	while ( true )
	{
		NodeID node = FieldAdvance();			//	get the id of the next node along the path
		if ( node == NodeIDZero ) break;	//	if we're at the end of the path, we're done!

		Node segmentTarget;
		FieldGetNode(node, &segmentTarget);	//	this is where we're heading

		_RobotGoFromCurrentNodeToNode(&previous, &segmentTarget);	//	go to the target

		previous = segmentTarget;	//	the node we're now heading to will be the previous node in the next iteration
	}
}



*/
