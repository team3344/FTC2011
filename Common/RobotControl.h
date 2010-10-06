
#import "Geometry.h"
#import "RobotC_Defines.h"	//	FIXME: remove this



typedef struct {
	Point location;
	float orientation;
} RobotPosition;










task RobotFollowWhiteLine();


task RobotFollowIR();




task RobotRotate(float angle);	//	0 = straight ahead, pi/2 = left, -pi/2 = right

task RobotMove(float dist);	//	distance in inches???.  Can be negative.














