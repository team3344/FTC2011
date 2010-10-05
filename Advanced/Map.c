/*
 *  Map.c
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */

#include "Map.h"


#define INFINITY 1000000




//	caches used for dijkstra's algorithm
NodeID previous[kNodeCount];
float tentativeCosts[kNodeCount];
bool traveled[kNodeCount];


const NodeID NodeIDZero = -1;
const Node NodeZero = { PointZero, NodeTypeNone };


static Map globalMap;	//	this is the map that everything works from






void _MapResetDijkstraAlgorithmCache()
{
	for ( NodeID n = 0; n < kNodeCount; n++ )
	{
		previous[n] = NodeIDZero;
		tentativeCosts[n] = INFINITY;
		traveled[n] = false;
	}
}

//	FIXME: find path function


void _MapFindShortestPath(NodeID from, NodeID to)
{
	//	FIXME: pull in code from dijkstra.c
}






#pragma mark Map

void MapConnectNodes(NodeID n1, NodeID n2, float cost)
{
	globalMap.pathCosts[n1][n2] = cost;
	globalMap.pathCosts[n2][n1] = cost;
}



void MapInvalidatePath(NodeID n1, NodeID n2)
{
	MapConnectNodes(n1, n2, INFINITY);
}

void MapSetCurrentNodeID(NodeID current)
{
	globalMap.cachedPath[0] = current;	//	set first node in path to given node id
	globalMap.cached = false;			//	tell it to update next time it needs path info
}

NodeID MapGetCurrentNodeID()
{
	return globalMap.path[0];	//	first node in path is our current position
}


void MapSetGoalNodeID(NodeID goal)
{
	globalMap.goalNodeID = goal;
	globalMap.cached = false;	//	tell it that it needs to update the cache
}


NodeID MapAdvance()	//	Sets current node to next node and returns the next node after that
{
	for ( NodeID n = 1; n < kPathCacheSize; n++ )
	{
		globalMap.cachedPath[n - 1] = globalMap.cachedPath[n];	//	shift nodes in array over 1 slot
	}
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//	FIXME: exceptions??? recalculate???
	//	FIXME: return value???
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
				globalMap.pathCosts[i][j] = INFINITY;	//	default value of infinity says there's no path between i & j
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

void MapInit()		//	sets values specific to our field.
{
	//	FIXME: implement
	
	
	//
	
	
	//
	
	
	//
	
	
	//
	
	
	//
}





