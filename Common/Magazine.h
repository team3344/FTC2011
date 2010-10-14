/*
 *  Magazine.h
 *  Get Over It
 *
 *  Created by Justin Buchanan on 9/11/10.
 *  Copyright 2010 JustBuchanan Software. All rights reserved.
 *
 */

#ifndef _Magazine_
#define _Magazine_

#ifndef _Baton_
#include "Baton.h"
#endif





#define kMagazineCapacity 5



typedef Baton MagazineContents[kMagazineCapacity];



void MagazineEat(float time);	//	time is in ms????? distance??? # of batons???
void MagazineEject(int count);
task MagazinePack();			//	pushes the batons back tight


task MagazineSaveContents();	//	saves magine contents to a file.  where??????????????




#endif
