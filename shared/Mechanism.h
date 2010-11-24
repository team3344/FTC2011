

#ifndef _Mechanism_
#define _Mechanism_



#ifndef _Sensors_
#include "Sensors.h"
#endif




void MechanismInit();


#define kSlideMaxPosition 144
#define kSlideMinPosition 10

#define kSlideDownPosition 20
#define kSlideMagnetPosition 95
#define kSlideRegularPosition 85
#define kSlideLongPosition 110

void MechanismSlideSetPosition(short position);
task MechanismSlideIncrementPosition();
task MechanismSlideDecrementPosition();

static bool MechanismSlideIsMoving;





#define kKickerSpeed 170
#define kKickerStopped 128





#define kRightStomperUp 237
#define kRightStomperDown 72
#define kLeftStomperUp 0
#define kLeftStomperDown 165

#define kElevatorSpeed 30


#define ElevatorIsAtTop (SensorValue[ElevatorTopStop] == 1)
#define ElevatorIsAtBottom TSreadState(ElevatorBottomStop)

#define kDoorUpPosition 205
#define kDoorDownPosition 80
#define kDoorFlatPosition  140


void MechanismDoorSetPosition(short position);



#endif
