#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTServo,  none)
#pragma config(Sensor, S2,     ElevatorTopStop,     sensorTouch)
#pragma config(Sensor, S3,     SMUX2,               sensorI2CCustom)
#pragma config(Sensor, S4,     SMUX1,               sensorI2CCustom)
#pragma config(Motor,  motorA,          IndicatorLight, tmotorNormal, openLoop)
#pragma config(Motor,  motorB,          ,              tmotorNormal, PIDControl)
#pragma config(Motor,  motorC,          ,              tmotorNormal, PIDControl)
#pragma config(Motor,  mtr_S1_C1_1,     Left,          tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     Right,         tmotorNormal, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     Elevator,      tmotorNormal, PIDControl, encoder)
#pragma config(Servo,  srvo_S1_C3_1,    Kicker,               tServoContinuousRotation)
#pragma config(Servo,  srvo_S1_C3_2,    DoorRight,            tServoStandard)
#pragma config(Servo,  srvo_S1_C3_3,    Slide,                tServoStandard)
#pragma config(Servo,  srvo_S1_C3_4,    RightStomper,         tServoStandard)
#pragma config(Servo,  srvo_S1_C3_5,    LeftStomper,          tServoStandard)


task main()
{
  while (true) {
    while ( nNxtButtonPressed != kLeftButton && nNxtButtonPressed != kRightButton )
    {
      motor[Left] = -17;
      motor[Right] = 17;
      wait10Msec(6);
      motor[Left] = 17;
      motor[Right] = -17;
      // PlaySound(soundBeepBeep);
      wait10Msec(6);
    }
    motor[Left] = 0;
    motor[Right] = 0;
  }
}
