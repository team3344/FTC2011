#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     ElevatorTopStop,     sensorTouch)
#pragma config(Sensor, S3,     SMUX2,               sensorI2CCustom)
#pragma config(Sensor, S4,     SMUX1,               sensorI2CCustom)
#pragma config(Motor,  motorA,          IndicatorLight, tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          ,              tmotorNormal, PIDControl)
#pragma config(Motor,  motorC,          ,              tmotorNormal, PIDControl)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Right,         tmotorNormal, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Elevator,      tmotorNormal, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    Kicker,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    Gate,                 tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    Slide,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    RightStomper,         tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    LeftStomper,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//  SMUX1
#define Magnet msensor_S4_2
#define LeftLightSensor msensor_S4_3
#define RightLightSensor msensor_S4_4


//  SMUX2 //  FIXME: set port numbers !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define ElevatorBottomStop msensor_S3_1
#define IR msensor_S3_2
#define Sonar msensor_S3_4
#define Accelerometer msensor_S3_2


//#include "JoystickDriver.c"
#include "shared/include.c"
#include "Autonomous/include.c"



task main()
{
  SensorsInit();
  MechanismInit();



  while ( true )
  {
    nxtDisplayCenteredTextLine(0, (string)LEFT_LIGHT_SENSOR());
    nxtDisplayCenteredTextLine(1, (string)RIGHT_LIGHT_SENSOR());
  }







  RobotFindWhiteLine();
  PlaySound(soundBeepBeep);
  RobotFollowWhiteLineToEnd(false);
  PlaySound(soundUpwardTones);
}



/*

bool EnemyRobotDetected() //  FIXME: adjust this method's constants!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
  float distance = SonarSensorDistance();
	return (distance < 10) && (distance > 3);	//	if the sonar detects something w/in 8 inches, we'll assume it's another bot
}
*/
