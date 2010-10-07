
#import "Vector.h"
#import "Constants.h"
#import "RobotControl.h"

#import "RobotC_Defines.h"	//	FIXME: remove this!!!



typedef struct {
	Vector displacement;	//	displacement is based off the direction of the previous angle
	float angleChange;
} PositionChange;




task TrackAllMotion();	//	FIXME: is this a necessary function???



PositionChange TrackerCalculateChange(int dl, int dr);




RobotPosition TrackerGetCurrentPosition();
void TrackerSetCurrentPosition(RobotPosition position);



