

#ifndef _Controller_
#include "Controller.h"
#endif








#define kJoystickConversionFactor (100.0/128.0)


void PrimaryController(Controller& c)
{
	//	get the joystick info
	Vector2DMake(joystick.joy1_x1 * kJoystickConversionFactor, joystick.joy1_y1 * kJoystickConversionFactor, c.leftJoystick);
	Vector2DMake(joystick.joy1_x2 * kJoystickConversionFactor, joystick.joy1_y2 *kJoystickConversionFactor, c.rightJoystick);
	
	//	FIXME: D-Pad?????????????????????????????????????????
	
	_UpdateControllerButtons(c, joystick.joy1_Buttons);
}


void SecondaryController(Controller& c)
{
	//	get the joystick info
	Vector2DMake(joystick.joy2_x1 * kJoystickConversionFactor, joystick.joy2_y1 * kJoystickConversionFactor, c.leftJoystick);
	Vector2DMake(joystick.joy2_x2 * kJoystickConversionFactor, joystick.joy2_y2 *kJoystickConversionFactor, c.rightJoystick);
	
	//	FIXME: D-Pad?????????????????????????????????????????
	
	_UpdateControllerButtons(c, joystick.joy2_Buttons);
}



void _UpdateControllerButtons(Controller& c, short buttons)
{
	c.buttonsPrevious = c.buttons;
	c.buttons = buttons;
	
	short changedButtons = c.buttonsPrevious ^ c.buttons;	//	XOR operation gives us all the buttons that changed
	short temp = !c.toggleButtons;
	temp = temp ^ changedButtons;	//	toggle the changed buttons
	c.toggleButtons = !temp;
}

