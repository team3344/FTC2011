#pragma config(Sensor, S1,     LEGOLS,                sensorLightInactive)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: LEGOLS-test1.c 20 2009-12-08 22:59:13Z xander $
 */

/**
 * LEGOLS-driver.h provides an API for the Lego Light Sensor.  This program
 * demonstrates how to use that API.
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

task main() {
  int raw = 0;
  int nrm = 0;
  bool active = true;
  LSsetActive(LEGOLS);

  nNxtButtonTask  = -2;

  eraseDisplay();
  nxtDisplayTextLine(0, "Light Sensor");
  nxtDisplayTextLine(2, "Press orange");
  nxtDisplayTextLine(3, "button to switch");

  while (true) {
    // The enter button has been pressed, switch
    // to the other mode
    if (nNxtButtonPressed == kEnterButton) {
      active = !active;
      if (!active)
        // Turn the light off
        LSsetInactive(LEGOLS);
      else
        // Turn the light on
        LSsetActive(LEGOLS);

      // wait 500ms to debounce the switch
      wait1Msec(500);
    }

    nxtDisplayClearTextLine(5);
    nxtDisplayClearTextLine(6);

    // Get the raw value from the sensor
    raw = LSvalRaw(LEGOLS);

    // Get the normalised value from the sensor
    nrm = LSvalNorm(LEGOLS);

    nxtDisplayTextLine(5, "Raw:  %4d", raw);
    nxtDisplayTextLine(6, "Norm: %4d", nrm);
    wait1Msec(50);
  }
}

/*
 * $Id: LEGOLS-test1.c 20 2009-12-08 22:59:13Z xander $
 */
