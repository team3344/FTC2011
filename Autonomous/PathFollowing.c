

#ifndef _PathFollowing_
#include "PathFollowing.h"
#endif



#define kObstructedPathInvalidationTime 5000	//	5 seconds




//	attempts to travel the segment.  returns success.  if successful, sets currentNode & currentPosition to wherever it went
bool RobotTravelPathSegment(PathSegment& segment)
{
	PathSegmentFlags segmentFlags = FieldGetPathSegmentFlags(segment);

	bool success;


	//	if there's a bridge in front of us, GET OVER IT!
	if ( segmentFlags & PathSegmentFlagBridgeEntrance )
	{
		RobotApproachBridge();
		RobotLowerBridge();
	}



	if ( segmentFlags & PathSegmentFlagWhiteConnectingLine )
	{
		LineFollowingContext ctxt;
		RobotFindWhiteLine(ctxt);
		success = RobotFollowWhiteLineToEnd(ctxt);
		
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
		memcpy(startPosition, currentRobotPosition, sizeof(RobotPosition));
		
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
			RobotRotateToOrientation(angle + PI);
			RobotMoveDistance(-distance);					//	FIXME: go this time without stopping for obstructions

			success = false;
		}
		else
		{
			memcpy(&currentRobotPosition.location, &destination, sizeof(Vector));	//	tell it we're at the location of the node	//	FIXME: is this necessary?
			success = true;
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

	while ( abortPathFollowing == false )	//	keep going as long as we're not aborted
	{
		PathSegment segment;
		segment.source = FieldGetCurrentNode();
		segment.destination = FieldGetNextNode();

		if ( FieldGetCurrentNode() == dest )
		{
			break;	//	we're there!!!
		}
		else if ( segment.destination == NodeZero )	//	there's no path available
		{
			wait10Msec(100);		//	wait 1 second to see if a path validated
			FieldRecalculatePath();
		}
		else
		{
			RobotTravelPathSegment(segment);
		}
	}

	abortPathFollowing = false;	//	unabort so the next task actually runs

	return FieldGetCurrentNode() == dest;	//	return true if we got where we were supposed to
}
