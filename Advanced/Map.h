/*
 *  Map.h
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */


#import "Vector.h"
#import "Geometry.h"


#import "RobotC_Defines.h"	//	FIXME: remove this
#import <stdio.h>
#import <stdlib.h>




typedef enum {
	LandmarkWhiteLineEnd,
	LandmarkWhiteLineMiddle
} Landmark;






typedef enum {
	NodeIDZero = 0,
	
	
	//	dispensers
	NodeIDBlueLeftDispenser,
	NodeIDBlueCenterDispenser,
	NodeIDBlueRightDispenser,
	
	NodeIDRedLeftDispenser,
	NodeIDRedCenterDispenser,
	NodeIDRedRightDispenser,
	
	
	
	
	NodeIDBlueBridgeCenter,
	NodeIDRedBridgeCenter,
	
	
	
	
	
	
	
	//	goals
	
	
	NodeIDWhiteLineEnd,
	
	NodeIDBridgeCenter,
	NodeIDBridgeEnd,
	
	NodeIDHillCenter,
	NodeIDHillBase,
	
	NodeIDFieldCorner,
	
	NodeIDPitCenter,
	
	
} NodeID;


#define kNodeCount 30	//	FIXME: set legit value



//	field coordinates are in inches
//	the origin is at the corner on the red side

/************************************************
 *			*						 *(144, 144)*
 *			*						 *			*
 *	 BLUE	*						 *	 BLUE	*
 *			*						 *			*
 *			*						 *			*
 ************						 ************
 *												*
 *												*
 *												*
 *												*
 *												*
 ************************************************
 *												*
 *												*
 *												*
 *												*
 ************						*************
 *			*						*			*
 *			*						*			*
 *	 RED	*						*	 RED	*
 *			*						*			*
 * (0,0)	*						*			*
 ************************************************/





typedef struct {
	Point location;
	NodeID type;
	string name;
} Node;


extern const Node NodeZero;





//	non-directed graph (dist from A to B is equal to distance from B to A)
typedef struct {
	Node nodes[kNodeCount];
	NodeID cachedPath[kNodeCount];
	NodeID goalNodeID;
	bool cached;
	float pathCosts[kNodeCount][kNodeCount];
} Map;



bool MapNodesAreConnected(NodeID, n1, NodeID n2);
void MapConnectNodes(NodeID n1, NodeID n2, float cost);	//	tell it the distance between the two given nodes
void MapInvalidatePath(NodeID n1, NodeID n2);			//	tell it there is no path between the two given nodes

void MapSetCurrentNodeID(NodeID current);				//	tell the map where we are at the moment
NodeID MapGetCurrentNodeID();							//	ask the map where it thinks we are

void MapSetGoalNodeID(NodeID goal);						//	tell it where we want to go
NodeID MapGetGoalNodeID();
NodeID MapAdvance();									//	sets current node to next node and returns the next node after that


void MapReset();	//	sets cost from each node to itself to zero, and the rest to infinity.  clears all Nodes from nodes array.  clears cachedPath.

void MapInit();		//	sets values specific to our field. (i.e. locations of nodes and costs between them)

void MapSetNodeForID(NodeID nodeID, Node node);			//	give it the node info for a given node id
Node MapGetNode(NodeID nodeID);							//	get the node info for a given node id






















