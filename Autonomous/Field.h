

#ifndef _Field_
#define _Field_

#ifndef _Vector_
#include "../shared/Vector.h"
#endif




#define kNodeCount 25

 typedef enum {
	NodeZero = -1,


	//	start squares	//
	NodeFriendStartSquareLeft,
	NodeFriendStartSquareRight,

	NodeFoeStartSquareLeft,
	NodeFoeStartSquareRight,



	//	dispensers	//
	NodeFoeDispenserLeft,
	NodeFoeDispenserCenter,
	NodeFoeDispenserRight,

	NodeFriendDispenserLeft,
	NodeFriendDispenserCenter,
	NodeFriendDispenserRight,



	//	bridges	//
	NodeFoeBridgeCenter,
	NodeFriendBridgeCenter,



	//	mountain	//
	//NodeMountainCenterTopEdge,
	//NodeMountainCenterPeak,
	//NodeMountainCenterBottomEdge,



	//	pit goals	//
	//NodeFriendPitCenter,
	//NodeFoePitCenter,



	//	white lines	//
	NodeLine1Top,
	NodeLine1Bottom,

	NodeLine2Top,
	NodeLine2Bottom,

	NodeLine3Top,
	NodeLine3Bottom,

	NodeLine4Top,
	NodeLine4Bottom,

	NodeLine5Top,
	NodeLine5Bottom,

	NodeLine6Top,
	NodeLine6Bottom

} Node;



typedef enum {
  NodeFlagLineEnd   = 1 << 0
} NodeFlags;



typedef struct {
	Vector location;
	NodeFlags flags;
} NodeInfo;




typedef struct {
	Node source, destination;
} PathSegment;




typedef enum {
	PathSegmentFlagBridgeEntrance		            = 1 << 0,
	PathSegmentFlagWhiteConnectingLine	        = 1 << 1,
	PathSegmentFlagPerpendicularWhiteLineAtEnd  = 1 << 2
} PathSegmentFlags;





typedef struct {
	NodeInfo nodeInfo[kNodeCount];							//	info on each node
	PathSegmentFlags segmentFlags[kNodeCount][kNodeCount];	//	info on each path segment
	Node cachedPath[kNodeCount];							//	array of nodes to go to.  the 0th entry is currentNode
	Node goalNode;											//	the node we want to go to
	bool cached;											//	tracks whether or not the path has been calculated between the currentNode and goalNode
	int currentNodeIndex;									//	the index in cachedPath of the node the bot is currently at
	float pathCosts[kNodeCount][kNodeCount];				//	cost value associated with each path segment.  may not be equal to the distance between the nodes, but it usually is.
	int validationTimes[kNodeCount][kNodeCount];			//	If nPgmTime is greater than the validation time b/w nodes, the node is valid
} Field;


static Field globalField; //	this is the field that everything works from



void FieldInit();


void FieldRecalculatePath();

bool FieldNodesAreConnected(Node n1, Node n2);				//	note: order matters
//void FieldConnectNodes(Node n1, Node n2, float cost);		//	tell it the distance between the two given nodes
void FieldConnectNodesAutomatically(Node n1, Node n2);		//	calculates the distance between the nodes using their locations. note: order doesn't matter
void FieldInvalidatePathFromNodeToNode(Node n1, Node n2);	//	tell it there is no path between the two given nodes.  order MATTERS
void FieldTemporarilyInvalidatePathBetweenNodes(Node n1, Node n2, int time);	//	tell it there is no path between the two given nodes.  order DOESN'T matter.  time = time in msec until it's validation
//bool FieldPathBetweenNodesIsValid(Node n1, Node n2);

void FieldSetCurrentNode(Node current);						//	tell the map where we are at the moment
Node FieldGetCurrentNode();									//	ask the map where it thinks we are
void FieldSetGoalNode(Node goal);							//	tell it where we want to go
Node FieldGetGoalNode();
Node FieldGetNextNode();
void FieldAdvance();										//	sets current node to the next node in the path


//void FieldReset();											//	sets cost from each node to itself to zero, and the rest to infinity.  clears all Nodes from nodes array.  clears cachedPath.


void FieldSetNodeCoordinates(Node n, float x, float y, float z);
void FieldSetNodeLocation(Node n, Vector& location);
void FieldGetNodeLocation(Node n, Vector& locationOut);

//void FieldSetNodeForID(Node Node, Node& node);				//	give it the node info for a given node id
//void FieldGetNode(Node Node, Node& nodeOut);				//	get the node info for a given node id

void FieldSetPathSegmentFlags(PathSegment& segment, PathSegmentFlags flags);
PathSegmentFlags FieldGetPathSegmentFlags(PathSegment& segment);




#endif
