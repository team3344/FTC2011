

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
