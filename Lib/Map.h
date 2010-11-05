

#ifndef _Map_
#define _Map_

#ifndef _Vector_
#include "Vector.h"
#endif




#define kNodeCount 40




typedef struct {
	Vector location;
	string name;
} Node;


#define NodeIDZero -1
typedef int NodeID;




typedef struct {
	Node nodes[kNodeCount];
	NodeID cachedPath[kNodeCount];
	NodeID goalNodeID;
	bool cached;
	int currentNode;
	float pathCosts[kNodeCount][kNodeCount];
	int validationTimes[kNodeCount][kNodeCount];	//	If nPgmTime is greater than the validation time b/w nodes, the node is valid
} Map;



void MapRecalculatePath();

bool MapNodesAreConnected(NodeID n1, NodeID n2);			//	note: order matters
void MapConnectNodes(NodeID n1, NodeID n2, float cost);		//	tell it the distance between the two given nodes
void MapConnectNodesAutomatically(NodeID n1, NodeID n2);	//	calculates the distance between the nodes using their locations. note: order doesn't matter
void MapInvalidatePathFromNodeToNode(NodeID n1, NodeID n2);	//	tell it there is no path between the two given nodes.  order MATTERS
void MapInvalidatePathBetweenNodes(NodeID n1, NodeID n2, int time);	//	tell it there is no path between the two given nodes.  order DOESN'T matter.  time = time in msec until it's valid again
bool MapPathBetweenNodesIsValid(NodeID n1, NodeID n2);

void MapSetCurrentNodeID(NodeID current);					//	tell the map where we are at the moment
NodeID MapGetCurrentNodeID();								//	ask the map where it thinks we are

void MapSetGoalNodeID(NodeID goal);							//	tell it where we want to go
NodeID MapGetGoalNodeID();

NodeID MapGetNextNodeID();
NodeID MapGetPreviousNodeID();

//NodeID MapRetract();										//	sets current node to previous node and returns the node before that
NodeID MapAdvance();										//	sets current node to next node and returns the next node after that


void MapReset();	//	sets cost from each node to itself to zero, and the rest to infinity.  clears all Nodes from nodes array.  clears cachedPath.


void MapSetNodeNameForID(NodeID nodeID, string name);
void MapSetNodeLocationForID(NodeID nodeID, Vector& location);
void MapSetNodeInfoForID(NodeID nodeID, string name, Vector& location);

void MapSetNodeForID(NodeID nodeID, Node& node);			//	give it the node info for a given node id
void MapGetNode(NodeID nodeID, Node& nodeOut);				//	get the node info for a given node id


//void MapDraw();
//task MapContinuouslyRedraw();





#endif
