
#include "AdvancedRobotControl.h"


void _RobotGoFromCurrentNodeToNode(Node current, Node target)
{
	Vector displacement = VectorSubtract(target.location, current.location);

	//printf("\ncurrentLocation = ");
	//PrintVector(current.location);

	//printf("\ntarget.location = ");
	//PrintVector(target.location);

	//printf("\nrobot move w/vector: ");
	//PrintVector(displacement);
	//printf("\n");


	RobotMoveWithVector(displacement);	//	FIXME: only do this for things without landmarks or beacons???

	//	FIXME: look for landmarks???
	//	FIXME: if we hit a landmark, tell tracker we have an absolute position





}


void RobotGoToNode(NodeID target)
{
	MapSetGoalNodeID(target);

	Node previous = MapGetNode(MapGetCurrentNodeID());	//	start position

	while ( true )
	{
		NodeID node = MapAdvance();			//	get the id of the next node along the path
		if ( node == NodeIDZero ) break;	//	if we're at the end of the path, we're done!

		Node segmentTarget = MapGetNode(node);	//	this is where we're heading

		_RobotGoFromCurrentNodeToNode(previous, segmentTarget);	//	go to the target

		previous = segmentTarget;	//	the node we're now heading to will be the previous node in the next iteration
	}
}



void RobotMoveWithVector(Vector displacement)
{
	RobotPosition currentPosition = TrackerGetCurrentPosition();

	//printf("currentPosition.orientation = %f\n", currentPosition.orientation);

	//printf("displacement angle = %f\n", VectorGetAngle(displacement));

	RobotRotate(VectorGetAngle(displacement) - currentPosition.orientation);	//	turn towards the destination
	RobotMove(VectorGetMagnitude(displacement));								//	move the required distance to the destination




	//FIXME: remove below line

	RobotPosition future;
	future.location = VectorAdd(currentPosition.location, displacement);
	future.orientation = VectorGetAngle(displacement);
	TrackerSetCurrentPosition(future);
	//	FIXME: trash above

}
