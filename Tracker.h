
#ifndef _Tracker_
#define _Tracker_



typedef struct {
	Vector location;
	float orientation;
} RobotPosition;



void TrackerSetCurrentPosition(RobotPosition& pos);
void TrackerGetCurrentPosition(RobotPosition& posOut);






#endif
