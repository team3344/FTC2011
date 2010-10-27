#pragma config(Sensor, S1,     SonarLeft,           sensorSONAR)
#pragma config(Sensor, S2,     SonarRight,          sensorSONAR)
#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Motor,  motorA,          Conveyer,      tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorB,          ,              tmotorNormal, openLoop)
#pragma config(Motor,  motorC,          ,              tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     Right,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     Front,         tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     Back,          tmotorNormal, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    SlideExtender,        tServoStandard)
#pragma config(Servo,  srvo_S1_C3_2,    SlidePivot,           tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    SlideKicker,          tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "../include.c"




task main()
{

  nMotorPIDSpeedCtrl[motorA] = mtrSpeedReg;
  nMotorPIDSpeedCtrl[motorB] = mtrSpeedReg;

  nMotorEncoderTarget[motorA] = 1000;
  motor[motorA] = 20;

  while ( motor[motorA] ) {}

  motor[motorB] = 50;
  wait10Msec(50);


  motor[motorA] = 0;
  motor[motorB] = 0;


}
