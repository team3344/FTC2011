/*
 *	Map.c
 *	Get Over It
 *
 *	Created by Justin Buchanan on 9/11/10.
 *	Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */

#ifndef _Map_
#include "Map.h"
#endif

//	caches used for dijkstra's algorithm
NodeID previous[kNodeCount];
float tentativeCosts[kNodeCount];
bool traveled[kNodeCount];


//const Node NodeZero;//FIXME: set this correctly = { PointZero, NodeTypeNone, stringZero };

static Map globalMap; //	this is the map that everything works from







//	Map Drawing
//=========================================================================================================

#define kDisplaySize 50

#define kDrawingScaleFactor .4

#define kLineSegmentSize 1

void _MapDrawLine(Vector& from, Vector& to)
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



void _MapDrawLines()
{
   for ( NodeID i = 0; i < kNodeCount; i++ )
   {


     for ( NodeID j = 0; j < kNodeCount; j++ )
     {
        if ( MapNodesAreConnected(i, j) && j > i )
        {


          Vector from;
          memcpy(from, globalMap.nodes[i].location, sizeof(Vector));
          VectorScalarMultiply(from, kDrawingScaleFactor, from);

          Vector to;
          memcpy(to, globalMap.nodes[j].location, sizeof(Vector));
          VectorScalarMultiply(to, kDrawingScaleFactor, to);

          _MapDrawLine(from, to);
       }
     }
   }
}


void _MapDrawNodes()
{
    float radius = 2.0;
    float diameter = 2.0 * radius;
		for ( NodeID node = 0; node < kNodeCount; node++ )
		{
				Vector location;
				memcpy(location, globalMap.nodes[node].location, sizeof(Vector));
				location.x *= kDrawingScaleFactor;
				location.x -= radius;
				location.y *= kDrawingScaleFactor;
				location.y -= radius;
			//	nxtDrawCircle(location.x - (diameter / 2), location.y - (diameter / 2), diameter);
				nxtFillEllipse(location.x, location.y + diameter, location.x + diameter, location.y);
		}
}



void MapDraw()
{
		eraseDisplay();

		nxtDrawRect(0, 144 * kDrawingScaleFactor, 144 * kDrawingScaleFactor, 0);

		_MapDrawNodes();
		_MapDrawLines();

		nxtDisplayStringAt(kDisplaySize + 10, kDisplaySize * .8, "B");
		nxtDisplayStringAt(kDisplaySize + 10, kDisplaySize * .4, "R");

}


task MapContinuouslyRedraw()
{
  while ( true )
  {
    MapDraw();

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





















//	Dijkstra's Algorithm
//=========================================================================================================



#define kInfinity 100000	//	FIXME: real value for this???





// mark Map Private

void _MapResetDijkstraAlgorithmCache()
{
	for ( NodeID n = 0; n < kNodeCount; n++ )
	{
		previous[n] = NodeIDZero;
		tentativeCosts[n] = kInfinity;
		traveled[n] = false;
	}
}



//	this function is here b/c robotc doesn't allow recursive functions.	 this is just an easy work-around
void _MapTravelNode(NodeID nodeID);
void _CallMapTravelNode(NodeID nodeID)
{
 _MapTravelNode(nodeID);
}


void _MapTravelNode(NodeID nodeID)
{
	traveled[nodeID] = true;

	//printf("traveling node %d\n", nodeID);

	for ( NodeID n = 0; n < kNodeCount; n++ )
	{
		if ( MapNodesAreConnected(nodeID, n) )	//	if they're connected, lets see if we have a shorter path
		{
			float totalCost = globalMap.pathCosts[nodeID][n] + tentativeCosts[nodeID];	//	cost from our current position to n + cost from start to current position

			//printf("cost from %d to %d is %f\n", nodeID, n, totalCost);
			//printf("tentative cost to %d is %f\n", n, tentativeCosts[n]);

			if ( totalCost < tentativeCosts[n] )	//	we found a path shorter than the one previously recorded
			{
				//printf("found new shortest path to %d with cost %f\n", n, totalCost);
				tentativeCosts[n] = totalCost;		//	new shortest cost to get to n
				previous[n] = nodeID;				//	shortest path to get to n
			}
		}
	}

	for ( NodeID n = 0; n < kNodeCount; n++ ) //	loop through each node
	{
		if ( MapNodesAreConnected(nodeID, n) && traveled[n] == false )
		{
			//printf("traveling to %d from %d\n", n, nodeID);
			_CallMapTravelNode(n);	//	if we're connected and it hasn't been traveled, travel it
		}
	}
}


void _MapPrintPath()
{
	//printf("\n\npath:\n");

	for ( NodeID n = 0; n < kNodeCount; n++ )
	{
		NodeID id = globalMap.cachedPath[n];
		if ( id == NodeIDZero ) break;	//	stop if we hit the end

		//printf("%s", globalMap.nodes[id].name);
		//printf("\n");
	}

	//printf("\n");
}



void _MapClearCachedPath()
{
	for ( NodeID n = 0; n < kNodeCount; n++ )
	{
		globalMap.cachedPath[n] = NodeIDZero;
	}
}


void _MapFindShortestPath(NodeID from, NodeID to)
{
	_MapResetDijkstraAlgorithmCache();
	_MapClearCachedPath();				//	clear previous path


	tentativeCosts[from] = 0;


	_MapTravelNode(from);			//	start at 'from' and find shortest path


	/*	count how many segments are in the path */
	int pathItemCount = 0;									//	number of nodes in the path including the start and the finish
	for ( NodeID n = to; n != NodeIDZero; n = previous[n] ) //	iterate through the path until we hit the beginning
	{
		pathItemCount++;				//	increment count
	}


	if ( pathItemCount > 1 )	//	see if we even have a path
	{
		//	store the path for later use
		int i = pathItemCount - 1;	//	index in cachedPath where we'll put the node id
		for ( NodeID n = to; i >= 0; i-- )
		{
			globalMap.cachedPath[i] = n;
			n = previous[n];
		}
	}



	globalMap.cached = true;	//	we just cached the results

	_MapPrintPath();	//	FIXME: remove this
}






//	Map

void MapConnectNodesAutomatically(NodeID n1, NodeID n2)
{
 Vector v1;
 memcpy(v1, globalMap.nodes[n1].location, sizeof(Vector));

 Vector v2;
 memcpy(v2, globalMap.nodes[n2].location, sizeof(Vector));


	Vector diff;
	VectorSubtract(v1, v2, diff); //	this line is no bueno!!!!!

	float distance = VectorGetMagnitude(diff);	//	FIXME: this says distance is zero



	nxtDisplayCenteredTextLine(0, "connect");
	nxtDisplayCenteredTextLine(1, (string)v1.x);
	nxtDisplayCenteredTextLine(2, (string)v1.y);
	nxtDisplayCenteredTextLine(3, (string)v2.x);
	nxtDisplayCenteredTextLine(4, (string)v2.y);
	nxtDisplayCenteredTextLine(6, (string)distance);
	//wait10Msec(400);


	MapConnectNodes(n1, n2, distance);
	MapConnectNodes(n2, n1, distance);
}

void MapConnectNodes(NodeID n1, NodeID n2, float cost)
{
	globalMap.pathCosts[n1][n2] = cost;
}


bool MapNodesAreConnected(NodeID n1, NodeID n2)
{
	return globalMap.pathCosts[n1][n2] != kInfinity;
}


void MapInvalidatePath(NodeID n1, NodeID n2)
{
	MapConnectNodes(n1, n2, kInfinity);
}

void MapSetCurrentNodeID(NodeID current)
{
	globalMap.cachedPath[0] = current;	//	set first node in path to given node id
	globalMap.cached = false;			//	tell it to update next time it needs path info
}

NodeID MapGetCurrentNodeID()
{
	return globalMap.cachedPath[0]; //	first node in path is our current position
}


void MapSetGoalNodeID(NodeID goal)
{
	globalMap.goalNodeID = goal;
	globalMap.cached = false; //	tell it that it needs to update the cache
}


NodeID MapAdvance() //	Sets current node to next node and returns the next node after that
{
	if ( !globalMap.cached ) _MapFindShortestPath(globalMap.cachedPath[0], globalMap.goalNodeID);

	for ( NodeID n = 1; n < kNodeCount; n++ )
	{
		NodeID id = globalMap.cachedPath[n];
		globalMap.cachedPath[n - 1] = id; //	shift nodes in array over 1 slot

		if ( id == NodeIDZero ) break;	//	we hit the end
	}


	return globalMap.cachedPath[0];
}


void MapReset() //	sets cost from each node to itself to zero, and the rest to infinity.	 clears all Nodes from nodes array.	 clears cachedPath.
{
	for ( NodeID i = 0; i < kNodeCount; i++ )
	{
		for ( NodeID j = 0; j < kNodeCount; j++ )
		{
			if ( j == i )
			{
				globalMap.pathCosts[i][j] = 0;	//	there's a cost of zero to go from a node to itself
			}
			else
			{
				globalMap.pathCosts[i][j] = kInfinity;	//	default value of infinity says there's no path between i & j
			}
		}

		globalMap.cachedPath[i] = NodeIDZero; //	clear each node id in the cached path
	}
}



void MapSetNodeForID(NodeID nodeID, Node& node)
{
	globalMap.nodes[nodeID] = node;
}


void MapGetNode(NodeID nodeID, Node& nodeOut)
{
	memcpy(nodeOut, globalMap.nodes[nodeID], sizeof(Node));
}

NodeID MapGetGoalNodeID()
{
	return globalMap.goalNodeID;
}



void MapSetNodeInfoForID(NodeID nodeID, string name, Vector& location)
{
	globalMap.nodes[nodeID].name = name;
	memcpy(globalMap.nodes[nodeID].location, location, sizeof(Vector));
}


void MapSetNodeNameForID(NodeID nodeID, string name)
{
	strcpy(globalMap.nodes[nodeID].name, name);
}






//		Field-specific details
//========================================================================================================================




//	note: width is the dimension that runs along the x-axis, and length runs along the y-axis


#define kFieldWidth 144
#define kFieldLength 144


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





void MapInit()		//	sets values specific to our field.
{
	MapReset(); //	clear old values

	Vector location;

	/**********		Start Squares		**********/
	Vector2DMake(kStartSquareWidth / 2, kStartSquareWidth / 2, location);
	MapSetNodeInfoForID(NodeIDRedStartSquareLeft, "R left start sqr", location);

	Vector2DMake(kFieldWidth - (kStartSquareWidth / 2), kStartSquareWidth / 2, location);
	MapSetNodeInfoForID(NodeIDRedStartSquareRight, "R right start sqr", location);

	Vector2DMake(kStartSquareWidth / 2, kFieldLength - (kStartSquareWidth / 2), location);
	MapSetNodeInfoForID(NodeIDBlueStartSquareLeft, "B left start sqr", location);

	Vector2DMake(kFieldWidth - (kStartSquareWidth / 2), kFieldLength - (kStartSquareWidth / 2), location);
	MapSetNodeInfoForID(NodeIDBlueStartSquareRight, "B right start sqr", location);


	/**********		Dispensers		**********/
	Vector2DMake(kDispenserPerpendicularDistance, kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(NodeIDRedDispenserLeft, "R left dispenser", location);

	Vector2DMake(kFieldWidth / 2, kFieldLength - kDispenserPerpendicularDistance, location);
	MapSetNodeInfoForID(NodeIDRedDispenserCenter, "R cntr dispenser", location);

	Vector2DMake(kFieldWidth - kDispenserPerpendicularDistance, kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(NodeIDRedDispenserRight, "R right dispenser", location);

	Vector2DMake(kDispenserPerpendicularDistance, kFieldLength - kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(NodeIDBlueDispenserLeft, "B left dispenser", location);

	Vector2DMake(kFieldWidth / 2, kDispenserPerpendicularDistance, location);
	MapSetNodeInfoForID(NodeIDBlueDispenserCenter, "B cntr dispenser", location);

	Vector2DMake(kFieldWidth - kDispenserPerpendicularDistance, kFieldLength - kSideDispenserDistanceFromFieldEnd, location);
	MapSetNodeInfoForID(NodeIDBlueDispenserRight, "B right dispenser", location);



	/**********		Bridges		**********/
	Vector2DMake(kFieldWidth - kBridgeDistanceFromSide, (kFieldLength / 2) + (kBridgeLength / 2), location);
	MapSetNodeInfoForID(NodeIDRedBridgeTop, "R bridge top", location);

	VectorMake(kFieldWidth - kBridgeDistanceFromSide, kFieldLength / 2, kBridgeHeight, location);
	MapSetNodeInfoForID(NodeIDRedBridgeCenter, "R bridge cntr", location);

	Vector2DMake(kFieldWidth - kBridgeDistanceFromSide, (kFieldLength / 2) - (kBridgeLength / 2), location);
	MapSetNodeInfoForID(NodeIDRedBridgeBottom, "R bridge btm", location);

	Vector2DMake(kBridgeDistanceFromSide, (kFieldLength / 2) + (kBridgeLength / 2), location);
	MapSetNodeInfoForID(NodeIDBlueBridgeTop, "B bridge top", location);


	VectorMake(kBridgeDistanceFromSide, kFieldLength / 2, kBridgeHeight, location);
	MapSetNodeInfoForID(NodeIDBlueBridgeCenter, "B bridge cntr", location);

	Vector2DMake(kBridgeDistanceFromSide, (kFieldLength / 2) - (kBridgeLength / 2), location);
	MapSetNodeInfoForID(NodeIDBlueBridgeBottom, "B bridge btm", location);



	/**********		Pit Goals		**********/
	Vector2DMake(kFieldWidth - (kPitWidth / 2), (kFieldLength / 2) - (kPitLength / 2), location);
	MapSetNodeInfoForID(NodeIDRedPitCenter, "R pit goal cntr", location);

	Vector2DMake(kPitWidth / 2, (kFieldLength / 2) + (kPitLength / 2), location);
	MapSetNodeInfoForID(NodeIDBluePitCenter, "B pit goal cntr", location);


	/**********		Mountain		**********/
	Vector2DMake(kFieldWidth / 2, (kFieldLength / 2) + (kMountainLength / 2), location);
	MapSetNodeInfoForID(NodeIDMountainCenterTopEdge, "mntn cntr top edge", location);

	VectorMake(kFieldWidth / 2, kFieldLength / 2, kMountainHeight, location);
	MapSetNodeInfoForID(NodeIDMountainCenterPeak, "mntn cntr peak", location);

	Vector2DMake(kFieldWidth / 2, (kFieldLength / 2) - (kMountainLength / 2), location);
	MapSetNodeInfoForID(NodeIDMountainCenterBottomEdge, "mntn cntr btm edge", location);




	/******************************		Connections between Nodes ******************************/


	/**********		Start Squares **********/

	MapConnectNodesAutomatically(NodeIDRedStartSquareLeft, NodeIDBlueDispenserLeft);	//	FIXME: this line is causing a freeze
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

	MapConnectNodesAutomatically(NodeIDBlueDispenserCenter, NodeIDMountainCenterBottomEdge);
	MapConnectNodesAutomatically(NodeIDRedDispenserCenter, NodeIDMountainCenterTopEdge);



	//	FIXME: finish implementation
}
