

typedef struct {
	Point location;
	float orientation;
} RobotPosition;










bool RobotFollowWhiteLine();



task RobotRotate(float angle);	//	0 = straight ahead, pi/2 = left, -pi/2 = right

task RobotMove(float dist);	//	distance in inches???.  Can be negative.














