


#ifndef _CustomJoystick_
#define _CustomJoystick_


#ifndef _Vector_
#include "../Vector.h"
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
	short buttons;			// Bit map for 12-buttons
	short buttonsPrevious;
	short toggleButtons;	//	
} Controller;






void UpdatePrimaryController(Controller& c);
void UpdateSecondaryController(Controller& c);






#endif
