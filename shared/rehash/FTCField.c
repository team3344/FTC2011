

#ifndef _FTCField_
#include "FTCField.h"
#endif





//		Teams
//========================================================================================================================

static FTCTeam _currentTeam;

void FTCTeamSetCurrent(FTCTeam team)
{
	_currentTeam = team;
}

FTCTeam FTCTeamGetCurrent()
{
	return _currentTeam;
}


KeyPointID FTCFieldGetKeyPointOfBridgeForTeam(FTCTeam team)
{
  return ( team == FTCTeamRed ) ? KeyPointIDRedBridgeCenter : KeyPointIDBlueBridgeCenter;
}

KeyPointID FTCFieldGetKeyPointOfCenterDispenserForTeam(FTCTeam team)
{
  return ( team == FTCTeamRed ) ? KeyPointIDRedDispenserCenter : KeyPointIDBlueDispenserCenter;
}







