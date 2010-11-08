

#ifndef _Mechanism_
#define _Mechanism_



#ifndef _Sensors_
#include "Sensors.h"
#endif



/*
typedef enum {
	BatonTypeUnknown,
	BatonTypeRegular,
	BatonTypeMagnet,
	BatonTypePointDoubler
} Baton;
*/


//#define kMagazineCapacity 5



bool MechanismIsKicking();
task MechanismKickBaton();

void MechanismInit();


bool MechanismHasMagnetBaton();
void MechanismSetIndicatorLightState(bool turnedOn);



bool MechanismConveyorIsRunning();
task MechanismCycleConveyor();    //  make it go all the way around once



void MechanismDoorClose();
void MechanismDoorOpen();





short MechanismSlideGetPosition();
void MechanismSlideSetPosition(short position);
task MechanismSlideIncrementPosition();
task MechanismSlideDecrementPosition();

bool MechanismSlideIsMoving();

void MechanismSlideSetRegularPosition();
void MechanismSlideSetMagnetPosition();
void MechanismSlideSetDownPosition();
void MechanismSlideSetLongPosition();


#endif
