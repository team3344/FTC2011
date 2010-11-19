

#ifndef _Mechanism_
#define _Mechanism_



#ifndef _Sensors_
#include "Sensors.h"
#endif




void MechanismInit();


static bool MechanismIsKicking;
task MechanismKickBaton();



void MechanismDoorClose();
void MechanismDoorOpen();







#define kSlideMaxPosition 255
#define kSlideMinPosition 1

#define kSlideDownPosition 100
#define kSlideMagnetPosition 86
#define kSlideRegularPosition 70
#define kSlideLongPosition 95

void MechanismSlideSetPosition(short position);
task MechanismSlideIncrementPosition();
task MechanismSlideDecrementPosition();

static bool MechanismSlideIsMoving;



#endif
