

#ifndef _JoystickDriver_
#include "joystickDriver.c"
#endif



#ifndef _Controller_
#include "Controller.h"
#endif








#define kJoystickConversionFactor (100.0/128.0)




void _UpdateControllerButtons(Controller& c, short buttons)
{
	c.buttonsPrevious = c.buttons;
	c.buttons = buttons;

	short changedButtons = c.buttonsPrevious ^ c.buttons;	//	XOR operation gives us all the buttons that changed

	if ( changedButtons > 0 )
	{
	    nxtDisplayCenteredTextLine(2, "true");
	    wait10Msec(50);
	 }


	short temp = !c.toggleButtons;
	temp = temp ^ (changedButtons & buttons);	//	toggle the changed buttons that became 'true'
	c.toggleButtons = !temp;
}







void UpdatePrimaryController(Controller& c)
{
	//	get the joystick info
	Vector left, right;
	Vector2DMake(joystick.joy1_x1 * kJoystickConversionFactor, joystick.joy1_y1 * kJoystickConversionFactor, left);
	Vector2DMake(joystick.joy1_x2 * kJoystickConversionFactor, joystick.joy1_y2 *kJoystickConversionFactor, right);

	memcpy(c.leftJoystick, left, sizeof(Vector));
	memcpy(c.rightJoystick, right, sizeof(Vector));

	if ( right.x > 0 ) PlaySound(soundBeepBeep);

	//	FIXME: D-Pad?????????????????????????????????????????

	_UpdateControllerButtons(c, joystick.joy1_Buttons);
}


void UpdateSecondaryController(Controller& c)
{
	//	get the joystick info
  Vector left, right;
	Vector2DMake(joystick.joy2_x1 * kJoystickConversionFactor, joystick.joy2_y1 * kJoystickConversionFactor, left);
	Vector2DMake(joystick.joy2_x2 * kJoystickConversionFactor, joystick.joy2_y2 *kJoystickConversionFactor, right);

	memcpy(c.leftJoystick, left, sizeof(Vector));
	memcpy(c.rightJoystick, right, sizeof(Vector));


	//	FIXME: D-Pad?????????????????????????????????????????

	_UpdateControllerButtons(c, joystick.joy2_Buttons);
}
