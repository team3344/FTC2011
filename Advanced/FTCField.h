


#ifndef _FTCField_
#define _FTCField_



#ifndef _Map_
#include "Map.h"
#endif






//	field coordinates are in inches
//	the origin is at the corner on the red side

/************************************************
 *			*						 *(144, 144)*
 *			*						 *			*
 *	 BLUE	*						 *	 BLUE	*
 *			*						 *			*
 *			*						 *			*
 ************						 ************
 *												*
 *												*
 *												*
 *												*
 *												*
 ************************************************
 *												*
 *												*
 *												*
 *												*
 ************						*************
 *			*						*			*
 *			*						*			*
 *	 RED	*						*	 RED	*
 *			*						*			*
 * (0,0)	*						*			*
 ************************************************/




/*
 *	A tunnel is just a place where turning is bad.
 *	For example: the top of the mountain.  The robot should
 *	only try to go over it perpindicular to the base otherwise
 *	bad things will happen.
 */





typedef struct {
	bool hasTunnel;
	float tunnelAngle;
	//	white line?????????????????
	//	bridge entrance?????????????????????????????????????????
} KeyPointInfo;








bool WhiteLineConnectsNodes(NodeID n1, NodeID n2);
bool TunnelExistsAtNode(NodeID n);























#endif
