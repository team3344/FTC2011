

#ifndef _Field_
#include "Field.h"
#endif


#ifndef _Defines_
#include "Defines.h"
#endif





//	caches used for dijkstra's algorithm
Node previous[kNodeCount];
float tentativeCosts[kNodeCount];
bool traveled[kNodeCount];






/*

//	Field Drawing
//=========================================================================================================

#define kDisplaySize 50

#define kDrawingScaleFactor .4

#define kLineSegmentSize 1

void _FieldDrawLine(Vector& from, Vector& to)
{
	Vector start;
	memcpy(start, from, sizeof(Vector));

	Vector diff;
	VectorSubtract(to, from, diff);

	Vector dl;	//	this is how far we go each iteration
	VectorScalarMultiply(diff, kLineSegmentSize / VectorGetMagnitude(diff), dl);

	Vector finish;


	nxtDrawLine(from.x, from.y, to.x, to.y);
}



void _FieldDrawLines()
{
   for ( Node i = 0; i < kNodeCount; i++ )
   {


     for ( Node j = 0; j < kNodeCount; j++ )
     {
        if ( FieldNodesAreConnected(i, j) && j > i )
        {


          Vector from;
          memcpy(from, globalField.nodes[i].location, sizeof(Vector));
          VectorScalarMultiply(from, kDrawingScaleFactor, from);

          Vector to;
          memcpy(to, globalField.nodes[j].location, sizeof(Vector));
          VectorScalarMultiply(to, kDrawingScaleFactor, to);

          _FieldDrawLine(from, to);
       }
     }
   }
}


void _FieldDrawNodes()
{
    float radius = 2.0;
    float diameter = 2.0 * radius;
		for ( Node node = 0; node < kNodeCount; node++ )
		{
				Vector location;
				memcpy(location, globalField.nodes[node].location, sizeof(Vector));
				location.x *= kDrawingScaleFactor;
				location.x -= radius;
				location.y *= kDrawingScaleFactor;
				location.y -= radius;
			//	nxtDrawCircle(location.x - (diameter / 2), location.y - (diameter / 2), diameter);
				nxtFillEllipse(location.x, location.y + diameter, location.x + diameter, location.y);
		}
}



void FieldDraw()
{
		eraseDisplay();

		nxtDrawRect(0, 144 * kDrawingScaleFactor, 144 * kDrawingScaleFactor, 0);

		_FieldDrawNodes();
		_FieldDrawLines();

		nxtDisplayStringAt(kDisplaySize + 10, kDisplaySize * .8, "B");
		nxtDisplayStringAt(kDisplaySize + 10, kDisplaySize * .4, "R");

}


task FieldContinuouslyFriendraw()
{
  while ( true )
  {
    FieldDraw();

    Vector location;


    //  show position of robot.  get this info from the tracker
    RobotPosition position;
    TrackerGetCurrentPosition(position);
    memcpy(location, position.location, sizeof(Vector));





    VectorScalarMultiply(location, kDrawingScaleFactor, location);  //  scale it for drawing



    //  draws box where roboat is
    float rectHalfSize = 3;
    nxtFillRect(location.x - rectHalfSize, location.y + rectHalfSize, location.x + rectHalfSize, location.y - rectHalfSize);



    //  below code draws a line from the center of the box out a little to show orientation of robot
    float s = sin(position.orientation + (PI / 2));
    float c = cos(position.orientation + (PI / 2));
    float slope = s / c;

    float length = rectHalfSize * 3;



    float dx;
    float dy;

    if ( c != 0 )
    {
      float a = powf(abs(length), 2) / (powf(abs(slope), 2) + 1);
      dx = sqrt( abs(a) );
      if ( c < 0 ) dx = -abs(dx); //  make it negative
      dy = dx * slope;
    }
    else
    {
      dx = 0;
      dy = s * length;
    }

   nxtDrawLine(location.x, location.y, location.x + dx, location.y + dy);





    wait10Msec(50);
  }
}

*/



















//	Dijkstra's Algorithm
//=========================================================================================================

#define kInfinity 100000


bool touched[kNodeCount];



void _Travel(Node n)
{
  traveled[n] = true;

  for ( Node i = 0; i < kNodeCount; i++ )
  {
    if ( FieldNodesAreConnected(n, i) )
    {
      touched[i] = true;

      float totalCost = globalField.pathCosts[n][i] + tentativeCosts[n];	//	cost from our current position to n + cost from start to current position

			if ( totalCost < tentativeCosts[i] )	//	we found a path shorter than the one previously recorded
			{
				tentativeCosts[i] = totalCost;		//	new shortest cost to get to n
				previous[i] = n;				//	shortest path to get to n
			}
    }
  }
}



void FieldRecalculatePath()
{
   globalField.currentNodeIndex = 0;	//	we're at the first node

	//	reset the dijkstra algorithm caches before we use them
	for ( Node n = 0; n < kNodeCount; n++ )
	{
		previous[n] = NodeZero;
		tentativeCosts[n] = kInfinity;
		traveled[n] = false;
		touched[n] = false;
	}



	Node src = globalField.cachedPath[0];



	//	clear previous path
	for ( Node n = 0; n < kNodeCount; n++ )
	{
		globalField.cachedPath[n] = NodeZero;
	}



	tentativeCosts[src] = 0;

	_Travel(src);			//	start at 'from' and find shortest path

	while ( true )
	{
	  bool madeProgress = false;

	  for ( Node i = 0; i < kNodeCount; i++ )
	  {
	    if ( touched[i] && !traveled[i] )
	    {
	      _Travel(i);
	      madeProgress = true;
	    }
	  }

	  if ( !madeProgress ) break; //  go until there's no more to do
	}






	//	count how many segments are in the path
	int pathItemCount = 0;									//	number of nodes in the path including the start and the finish
	for ( Node n = globalField.goalNode; n != NodeZero; n = previous[n] ) //	iterate through the path until we hit the beginning
	{
		pathItemCount++;				//	increment count
	}


	if ( pathItemCount > 1 )	//	see if we even have a path
	{
		//	store the path for later use
		int i = pathItemCount - 1;	//	index in cachedPath where we'll put the node id
		for ( Node n = globalField.goalNode; i >= 0; i-- )
		{
			globalField.cachedPath[i] = n;
			n = previous[n];
		}
	}


	globalField.cached = true;	//	we just cached the results
}

















/*
void _FieldTravelNode(Node node);
void _CallFieldTravelNode(Node node)
{
	_FieldTravelNode(node);	//	this function is here b/c robotc doesn't allow recursive functions.	 this is just an easy work-around
}


void _FieldTravelNode(Node node)
{
	traveled[node] = true;

	//printf("traveling node %d\n", Node);

	for ( Node n = 0; n < kNodeCount; n++ )
	{
		if ( FieldNodesAreConnected(node, n) )	//	if they're connected, lets see if we have a shorter path
		{
			float totalCost = globalField.pathCosts[node][n] + tentativeCosts[node];	//	cost from our current position to n + cost from start to current position

			//printf("cost from %d to %d is %f\n", Node, n, totalCost);
			//printf("tentative cost to %d is %f\n", n, tentativeCosts[n]);

			if ( totalCost < tentativeCosts[n] )	//	we found a path shorter than the one previously recorded
			{
				//printf("found new shortest path to %d with cost %f\n", n, totalCost);
				tentativeCosts[n] = totalCost;		//	new shortest cost to get to n
				previous[n] = node;				//	shortest path to get to n
			}
		}
	}

	for ( Node n = 0; n < kNodeCount; n++ ) //	loop through each node
	{
		if ( FieldNodesAreConnected(node, n) && traveled[n] == false )
		{
			//printf("traveling to %d from %d\n", n, Node);
			_CallFieldTravelNode(n);	//	if we're connected and it hasn't been traveled, travel it
		}
	}
}
*/




/*
void _FieldPrintPath()
{
	//printf("\n\npath:\n");

	for ( Node n = 0; n < kNodeCount; n++ )
	{
		Node id = globalField.cachedPath[n];
		if ( id == NodeZero ) break;	//	stop if we hit the end

		//printf("%s", globalField.nodes[id].name);
		//printf("\n");
	}

	//printf("\n");
}
*/




//	Field


void FieldConnectNodesAutomatically(Node n1, Node n2, bool bidirectional)
{
 Vector v1;
 memcpy(v1, globalField.nodeInfo[n1].location, sizeof(Vector));

 Vector v2;
 memcpy(v2, globalField.nodeInfo[n2].location, sizeof(Vector));


	Vector diff;
	VectorSubtract(v1, v2, diff);

	float distance = VectorGetMagnitude(diff);

	globalField.pathCosts[n1][n2] = distance;
	if ( bidirectional ) globalField.pathCosts[n2][n1] = distance;
}


bool FieldNodesAreConnected(Node n1, Node n2)
{
	return globalField.pathCosts[n1][n2] != kInfinity && (nPgmTime > globalField.validationTimes[n1][n2]);	//	it's valid and not infinite
}

void FieldTemporarilyInvalidatePathBetweenNodes(Node n1, Node n2, int time)	//	tell it there is no path between the two given nodes.  order DOESN'T matter
{
  int validTime = time + nPgmTime;
	globalField.validationTimes[n1][n2] = validTime;
	globalField.validationTimes[n2][n1] = validTime;
}


void FieldSetCurrentNode(Node current)
{
	globalField.cachedPath[0] = current;	//	set first node in path to given node id
	globalField.cached = false;			//	tell it to update next time it needs path info
}

Node FieldGetCurrentNode()
{
	return globalField.cachedPath[globalField.currentNodeIndex];
}


void FieldSetGoalNode(Node goal)
{
	globalField.goalNode = goal;
	globalField.cached = false; //	tell it that it needs to update the cache
}

/*
void FieldRecalculatePath()
{

	globalField.currentNodeIndex = 0;	//	we're at the first node

	//	reset the dijkstra algorithm caches before we use them
	for ( Node n = 0; n < kNodeCount; n++ )
	{
		previous[n] = NodeZero;
		tentativeCosts[n] = kInfinity;
		traveled[n] = false;
	}



	Node src = globalField.cachedPath[0];



	//	clear previous path
	for ( Node n = 0; n < kNodeCount; n++ )
	{
		globalField.cachedPath[n] = NodeZero;
	}



	tentativeCosts[src] = 0;

	_FieldTravelNode(src);			//	start at 'from' and find shortest path


	//	count how many segments are in the path
	int pathItemCount = 0;									//	number of nodes in the path including the start and the finish
	for ( Node n = globalField.goalNode; n != NodeZero; n = previous[n] ) //	iterate through the path until we hit the beginning
	{
		pathItemCount++;				//	increment count
	}


	if ( pathItemCount > 1 )	//	see if we even have a path
	{
		//	store the path for later use
		int i = pathItemCount - 1;	//	index in cachedPath where we'll put the node id
		for ( Node n = globalField.goalNode; i >= 0; i-- )
		{
			globalField.cachedPath[i] = n;
			n = previous[n];
		}
	}


	globalField.cached = true;	//	we just cached the results
}
*/


Node FieldGetNextNode()
{
	if ( !globalField.cached ) FieldRecalculatePath();	//	recalculate if necessary
	return globalField.cachedPath[globalField.currentNodeIndex + 1];
}



void FieldAdvance() //	Sets current node to next node and returns the next node after that
{
	if ( !globalField.cached ) FieldRecalculatePath();	//	recalculate if necessary

	++globalField.currentNodeIndex;	//	set the index to the next node
}


void FieldSetNodeCoordinates(Node n, float x, float y, float z)
{
	Vector location;
	VectorMake(x, y, z, location);
	FieldSetNodeLocation(n, location);
}


void FieldSetNodeLocation(Node n, Vector& location)
{
	memcpy(globalField.nodeInfo[n].location, location, sizeof(Vector));
}


void FieldGetNodeLocation(Node n, Vector& locationOut)
{
	memcpy(locationOut, globalField.nodeInfo[n].location, sizeof(Vector));
}

Node FieldGetGoalNode()
{
	return globalField.goalNode;
}




void FieldSetPathSegmentFlags(PathSegment& segment, PathSegmentFlags flags)
{
	globalField.segmentFlags[segment.source][segment.destination] = flags;
}

PathSegmentFlags FieldGetPathSegmentFlags(PathSegment& segment)
{
	return globalField.segmentFlags[segment.source][segment.destination];
}










//		Field Setup
//========================================================================================================================




void FieldInit()		//	sets values specific to our field.
{

	//	sets cost from each node to itself to zero, and the rest to infinity.	 clears all Nodes from nodes array.	 clears cachedPath.
	for ( Node i = 0; i < kNodeCount; i++ )
	{
		for ( Node j = 0; j < kNodeCount; j++ )
		{
			if ( j == i )
			{
				globalField.pathCosts[i][j] = 0;	//	there's a cost of zero to go from a node to itself
			}
			else
			{
				globalField.pathCosts[i][j] = kInfinity;	//	default value of infinity says there's no path between i & j
			}

			globalField.validationTimes[i][j] = 0;
		}


		globalField.cachedPath[i] = NodeZero; //	clear each node in the cached path
	}

	globalField.currentNodeIndex = 0;	//	we're at the first node in the path




	/**********		Start Squares		**********/
	#define kStartPointDistanceFromFieldEnd (((kRobotLength + kStartSquareWidth) / 2) - kRotationPointDistanceFromFront)
	FieldSetNodeCoordinates(NodeFriendStartSquareLeft, kStartSquareWidth / 2, kStartPointDistanceFromFieldEnd, 0);
	FieldSetNodeCoordinates(NodeFriendStartSquareRight, kFieldSize - (kStartSquareWidth / 2), kStartPointDistanceFromFieldEnd, 0);
	FieldSetNodeCoordinates(NodeFoeStartSquareLeft, kStartSquareWidth / 2, kFieldSize - kStartPointDistanceFromFieldEnd, 0);
	FieldSetNodeCoordinates(NodeFoeStartSquareRight, kFieldSize - (kStartSquareWidth / 2), kFieldSize - kStartPointDistanceFromFieldEnd, 0);


	/**********		Dispensers		**********/
	FieldSetNodeCoordinates(NodeFriendDispenserLeft, kDispenserPerpendicularDistance, kFieldSize - kSideDispenserDistanceFromFieldEnd, 0);
	FieldSetNodeCoordinates(NodeFriendDispenserCenter, kFieldSize / 2, kFieldSize - kDispenserPerpendicularDistance, 0);
	FieldSetNodeCoordinates(NodeFriendDispenserRight, kFieldSize - kDispenserPerpendicularDistance, kFieldSize - kSideDispenserDistanceFromFieldEnd, 0);

	FieldSetNodeCoordinates(NodeFoeDispenserLeft, kDispenserPerpendicularDistance, kSideDispenserDistanceFromFieldEnd, 0);
	FieldSetNodeCoordinates(NodeFoeDispenserCenter, kFieldSize / 2, kDispenserPerpendicularDistance, 0);
	FieldSetNodeCoordinates(NodeFoeDispenserRight, kFieldSize - kDispenserPerpendicularDistance, kSideDispenserDistanceFromFieldEnd, 0);



	/**********		Bridges		**********/
	FieldSetNodeCoordinates(NodeFriendBridgeCenter, kFieldSize - kLineDistanceFromFieldSide, kFieldSize / 2, kBridgeHeight);
	FieldSetNodeCoordinates(NodeFoeBridgeCenter, kLineDistanceFromFieldSide, kFieldSize / 2, kBridgeHeight);



	/**********		Pit Goals		**********/
	//FieldSetNodeCoordinates(??Node??, kFieldSize - (kPitWidth / 2), (kFieldSize / 2) - (kPitLength / 2), location);
	//FieldSetNodeLocation(NodeFriendPitCenter, "R pit goal cntr", location);

	//FieldSetNodeCoordinates(??Node??, kPitWidth / 2, (kFieldSize / 2) + (kPitLength / 2), location);
	//FieldSetNodeLocation(NodeFoePitCenter, "B pit goal cntr", location);


	/**********		Mountain		**********/
	//FieldSetNodeCoordinates(??Node??, kFieldSize / 2, (kFieldSize / 2) + (kMountainLength / 2), location);
	//FieldSetNodeLocation(NodeMountainCenterTopEdge, "mntn cntr top edge", location);

	//VectorMake(kFieldSize / 2, kFieldSize / 2, kMountainHeight, location);
	//FieldSetNodeLocation(NodeMountainCenterPeak, "mntn cntr peak", location);

	//FieldSetNodeCoordinates(??Node??, kFieldSize / 2, (kFieldSize / 2) - (kMountainLength / 2), location);
	//FieldSetNodeLocation(NodeMountainCenterBottomEdge, "mntn cntr btm edge", location);




	/**********		White Lines		**********/
	//FieldSetNodeCoordinates(NodeLine1Bottom, kLineDistanceFromFieldSide, kLineDistanceFromFieldEnd + kLightSensorDistanceFromCenter, 0);				//	line 1
	FieldSetNodeCoordinates(NodeLine1Top, kLineDistanceFromFieldSide, ((kFieldSize  - kBridgeLength) / 2) - kRobotRadius, 0);
	FieldSetNodeCoordinates(NodeLine1BottomEnd, kLineDistanceFromFieldSide, kLineDistanceFromFieldEnd, 0);

	FieldSetNodeCoordinates(NodeLine2Bottom, kFieldSize / 2, kLineDistanceFromFieldEnd + kLightSensorDistanceFromCenter, 0);							//	line 2
	FieldSetNodeCoordinates(NodeLine2Top, kFieldSize / 2, ((kFieldSize - kMountainLength) / 2) - kRobotRadius, 0);
	FieldSetNodeCoordinates(NodeLine2BottomEnd, kFieldSize / 2, kLineDistanceFromFieldEnd, 0);

	//FieldSetNodeCoordinates(NodeLine3Bottom, kFieldSize - kLineDistanceFromFieldSide, kLineDistanceFromFieldEnd + kLightSensorDistanceFromCenter, 0);	//	line 3
	FieldSetNodeCoordinates(NodeLine3Top, kFieldSize - kLineDistanceFromFieldSide, ((kFieldSize  - kBridgeLength) / 2) - kRobotRadius, 0);
  FieldSetNodeCoordinates(NodeLine3BottomEnd, kFieldSize - kLineDistanceFromFieldSide, kLineDistanceFromFieldEnd, 0);

	FieldSetNodeCoordinates(NodeLine4Bottom, kLineDistanceFromFieldSide, ((kFieldSize + kBridgeLength) / 2) + kRobotRadius, 0);							//	line 4
	FieldSetNodeCoordinates(NodeLine4Top, kLineDistanceFromFieldSide, kFieldSize - (kLineDistanceFromFieldEnd + kLightSensorDistanceFromCenter), 0);
  FieldSetNodeCoordinates(NodeLine4TopEnd, kLineDistanceFromFieldSide, kFieldSize - kLineDistanceFromFieldEnd, 0);

	//FieldSetNodeCoordinates(NodeLine5Bottom, kFieldSize / 2, ((kFieldSize + kMountainLength) / 2) + kRobotRadius, 0);									//	line 5
	FieldSetNodeCoordinates(NodeLine5Top, kFieldSize / 2, kFieldSize - (kLineDistanceFromFieldEnd + kLightSensorDistanceFromCenter), 0);
  FieldSetNodeCoordinates(NodeLine5TopEnd, kFieldSize / 2, kFieldSize - kLineDistanceFromFieldEnd, 0);

	FieldSetNodeCoordinates(NodeLine6Bottom, kFieldSize - kLineDistanceFromFieldSide, ((kFieldSize + kBridgeLength) / 2) + kRobotRadius, 0);			//	line 6
	FieldSetNodeCoordinates(NodeLine6Top, kFieldSize - kLineDistanceFromFieldSide, kFieldSize - (kLineDistanceFromFieldEnd + kLightSensorDistanceFromCenter), 0);
  FieldSetNodeCoordinates(NodeLine6TopEnd, kFieldSize - kLineDistanceFromFieldSide, kFieldSize - kLineDistanceFromFieldEnd, 0);


	//	Tell it where the white lines are
	#define ADD_WHITE_LINE(n1, n2) globalField.segmentFlags[n1][n2] |= PathSegmentFlagWhiteConnectingLine
	ADD_WHITE_LINE(NodeLine1BottomEnd, NodeLine1Top);	//	line 1
	ADD_WHITE_LINE(NodeLine2BottomEnd, NodeLine2Bottom);	//	line 2
	
	ADD_WHITE_LINE(NodeLine2BottomEnd, NodeLine2Bottom);
	ADD_WHITE_LINE(NodeLine2Bottom, NodeLine2Top);
	ADD_WHITE_LILNE(NodeLine2Top, NodeLine2Bottom);

	ADD_WHITE_LINE(NodeLine3Bottom, NodeLine3Top);	//	line 3
	ADD_WHITE_LINE(NodeLine4Bottom, NodeLine4Top);	//	line 4
	ADD_WHITE_LINE(NodeLine5Bottom, NodeLine5Top);	//	line 5

	ADD_WHITE_LINE(NodeLine4TopEnd, NodeLine4Top);
	ADD_WHITE_LINE(NodeLine4Top, NodeLine4Bottom);
	ADD_WHITE_LINE(NodeLine4Bottom, NodeLine4Top);

	ADD_WHITE_LINE(NodeLine6Bottom, NodeLine6Top);	//	line 6


  #define ADD_LINE_END(n) globalField.nodeInfo[n].flags |= NodeFlagLineEnd
	ADD_LINE_END(NodeLine1Bottom);
	ADD_LINE_END(NodeLine2Bottom);
	ADD_LINE_END(NodeLine3Bottom);
	ADD_LINE_END(NodeLine4Top);
	ADD_LINE_END(NodeLine5Top);
	ADD_LINE_END(NodeLine6Top);



  #define ADD_PERPINDICULAR_WHITE_LINE(n1, n2) globalField.segmentFlags[n1][n2] |= PathSegmentFlagPerpendicularWhiteLineAtEnd
	ADD_PERPINDICULAR_WHITE_LINE(NodeLine1Top, NodeLine2Bottom);
	ADD_PERPINDICULAR_WHITE_LINE(NodeLine2Bottom, NodeLine1Top);
	ADD_PERPINDICULAR_WHITE_LINE(NodeLine2Bottom, NodeLine3Top);
	ADD_PERPINDICULAR_WHITE_LINE(NodeLine3Top, NodeLine2Bottom);

	ADD_PERPINDICULAR_WHITE_LINE(NodeLine4Bottom, NodeLine5Top);
	ADD_PERPINDICULAR_WHITE_LINE(NodeLine5Top, NodeLine4Bottom);
	ADD_PERPINDICULAR_WHITE_LINE(NodeLine5Top, NodeLine6Bottom);
	ADD_PERPINDICULAR_WHITE_LINE(NodeLine6Bottom, NodeLine5Top);

	//  NOTE: I commented out the ones for the bridge because the contrast between the white tape
	//  and the color of the bridges wasn't enough to be able to differentiate b/w the 2
	//ADD_PERPINDICULAR_WHITE_LINE(NodeLine1Top, NodeFoeBridgeCenter);
	//ADD_PERPINDICULAR_WHITE_LINE(NodeLine4Bottom, NodeFoeBridgeCenter);

	//ADD_PERPINDICULAR_WHITE_LINE(NodeLine3Top, NodeFriendBridgeCenter);
	//ADD_PERPINDICULAR_WHITE_LINE(NodeLine6Bottom, NodeFriendBridgeCenter);



	//	Tell it where the bridge entrances are
	#define ADD_BRIDGE_ENTRANCE(n1, n2) globalField.segmentFlags[n1][n2] |= PathSegmentFlagBridgeEntrance
	ADD_BRIDGE_ENTRANCE(NodeLine1Top, NodeFoeBridgeCenter);	//	Foe bridge
	ADD_BRIDGE_ENTRANCE(NodeLine4Bottom, NodeFoeBridgeCenter);	//

	ADD_BRIDGE_ENTRANCE(NodeLine3Top, NodeFriendBridgeCenter);		//	Friend bridge
	ADD_BRIDGE_ENTRANCE(NodeLine6Bottom, NodeFriendBridgeCenter);	//





	/******************************		Connections between Nodes ******************************/


//	FIXME: change everything that references line nodes!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	/**********		Start Squares **********/
	FieldConnectNodesAutomatically(NodeFriendStartSquareLeft, NodeFoeDispenserLeft, true);
	FieldConnectNodesAutomatically(NodeFriendStartSquareLeft, NodeFoeDispenserCenter, true);
	FieldConnectNodesAutomatically(NodeFriendStartSquareLeft, NodeLine1Bottom, true);

	FieldConnectNodesAutomatically(NodeFriendStartSquareRight, NodeFoeDispenserCenter, true);
	FieldConnectNodesAutomatically(NodeFriendStartSquareRight, NodeFoeDispenserRight, true);
	FieldConnectNodesAutomatically(NodeFriendStartSquareRight, NodeLine3Bottom, true);


	FieldConnectNodesAutomatically(NodeFoeStartSquareLeft, NodeFriendDispenserLeft, true);
	FieldConnectNodesAutomatically(NodeFoeStartSquareLeft, NodeFriendDispenserCenter, true);
	FieldConnectNodesAutomatically(NodeFoeStartSquareLeft, NodeLine4Top, true);

	FieldConnectNodesAutomatically(NodeFoeStartSquareRight, NodeFriendDispenserCenter, true);
	FieldConnectNodesAutomatically(NodeFoeStartSquareRight, NodeFriendDispenserRight, true);
	FieldConnectNodesAutomatically(NodeFoeStartSquareRight, NodeLine6Top, true);


	/**********		Bridge Centers		**********/
	FieldConnectNodesAutomatically(NodeFriendBridgeCenter, NodeLine6Bottom, true);
	FieldConnectNodesAutomatically(NodeFriendBridgeCenter, NodeLine3Top, true);

	FieldConnectNodesAutomatically(NodeFoeBridgeCenter, NodeLine4Bottom, true);
	FieldConnectNodesAutomatically(NodeFoeBridgeCenter, NodeLine1Top, true);


	/**********		Mountain	**********/
	//FieldConnectNodesAutomatically(NodeMountainCenterPeak, NodeMountainCenterTopEdge, true);
	//FieldConnectNodesAutomatically(NodeMountainCenterPeak, NodeMountainCenterBottomEdge, true);


	/**********		Pits	**********/
	//FieldConnectNodesAutomatically(NodeFriendPitCenter, NodeFoeDispenserRight, true);
	//FieldConnectNodesAutomatically(NodeFoePitCenter, NodeFriendDispenserLeft, true);


	/**********		White Lines	**********/	//	FIXME: redo these connections to respect the new design
	FieldConnectNodesAutomatically(NodeLine1Bottom, NodeLine1Top, true);
	FieldConnectNodesAutomatically(NodeLine1Bottom, NodeFoeDispenserLeft, true);
	FieldConnectNodesAutomatically(NodeLine1Bottom, NodeLine2Bottom, true);
	FieldConnectNodesAutomatically(NodeLine1Bottom, NodeFoeDispenserCenter, true);
	FieldConnectNodesAutomatically(NodeLine1Top, NodeFoeDispenserLeft, true);

	FieldConnectNodesAutomatically(NodeLine2Bottom, NodeLine2Top, true);
	FieldConnectNodesAutomatically(NodeLine2Bottom, NodeFoeDispenserCenter, true);
	FieldConnectNodesAutomatically(NodeLine2Bottom, NodeLine1Top, true);
	FieldConnectNodesAutomatically(NodeLine2Bottom, NodeLine3Top, true);

	FieldConnectNodesAutomatically(NodeLine3Bottom, NodeLine3Top, true);
	FieldConnectNodesAutomatically(NodeLine3Bottom, NodeFoeDispenserRight, true);
	FieldConnectNodesAutomatically(NodeLine3Bottom, NodeLine2Bottom, true);
	FieldConnectNodesAutomatically(NodeLine3Bottom, NodeFoeDispenserCenter, true);
	FieldConnectNodesAutomatically(NodeLine3Top, NodeFoeDispenserRight, true);


	FieldConnectNodesAutomatically(NodeLine4Top, NodeLine4Bottom, true);
	FieldConnectNodesAutomatically(NodeLine4Top, NodeFriendDispenserLeft, true);
	FieldConnectNodesAutomatically(NodeLine4Top, NodeLine5Top, true);
	FieldConnectNodesAutomatically(NodeLine4Top, NodeFriendDispenserCenter, true);
	FieldConnectNodesAutomatically(NodeLine4Bottom, NodeFriendDispenserLeft, true);

	FieldConnectNodesAutomatically(NodeLine5Top, NodeLine5Bottom, true);
	FieldConnectNodesAutomatically(NodeLine5Top, NodeFriendDispenserCenter, true);
	FieldConnectNodesAutomatically(NodeLine5Top, NodeLine4Bottom, true);
	FieldConnectNodesAutomatically(NodeLine5Top, NodeLine6Bottom, true);

	FieldConnectNodesAutomatically(NodeLine6Top, NodeLine6Bottom, true);
	FieldConnectNodesAutomatically(NodeLine6Top, NodeFriendDispenserRight, true);
	FieldConnectNodesAutomatically(NodeLine6Top, NodeLine5Top, true);
	FieldConnectNodesAutomatically(NodeLine6Top, NodeFriendDispenserCenter, true);
	FieldConnectNodesAutomatically(NodeLine6Bottom, NodeFriendDispenserRight, true);
}
