
#import "Vector.h"
#import "Geometry.h"
#import "Constants.h"

#import "RobotC_Defines.h"	//	FIXME: remove this!!!



typedef struct {
	Vector displacement;	//	displacement is based off the direction of the previous angle
	float angleChange;
} PositionChange;




task TrackAllMotion();



PositionChange TrackerCalculateChange(int dl, int dr);





