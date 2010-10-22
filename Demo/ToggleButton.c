#pragma config(Motor,  motorA,          Left,          tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorB,          Right,         tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#include "../Common/include.c"
#include "../Advanced/include.c"

task main()
{
  Controller c;

  while ( true )
  {
    UpdatePrimaryController(c);

    for ( int i = 0; i < 10; i++ )
    {
     nxtDisplayCenteredTextLine(i, (string)(i & c.toggleButtons));
    }
  }



}
