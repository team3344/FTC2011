

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

static bool MechanismSlideIsMoving;





#define kKickerSpeed 255
#define kKickerSpeedReverse 0
#define kKickerStopped 128




//	stomper
#define kRightStomperUp 220
#define kRightStomperDown 72
#define kLeftStomperUp 17
#define kLeftStomperDown 165




#define kElevatorSpeed 30


#define ElevatorIsAtTop() TSreadState(ElevatorTopStop)
#define ElevatorIsAtBottom() SensorValue[ElevatorBottomStop]



#define kElevatorHeightLowDispenser 1
#define kElevatorHeightMidDispenser 4
#define kElevatorHeightHighDispenser 10

#define kElevatorHeightBridgeCrossing 10
#define kElevatorHeightLineFollowing kElevatorHeightLowDispenser


void MechanismElevatorSetHeight(float height);



static bool MechanismElevatorIsOscillating;	//	FIXME: implement these!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
task MechanismElevatorOscillate();






/*
#define kFlapUpPosition 205
#define kFlapDownPosition 80
#define kFlapFlatPosition  140
*/



#define kGateDownPosition 41
#define kGateUpPosition 159




#endif
