
#import "Vector.h"
#import "Geometry.h"



typedef struct {
	Vector displacement;	//	displacement is based off the direction of the previous angle
	float angleChange;
} PositionChange;




task TrackAllMotion();



PositionChange TrackerCalculateChange(int dl, int dr);





