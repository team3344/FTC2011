/*
 *  Magazine.h
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */



#import "Baton.h"


#define kMagazineCapacity 5





typedef enum {
	MagazineCompartmentMain,
	MagazineCompartmentSpecial
} MagazineCompartment;



typedef struct {
	Baton[2][kMagazineCapacity];
} Magazine;



float MagazineGetPosition();



