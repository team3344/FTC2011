

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





//#define kKickerSpeed 255
//#define kKickerSpeedReverse 0
//#define kKickerStopped 128


#define kKickerUp 165
#define kKickerDown 80



//	stomper
#define kRightStomperUp 0
#define kRightStomperDown 144
#define kLeftStomperUp 248
#define kLeftStomperDown 98




#define kElevatorSpeed 30


#define ElevatorIsAtTop() TSreadState(ElevatorTopStop)
#define ElevatorIsAtBottom() SensorValue[ElevatorBottomStop]



#define kElevatorHeightLowDispenser 1 //  FIXME: change these
#define kElevatorHeightMidDispenser 4
#define kElevatorHeightHighDispenser 10

#define kElevatorHeightBridgeCrossing 10  //  FIXME: fix
#define kElevatorHeightLineFollowing kElevatorHeightLowDispenser


void MechanismElevatorTarget(int targetEncoder);
void MechanismElevatorSetHeight(float height);



static bool MechanismElevatorIsOscillating;	//	FIXME: implement these!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
task MechanismElevatorOscillate();


task MechanismKickerKick();
static bool MechanismKickerIsKicking;


#define kFlapDownPosition 78
#define kFlapFlatPosition  153



#define kIntakeOn 255
#define kIntakeOff 127



#endif
