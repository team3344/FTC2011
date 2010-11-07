#pragma config(Sensor, S1,     HTPB,                sensorLowSpeed9v)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
 * $Id: HTPB-test2.c 20 2009-12-08 22:59:13Z xander $
 */

/**
 * HTPB-driver.h provides an API for the HiTechnic Protoboard.  This program
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

#include "drivers/common.h"
#include "drivers/HTPB-driver.h"

task main() {
  byte inputs = 0;

  nxtDisplayCenteredTextLine(0, "HiTechnic");
  nxtDisplayCenteredBigTextLine(1, "Proto");
  nxtDisplayCenteredTextLine(3, "Test 2");
  nxtDisplayCenteredTextLine(5, "Connect HTPB");
  nxtDisplayCenteredTextLine(6, "to S1");
  wait1Msec(2000);

  while(true) {
    eraseDisplay();
    // Fetch the state of the digital IO pins.  When not explicitly
    // configured as input or output, they will default to input.
    inputs = HTPBreadIO(HTPB, 0x3F);
    nxtDisplayTextLine(4, "D: 0x%x", ubyteToInt(inputs));
    wait1Msec(100);
  }
}

/*
 * $Id: HTPB-test2.c 20 2009-12-08 22:59:13Z xander $
 */
