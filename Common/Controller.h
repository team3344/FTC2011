

#ifndef _Controller_
#define _Controller_


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




typedef struct {
	Vector leftJoystick;	//	components are from 0 to 1
	Vector rightJoystick;	//	components are from 0 to 1
	Vector dPad;			//	components are either 0 or 1
	short buttons;			//	Bit map for 12-buttons
	short previousButtons;
	short toggleButtons;
} Controller;




/*
 Axis for all directional values (Vectors)

        *
        *
 (-,+)	*	(+,+)
        *
 *****************
        *
 (-,-)	*	(+,-)
        *
        *

 */




bool ControllerButtonIsPressed(Controller& c, ControllerButton b);		//	returns true if it is currently pressed
bool ControllerButtonChanged(Controller& c, ControllerButton b);		//	returns yes if the button changed since the last update
bool ControllerButtonIsToggledOn(Controller& c, ControllerButton b);	//	the controller tracks toggled buttons.  pressing a button toggles it on.  pressing it again toggles it off.


void UpdatePrimaryController(Controller& c);
void UpdateSecondaryController(Controller& c);




#endif
