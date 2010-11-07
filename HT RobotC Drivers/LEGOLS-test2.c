#pragma config(Sensor, S1,     LEGOLS,                sensorLightInactive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: LEGOLS-test2.c 20 2009-12-08 22:59:13Z xander $
 */

/**
 * LEGOLS-driver.h provides an API for the Lego Light Sensor.  This program
 * demonstrates how to use that API to calibrate the sensor.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 25 November 2009
 * version 0.2
 */

#include "drivers/LEGOLS-driver.h"

task main () {
  int raw = 0;
  int nrm = 0;
  // Get control over the buttons
  nNxtButtonTask  = -2;

  LSsetActive(LEGOLS);
  eraseDisplay();
  nxtDisplayTextLine(0, "Light Sensor Cal.");
  nxtDisplayTextLine(2, "Left:  set black");
  nxtDisplayTextLine(3, "Right: set white");
  nxtDisplayTextLine(7, "Grey:  exit");

  while (true) {
    switch(nNxtButtonPressed) {
      // if the left button is pressed calibrate the black value for the sensor
      case kLeftButton:
                        LScalLow(LEGOLS);
                        PlaySound(soundBeepBeep);
                        while(bSoundActive);
                        break;

      // if the left button is pressed calibrate the white value for the sensor
      case kRightButton:
                        LScalHigh(LEGOLS);
                        PlaySound(soundBeepBeep);
                        while(bSoundActive);
                        break;
    }

    nxtDisplayClearTextLine(5);
    nxtDisplayClearTextLine(6);

    // Read the raw value of the sensor
    raw = LSvalRaw(LEGOLS);

    // Read the normalised value of the sensor
    nrm = LSvalNorm(LEGOLS);

    // Display the raw and normalised values
    nxtDisplayTextLine(5, "R: %4d N: %4d", raw, nrm);

    // Display the values for black and white
    nxtDisplayTextLine(6, "B: %4d W: %4d", lslow, lshigh);
    wait1Msec(50);
  }
}

/*
 * $Id: LEGOLS-test2.c 20 2009-12-08 22:59:13Z xander $
 */
