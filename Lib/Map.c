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

/*
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




*/
















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


void _MapClearCachedPath()
{
	for ( NodeID n = 0; n < kNodeCount; n++ )
	{
		globalMap.cachedPath[n] = NodeIDZero;
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
}



/*
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
*/




//	Map

void MapConnectNodesAutomatically(NodeID n1, NodeID n2)
{
 Vector v1;
 memcpy(v1, globalMap.nodes[n1].location, sizeof(Vector));

 Vector v2;
 memcpy(v2, globalMap.nodes[n2].location, sizeof(Vector));


	Vector diff;
	VectorSubtract(v1, v2, diff);

	float distance = VectorGetMagnitude(diff);

	MapConnectNodes(n1, n2, distance);
	MapConnectNodes(n2, n1, distance);
}

void MapConnectNodes(NodeID n1, NodeID n2, float cost)
{
	globalMap.pathCosts[n1][n2] = cost;
}


bool MapNodesAreConnected(NodeID n1, NodeID n2)
{
	return globalMap.pathCosts[n1][n2] != kInfinity && MapPathBetweenNodesIsValid(n1, n2);	//	it's valid and not infinite
}

void MapInvalidatePathBetweenNodes(NodeID n1, NodeID n2, int time)	//	tell it there is no path between the two given nodes.  order DOESN'T matter
{
  int validTime = time + nPgmTime;
	globalMap.validationTimes[n1][n2] = validTime;
	globalMap.validationTimes[n2][n1] = validTime;
}

bool MapPathBetweenNodesIsValid(NodeID n1, NodeID n2)
{
	return nPgmTime > globalMap.validationTimes[n1][n2];
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


NodeID MapGetNextNodeID()
{
	return globalMap.cachedPath[globalMap.currentNode + 1];
}


NodeID MapGetPreviousNodeID()
{
	if ( globalMap.currentNode == 0 ) return NodeIDZero;
	return globalMap.cachedPath[globalMap.currentNode - 1];
}


NodeID MapRetract()
{
	globalMap.currentNode = MAX(globalMap.currentNode - 1, 0);	//	don't let it go before zero

	if ( globalMap.currentNode == 0 ) return NodeIDZero;	//	there's not a node before the first one
	return globalMap.cachedPath[globalMap.currentNode - 1];
}


NodeID MapAdvance() //	Sets current node to next node and returns the next node after that
{
	if ( !globalMap.cached ) _MapFindShortestPath(globalMap.cachedPath[0], globalMap.goalNodeID);

	++globalMap.currentNode;	//	set the index to the next node

	return globalMap.cachedPath[globalMap.currentNode];
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

			globalMap.validationTimes[i][j] = 0;
		}

		globalMap.cachedPath[i] = NodeIDZero; //	clear each node id in the cached path
	}

	globalMap.currentNode = 0;	//	we're at the first node in the path
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
