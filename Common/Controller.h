


#ifndef _CustomJoystick_
#define _CustomJoystick_


#ifndef _Vector_
#include "Vector.h"
#endif




typedef enum {
	ControllerButton1,
	ControllerButton2,
	ControllerButton3,
	ControllerButton4,
	ControllerButtonR1,
	ControllerButtonR2,
	ControllerButtonL1,
	ControllerButtonL2
} ControllerButton;

#define kControllerButtonCount ControllerButtonL2 + 1



typedef struct {
	Vector leftJoystick;	//	components are percentages
	Vector rightJoystick;
	bool buttons[kControllerButtonCount];
} Controller;






void PrimaryController(Controller& c);
void SecondaryController(Controller& c);






#endif
