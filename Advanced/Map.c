/*
 *  Map.c
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */

#include "Map.h"


//	caches used for dijkstra's algorithm
NodeID previous[kNodeCount];
float tentativeCosts[kNodeCount];
bool traveled[kNodeCount];


const Node NodeZero;//FIXME: set this correctly = { PointZero, NodeTypeNone, stringZero };

static Map globalMap;	//	this is the map that everything works from






#pragma mark Dijkstra's Algorithm
//=========================================================================================================



#define kInfinity 100000	//	FIXME: real value for this???





#pragma mark Map Private

void _MapResetDijkstraAlgorithmCache()
{
	for ( NodeID n = 0; n < kNodeCount; n++ )
	{
		previous[n] = NodeIDZero;
		tentativeCosts[n] = kInfinity;
		traveled[n] = false;
	}
}

void _MapTravelNode(NodeID nodeID)
{
	traveled[nodeID] = true;
	
	printf("traveling node %d\n", nodeID);
	
	for ( NodeID n = 0; n < kNodeCount; n++ )
	{
		if ( MapNodesAreConnected(nodeID, n) )	//	if they're connected, lets see if we have a shorter path
		{
			float totalCost = globalMap.pathCosts[nodeID][n] + tentativeCosts[nodeID];	//	cost from our current position to n + cost from start to current position
			
			printf("cost from %d to %d is %f\n", nodeID, n, totalCost);
			printf("tentative cost to %d is %f\n", n, tentativeCosts[n]);
			
			if ( totalCost < tentativeCosts[n] )	//	we found a path shorter than the one previously recorded
			{
				printf("found new shortest path to %d with cost %f\n", n, totalCost);
				tentativeCosts[n] = totalCost;		//	new shortest cost to get to n
				previous[n] = nodeID;				//	shortest path to get to n 
			}
		}
	}
	
	for ( NodeID n = 0; n < kNodeCount; n++ )	//	loop through each node
	{
		if ( MapNodesAreConnected(nodeID, n) && traveled[n] == false )
		{
			printf("traveling to %d from %d\n", n, nodeID);
			_MapTravelNode(n);	//	if we're connected and it hasn't been traveled, travel it
		}
	}
}


void _MapPrintPath()
{
	printf("\n\npath:\n");
	
	for ( NodeID n = 0; n < kNodeCount; n++ )
	{
		NodeID id = globalMap.cachedPath[n];
		if ( id == NodeIDZero ) break;	//	stop if we hit the end
		
		printf("%d", id);
		printf("%s", globalMap.nodes[id].name);
		printf("\n");
	}
	
	printf("\n");
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
	
	
	/*	count how many segments are in the path	*/
	int pathItemCount = 0;									//	number of nodes in the path including the start and the finish
	for ( NodeID n = to; n != NodeIDZero; n = previous[n] )	//	iterate through the path until we hit the beginning
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






#pragma mark Map

void MapConnectNodesAutomatically(NodeID n1, NodeID n2)
{
	float distance = VectorGetMagnitude(VectorSubtract( globalMap.nodes[n2].location, globalMap.nodes[n1].location));
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
	return globalMap.cachedPath[0];	//	first node in path is our current position
}


void MapSetGoalNodeID(NodeID goal)
{
	globalMap.goalNodeID = goal;
	globalMap.cached = false;	//	tell it that it needs to update the cache
}


NodeID MapAdvance()	//	Sets current node to next node and returns the next node after that
{
	if ( !globalMap.cached ) _MapFindShortestPath(globalMap.cachedPath[0], globalMap.goalNodeID);
	
	for ( NodeID n = 1; n < kNodeCount; n++ )
	{
		NodeID id = globalMap.cachedPath[n];
		globalMap.cachedPath[n - 1] = id;	//	shift nodes in array over 1 slot
		
		if ( id == NodeIDZero ) break;	//	we hit the end
	}
	
	
	return globalMap.cachedPath[0];
}


void MapReset()	//	sets cost from each node to itself to zero, and the rest to infinity.  clears all Nodes from nodes array.  clears cachedPath.
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
		
		globalMap.cachedPath[i] = NodeIDZero;	//	clear each node id in the cached path
		globalMap.nodes[i] = NodeZero;			//	clear each node
	}
}

void MapSetNodeForID(NodeID nodeID, Node node)
{
	globalMap.nodes[nodeID] = node;
}


Node MapGetNode(NodeID nodeID)
{
	return globalMap.nodes[nodeID];
}

NodeID MapGetGoalNodeID()
{
	return globalMap.goalNodeID;
}



void _MapLoadDebugValues()	//	load crap values so we can test stuff	//	FIXME: this function is shenannigans
{
	MapConnectNodesAutomatically(NodeIDBlueBridgeCenter, NodeIDBlueDispenserCenter);
	MapConnectNodesAutomatically(NodeIDBlueDispenserCenter, NodeIDRedDispenserCenter);
	//MapConnectNodes(NodeIDRedBridgeCenter, NodeIDRedCenterDispenser, 15);
}


void MapSetNodeNameForID(NodeID nodeID, string name)
{
	strcpy(globalMap.nodes[nodeID].name, name);
}

void MapSetNodeLocationForID(NodeID nodeID, Vector location)
{
	globalMap.nodes[nodeID].location = location;
}






#pragma mark Field-specific details
//========================================================================================================================







#define kFieldWidth 144
#define kFieldHeight 144


#define kDispenserPerpendicularDistance 10	//	distance from a dispenser to its corresponding node
#define kSideDispenserDistanceFromFieldEnd 10

#define kStartSquareWidth 18





void MapInit()		//	sets values specific to our field.
{
	MapReset();	//	clear old values
	
	
	
	Node node;
	
	
	/**********		Start Sqruares		**********/
	MapSetNodeNameForID(NodeIDRedStartSquareLeft, "R left start sqr");
	MapSetNodeLocationForID(NodeIDRedStartSquareLeft, Vector2DMake(kStartSquareWidth / 2, kStartSquareWidth / 2) );
	
	MapSetNodeNameForID(NodeIDRedStartSquareRight, "R right start sqr");
	MapSetNodeLocationForID(NodeIDRedStartSquareRight, Vector2DMake(kFieldWidth - (kStartSquareWidth / 2), kStartSquareWidth / 2) );
	
	MapSetNodeNameForID(NodeIDBlueStartSquareLeft, "B left start sqr");
	MapSetNodeLocationForID(NodeIDBlueStartSquareLeft, Vector2DMake(kStartSquareWidth / 2, kFieldHeight - (kStartSquareWidth / 2)) );
	
	MapSetNodeNameForID(NodeIDBlueStartSquareRight, "B right start sqr");
	MapSetNodeLocationForID(NodeIDBlueStartSquareRight, Vector2DMake(kFieldWidth - (kStartSquareWidth / 2), kFieldHeight - (kStartSquareWidth / 2)) );
	
	
	
	
	
	
	
	
	
	/**********		Dispensers		**********/
	strcpy(node.name, "R left dispenser");
	node.location = Vector2DMake(kDispenserPerpendicularDistance, kSideDispenserDistanceFromFieldEnd);
	MapSetNodeForID(NodeIDRedDispenserLeft, node);
	
	strcpy(node.name, "R cntr dispenser");
	node.location = Vector2DMake(kFieldWidth / 2, kDispenserPerpendicularDistance);
	MapSetNodeForID(NodeIDRedDispenserCenter, node);
	
	strcpy(node.name, "R right dispenser");
	node.location = Vector2DMake(kFieldWidth - kDispenserPerpendicularDistance, kSideDispenserDistanceFromFieldEnd);
	MapSetNodeForID(NodeIDRedDispenserRight, node);
	
	
	
	
	
	
	
	
	
	
	
	
	
	strcpy(node.name, "B bridge center");
	node.location = Vector2DMake(20, 50);
	MapSetNodeForID(NodeIDBlueBridgeCenter, node);
	
	
	strcpy(node.name, "B cntr dispenser");
	node.location = Vector2DMake(kFieldWidth / 2, kFieldHeight - kDispenserPerpendicularDistance);
	MapSetNodeForID(NodeIDBlueDispenserCenter, node);
	
	
	
	
	
	
	MapConnectNodesAutomatically(NodeIDBlueBridgeCenter, NodeIDBlueDispenserCenter);
	MapConnectNodesAutomatically(NodeIDBlueDispenserCenter, NodeIDRedDispenserCenter);
	
	
	
	
	
	//	FIXME: implement
	
	
	//
	
	
	//
	
	
	//
	
	
	//
	
	
	//
	
	
	
	
	_MapLoadDebugValues();	//	FIXME: remove this
}







