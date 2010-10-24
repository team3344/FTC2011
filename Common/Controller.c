

#ifndef _JoystickDriver_
#include "JoystickDriver.c"
#endif



#ifndef _Controller_
#include "Controller.h"
#endif




#define kJoystickConversionFactor (1.0/128.0)



void _UpdateControllerButtons(Controller& c, short buttons)
{
	c.buttonsPrevious = c.buttons;
	c.buttons = buttons;
	
	short changedButtons = c.buttonsPrevious ^ c.buttons;	//	XOR operation gives us all the buttons that changed
	c.toggleButtons = c.toggleButtons ^ (changedButtons & buttons);	//	toggle the changed buttons that became 'true'
}


void _UpdateControllerDPad(Controller& c, short dPadValue)
{
	/*
	
	DPad values from joystick
	
	-1 = (0,0) = not pressed
	0  = (0,1)
	1  = (1,1)
	2  = (1,0)
	3  = (1,-1)
	4  = (0,-1)
	5  = (-1,-1)
	6  = (-1,0)
	7  = (-1,1)
	
	*/
	
	
	
	/*	the x & y values are in arrays so they can be looked up quickly	*/
	static float dPadXValues[] = {
		0, 0, 1, 1, 1, 0, -1, -1, -1
	};
	
	static float dPadYValues[] = {
		0, 1, 1, 0, -1, -1, -1, 0, 1
	};
	
	
	Vector dPad;
	Vector2DMake(dPadXValues[dPadValue + 1], dPadYValues[dPadValue + 1], dPad);
	memcpy(c.dPad, dPad, sizeof(Vector));
}



bool ControllerButtonIsPressed(Controller& c, ControllerButton b)
{
	return c.buttons & (1 << b);
}

bool ControllerButtonChanged(Controller& c, ControllerButton b)
{
	return (c.buttons ^ c.previousButtons) & (1 << b);
}

bool ControllerButtonIsToggledOn(Controller& c, ControllerButton b)
{
	return c.toggledButtons & (1 << b);
}



void UpdatePrimaryController(Controller& c)
{
	//	get the joystick info
	Vector left, right;
	Vector2DMake(joystick.joy1_x1 * kJoystickConversionFactor, joystick.joy1_y1 * kJoystickConversionFactor * -1.0, left);
	Vector2DMake(joystick.joy1_x2 * kJoystickConversionFactor, joystick.joy1_y2 * kJoystickConversionFactor * -1.0, right);

	memcpy(c.leftJoystick, left, sizeof(Vector));
	memcpy(c.rightJoystick, right, sizeof(Vector));

	//	get D-Pad
	_UpdateControllerDPad(c, joystick.joy1_TopHat);
	
	//	get buttons
	_UpdateControllerButtons(c, joystick.joy1_Buttons);
}


void UpdateSecondaryController(Controller& c)
{
	//	get the joystick info
	Vector left, right;
	Vector2DMake(joystick.joy2_x1 * kJoystickConversionFactor, joystick.joy2_y1 * kJoystickConversionFactor * -1.0, left);
	Vector2DMake(joystick.joy2_x2 * kJoystickConversionFactor, joystick.joy2_y2 * kJoystickConversionFactor * -1.0, right);

	memcpy(c.leftJoystick, left, sizeof(Vector));
	memcpy(c.rightJoystick, right, sizeof(Vector));

	//	get D-Pad
	_UpdateControllerDPad(c, joystick.joy2_TopHat);
	
	//	get buttons
	_UpdateControllerButtons(c, joystick.joy2_Buttons);
}



