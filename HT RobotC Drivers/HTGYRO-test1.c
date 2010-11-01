#pragma config(Sensor, S1,     HTGYRO,              sensorRawValue)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: HTGYRO-test1.c 20 2009-12-08 22:59:13Z xander $
 */

/**
 * HTGYRO-driver.h provides an API for the HiTechnic Gyroscopic Sensor.  This program
 * demonstrates how to use that API.
 *
 * Changelog:
 * - 0.1: Initial release
 * - 0.2: More comments
 *
 * Credits:
 * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where it's due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * Xander Soldaat (mightor_at_gmail.com)
 * 25 November 2009
 * version 0.2
 */

#include "drivers/HTGYRO-driver.h"

task main () {
  nxtDisplayTextLine(0, "HT Gyro");
  nxtDisplayTextLine(1, "Test 1");
  nxtDisplayTextLine(5, "Press enter");
  nxtDisplayTextLine(6, "to set relative");
  nxtDisplayTextLine(7, "heading");

  wait1Msec(2000);
  eraseDisplay();
  time1[T1] = 0;
  while(true) {
    if (time1[T1] > 1000) {
      eraseDisplay();
      nxtDisplayTextLine(1, "Resetting");
      nxtDisplayTextLine(1, "heading");
      wait1Msec(500);

      // Start the calibration and display the offset
      nxtDisplayTextLine(2, "Offset: %4d", HTGYROstartCal(HTGYRO));
      PlaySound(soundBlip);
      while(bSoundActive);
      time1[T1] = 0;
    }

    while(nNxtButtonPressed != kEnterButton) {
      eraseDisplay();

      nxtDisplayTextLine(1, "Reading");
      // Read the current calibration offset and display it
      nxtDisplayTextLine(2, "Offset: %4d", HTGYROreadCal(HTGYRO));

      nxtDisplayClearTextLine(4);
      // Read the current rotational speed and display it
      nxtDisplayTextLine(4, "Gyro:   %4d", HTGYROreadRot(HTGYRO));
      nxtDisplayTextLine(6, "Press enter");
      nxtDisplayTextLine(7, "to recalibrate");
      wait1Msec(100);
    }
  }
}

/*
 * $Id: HTGYRO-test1.c 20 2009-12-08 22:59:13Z xander $
 */
