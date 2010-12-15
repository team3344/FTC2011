

#ifndef _Field_
#include "Field.h"
#endif





typedef struct {
  string title;
  int itemCount;
  string items[6];
} NXTMenu;



/*
nNxtButtonPressed
kNoButton
kLeftButton
kRightButton

100x64 pixel display
8 lines
*/

TButtons NXTGetButtonPress()
{
	TButtons button;
	do {
		button = nNxtButtonPressed;
	} while ( button == kNoButton );
  return button;
}






#define kMenuBlinkInterval 300  //  time in ms between blinks

//  returns bit mask of checked items
int NXTShowChecklistMenu(NXTMenu& menu, int checkedItems)
{
  //  FIXME: implement this!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  int selectedIndex = 0;
  int doneIndex = menu.itemCount + 2;

  while ( true )
  {

    if ( selectedIndex < 0 ) selectedIndex = 0;
    else if ( selectedIndex > doneIndex ) selectedIndex = doneIndex;

    eraseDisplay();
    nxtDisplayCenteredTextLine(0, menu.title);


    for ( int i = 0; i < menu.itemCount; i++ )
    {
      nxtDisplayCenteredTextLine(i + 1, menu.items[i]);
    }

    nxtDisplayCenteredTextLine(doneIndex, "Done");





    //  FIXME: draw it & wait for input






    //  FIXME: draw checkmarks!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!




    //  wait until button press
    TButtons button = NXTGetButtonPress();
    PlaySound(soundBlip);
    while ( nNxtButtonPressed != kNoButton ){}  //  wait until button release

    if ( button == 3 )  //  center button
    {
      if ( selectedIndex == doneIndex )
      {
        return checkedItems;
      }
      else
      {
        checkedItems ^= selectedIndex;  //  toggle the bit for the selected item
      }
    }
    else if ( button == kLeftButton )
    {
      --selectedIndex;
    }
    else if ( button == kRightButton )
    {
      ++selectedIndex;
    }
  }

  return checkedItems;
}


//  returns index of selected item
int NXTShowSelectionMenu(NXTMenu& menu)
{
  int selectedIndex = 0;

  while ( true )
  {
    eraseDisplay();
    nxtDisplayCenteredTextLine(0, menu.title);


    //  show the menu
    for ( int i = 0; i < menu.itemCount; i++ )
    {
      nxtDisplayStringAt(20, (6 - i) * 8, menu.items[i]);
    }

    //  limit the selectedIndex
    if ( selectedIndex < 0 ) selectedIndex = 0;
    else if ( selectedIndex >= menu.itemCount ) selectedIndex = menu.itemCount - 1;


    //  draw the selection indicator - a small, filled circle
    int y = 8 * (5 - selectedIndex);
    int x = 0;
    nxtFillEllipse(x, y, x + 8, y + 8);



    TButtons button = NXTGetButtonPress();
    PlaySound(soundBlip);
    while ( nNxtButtonPressed != kNoButton ){}  //  wait until button release

    if ( button == 3 )  //  center button
    {
      return selectedIndex;
    }
    else if ( button == kLeftButton )
    {
      --selectedIndex;
    }
    else if ( button == kRightButton )
    {
      ++selectedIndex;
    }
  }
}






void FTCGetStartInfo()
{
	hogCPU(); //  do this so the waitForStart task doesn't display its trash on the screen while we're trying to get input

	/*
	NXTMenu teamMenu;
	teamMenu.title = "Select Team";
	teamMenu.items[0] = "Red";
	teamMenu.items[1] = "Blue";
	teamMenu.itemCount = 2;
	*/
	//int team = NXTShowMenu(teamMenu);	//	FIXME: is it necessary to get the team color?



	NXTMenu sideMenu;
	sideMenu.title = "Select Side";
	sideMenu.items[0] = "Left";
	sideMenu.items[1] = "Right";
	sideMenu.itemCount = 2;

	int side = NXTShowSelectionMenu(sideMenu);


	//  set the start node
	Node startNode = ( side == 0 ) ? NodeFriendStartSquareLeft : NodeFriendStartSquareRight;
	FieldSetCurrentNode(startNode);

	//	set the start position
	FieldGetNodeLocation(startNode, CurrentRobotPosition.location);
	CurrentRobotPosition.orientation = PI / 2.0;


	//  goals for autonomous period
	NXTMenu autonomousMenu;
	autonomousMenu.title = "Select Goals";
	autonomousMenu.items[0] = "Preloads";
	autonomousMenu.items[1] = "Mission";
	autonomousMenu.items[2] = "Balance";

	int goals = NXTShowChecklistMenu(autonomousMenu, 0);

	//  FIXME: do something with the return value goals!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	//  FIXME: setup status string to display!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



	eraseDisplay();

	releaseCPU();	//	'unhog' the CPU so other tasks can run
}
