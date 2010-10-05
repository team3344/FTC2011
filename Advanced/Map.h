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





typedef enum {
	LandmarkWhiteLineEnd,
	LandmarkWhiteLineMiddle
} Landmark;






typedef enum {
	NodeTypeNone,
	
	//	dispensers
	NodeBlueLeftDispenser,
	NodeBlueCenterDispenser,
	NodeBlueRightDispenser,
	
	NodeRedLeftDispenser,
	NodeRedCenterDispenser,
	NodeRedRightDispenser,
	
	
	
	
	NodeBlueBridgeCenter,
	NodeRedBridgeCenter,
	
	
	
	
	
	
	
	//	goals
	
	
	NodeWhiteLineEnd,
	
	NodeBridgeCenter,
	NodeBridgeEnd,
	
	NodeHillCenter,
	NodeHillBase,
	
	NodeFieldCorner,
	
	NodePitCenter,
	
	
} NodeType;


#define kNodeCount 30	//	FIXME: set legit value
#define kPathCacheSize 10



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
	NodeType type;
	string name;
} Node;




extern const NodeID NodeIDZero;
extern const Node NodeZero;


typedef int NodeID;



//	non-directed graph (dist from A to B is equal to distance from B to A)
typedef struct {
	Node nodes[kNodeCount];
	NodeID cachedPath[10];
	NodeID goalNodeID;
	bool cached;
	float pathCosts[kNodeCount][kNodeCount];
} Map;




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






















