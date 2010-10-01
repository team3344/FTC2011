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



typedef Baton[kMagazineCapacity] MagazineContents;



task MagazineEat(float time);	//	time is in ms????? distance??? # of batons???
task MagazineEject(int count);
task MagazinePack();			//	pushes the batons back tight


task MagazineSaveContents();	//	saves magine contents to a file.  where??????????????

