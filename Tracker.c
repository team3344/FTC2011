
#ifndef _Tracker_
#include "Tracker.h"
#endif




RobotPosition _position;


void TrackerGetCurrentPosition(RobotPosition& posOut)
{
 memcpy(posOut, _position, sizeof(RobotPosition));
}


void TrackerSetCurrentPosition(RobotPosition& pos)
{
 memcpy(_position, pos, sizeof(RobotPosition));
}
