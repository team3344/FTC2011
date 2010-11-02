

#ifndef _SystemEvent_
#define _SystemEvent_




typedef enum {
	SystemEventProximity6in			= 1 << 0,	//	there's something within 6 inches of us
	SystemEventProximity12in		= 1 << 1,	//	there's something within 12 inches of us
	SystemEventIRVisible			= 1 << 2,	//	we can see IR
	SystemEventAutonomousHalfOver	= 1 << 3,	//	we have 20 seconds left
	SystemEventAutonomousAlmostOver	= 1 << 4
} SystemEvent;




SystemEvent SystemGetCurrentEvents();

task SystemContinuouslyUpdateEvents();




#endif
