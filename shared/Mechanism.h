

#ifndef _Mechanism_
#define _Mechanism_



#ifndef _Sensors_
#include "Sensors.h"
#endif




void MechanismInit();


#define kSlideMaxPosition 121
#define kSlideMinPosition 244

#define kSlideDownPosition 244
#define kSlideMagnetPosition 163
#define kSlideRegularPosition 150
#define kSlideLongPosition 125

static bool MechanismSlideIsMoving;



#define kKickerUp 165
#define kKickerDown 80



//	stomper
#define kRightStomperUp 0
#define kRightStomperDown 155
#define kLeftStomperUp 248
#define kLeftStomperDown 87




#define kElevatorSpeed 30


#define ElevatorIsAtTop() TSreadState(ElevatorTopStop)
#define ElevatorIsAtBottom() SensorValue[ElevatorBottomStop]



#define kElevatorHeightLowDispenser 1 //  FIXME: change these
#define kElevatorHeightMidDispenser 4
#define kElevatorHeightHighDispenser 10

#define kElevatorHeightBridgeCrossing 10  //  FIXME: fix
#define kElevatorHeightLineFollowing kElevatorHeightLowDispenser



//  FIXME: fix these
#define kElevatorTargetBridgeCrossing 2207
#define kElevatorTargetLineFollowing 30
#define kElevatorTargetHighDispenser 1010
#define kElevatorTargetMidDispenser 412





void MechanismElevatorTarget(int targetEncoder);
//void MechanismElevatorSetHeight(float height);

//  to move elevator asynchronously, set MechanismElevatorTarget,
//  then call the task.  watch MechanismElevatorIsTargeting to see if
//  it's still going or if it's finished
task MechanismElevatorTargetTask();
static int MechanismElevatorTargetEncoder;
static bool MechanismElevatorIsTargeting;



task MechanismKickerKick();
static bool MechanismKickerIsKicking;


#define kFlapDownPosition 78
#define kFlapFlatPosition  153



#define kIntakeOn 255
#define kIntakeOff 127
#define kIntakeReverse 0


#endif
