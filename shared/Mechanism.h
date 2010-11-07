

#ifndef _Mechanism_
#define _Mechanism_



#ifndef _Sensors_
#include "Sensors.h"
#endif


void MechanismInit();



bool MechanismIsKicking();
task MechanismKickBaton();



//bool MechanismHasMagnetBaton();
//void MechanismSetIndicatorLightState(bool turnedOn);



bool MechanismConveyorIsRunning();
task MechanismCycleConveyor();    //  make it go all the way around once






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
