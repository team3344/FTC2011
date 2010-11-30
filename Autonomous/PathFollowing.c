

#ifndef _PathFollowing_
#include "PathFollowing.h"
#endif



#define kObstructedPathInvalidationTime 5000	//	5 seconds


//  FIXME: implement perpendicular line stuff!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




/*
bool _TravelSegment(PathSegment& segment, bool avoidEnemies, bool forward)
{
  Vector startLocation;
  memcpy(startLocation, CurrentRobotPosition.location, sizeof(Vector));

  PathSegmentFlags segmentFlags = FieldGetSegmentFlags(segment);




  if ( (segmentFlags & PathSegmentFlagWhiteConnectingLine) && forward )
  {

  }
  else




}
*/





static bool FollowLines = false;



//	attempts to travel the segment.  returns success.  if successful, sets currentNode & CurrentRobotPosition to wherever it went
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


	Vector startLocation, startNodeLocation;
	memcpy(startLocation, CurrentRobotPosition.location, sizeof(Vector));
  FieldGetNodeLocation(segment.source, startNodeLocation);

	Vector destination;
	FieldGetNodeLocation(segment.destination, destination);

	Vector displacement;
	VectorSubtract(destination, startLocation, displacement);

	float distance, angle;
	distance = VectorGetMagnitude(displacement);
	angle = VectorGetAngle(displacement);
	RobotRotateToOrientation(angle);


	if ( (segmentFlags & PathSegmentFlagWhiteConnectingLine) && FollowLines )  //  there's a line between nodes, so follow it
	{
		if ( RobotFindWhiteLine() ) //  look for the line, proceed if we find it
    {
		  if ( globalField.nodeInfo[segment.destination].flags & NodeFlagLineEnd )
		  {
		    success = RobotFollowWhiteLineToEnd(CurrentLineFollowingContext, true);
		  }
		  else
		  {
		    success = RobotFollowWhiteLineForDistance(CurrentLineFollowingContext, distance, true);
		  }

		  if ( !success )
		  {
		    //  go back to the start node location
		    RobotMoveToLocation(startNodeLocation, true, false);  //  backwards. don't avoid robots
		  }
	  }
	  else  //  we couldn't find the line, so we must be completely and totally lost
	  {
	    for ( int i = 0; i < 10; i++ )
	    {
	      PlaySound(soundException);  //  play "Exception" 10 times
	    }

	    //  FIXME: what to do here??????????????????????????????????????????????????????????????
	  }
	}
	else if ( segmentFlags & PathSegmentFlagPerpendicularWhiteLineAtEnd )
	{
	  if ( RobotMoveUntilPerpendicularLine(distance, true) )
	  {
	    //  FIXME: set location based on the line!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	    //  when we hit the line, we're kLightSensorDistanceFromCenter away from the node, so let's go the rest of the way
	    RobotMoveToLocation(destination, false, false);
	    success = true;
	  }
	  else
	  {
	    RobotMoveToLocation(startNodeLocation, true, false);  //  back up to the start node w/out caring about other bots
	    success = false;
	  }
	}
	else	//	there's no line to follow
	{
		success = RobotMoveDistance(distance, true);	//	try to travel the distance

		if ( !success ) //  if we failed, go back to where we started
		{
		  RobotMoveToLocation(startNodeLocation, true, false);  //  retrace steps
    }
	}


	if ( success )
	{
		FieldAdvance();	//	tell the field we made it to the next node
		PlaySound(soundBeepBeep); //  let us know we got to the node
	}
	else	//	if we failed, invalidate the segment
	{
		FieldTemporarilyInvalidatePathBetweenNodes(segment.source, segment.destination, kObstructedPathInvalidationTime);
		PlaySound(soundDownwardTones);  //  let us know we didn't get to the node
	}

	return success;
}



bool RobotTravelFromNodeToNode(Node src, Node dest)
{
	FieldSetCurrentNode(src);
	FieldSetGoalNode(dest);

	while ( AbortPathFollowing == false )	//	keep going as long as we're not aborted
	{
		PathSegment segment;
		segment.source = FieldGetCurrentNode();
		segment.destination = FieldGetNextNode();

		if ( FieldGetCurrentNode() == dest )
		{
		  PlaySound(soundUpwardTones);
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

	AbortPathFollowing = false;	//	unabort so the next task actually runs

	return FieldGetCurrentNode() == dest;	//	return true if we got where we were supposed to
}
