


#ifndef _FTCField_
#define _FTCField_


#ifndef _Defines_
#include "Defines.h"
#endif





typedef enum {
	FTCTeamRed,
	FTCTeamBlue
} FTCTeam;

void FTCTeamSetCurrent(FTCTeam team);
FTCTeam FTCTeamGetCurrent();



typedef enum {
	FTCStartPositionLeft,
	FTCStartPositionRight
} FTCStartPosition;



KeyPointID FTCFieldGetKeyPointOfBridgeForTeam(FTCTeam team);
KeyPointID FTCFieldGetKeyPointOfCenterDispenserForTeam(FTCTeam team);








#endif
