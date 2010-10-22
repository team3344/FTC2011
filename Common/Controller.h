


#ifndef _CustomJoystick_
#define _CustomJoystick_


#ifndef _Vector_
#include "../Advanced/Vector.h"
#endif




typedef enum {
	ControllerButton1                   = 0,
	ControllerButton2                   = 1,
	ControllerButton3                   = 2,
	ControllerButton4                   = 3,
	ControllerButtonR1                  = 5,
	ControllerButtonR2                  = 7,
	ControllerButtonL1                  = 4,
	ControllerButtonL2                  = 6,
	ControllerButtonLeftMiddle          = 8,
	ControllerButtonRightMiddle         = 9,
	ControllerButtonRightJoystickPress  = 11,
	ControllerButtonLeftJoystickPress   = 10
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
