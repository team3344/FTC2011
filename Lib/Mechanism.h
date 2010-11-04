

#ifndef _Mechanism_
#define _Mechanism_





typedef enum {
	BatonTypeUnknown,
	BatonTypeRegular,
	BatonTypeMagnet,
	BatonTypePointDoubler
} Baton;



#define kMagazineCapacity 5



bool MechanismIsKicking();
task MechanismKickBaton();

void MechanismInit();



bool MechanismConveyorIsRunning();
task MechanismCycleConveyor();    //  make it go all the way around once








//typedef Baton MagazineContents[kMagazineCapacity];
//void MagazineEat(float time);	//	time is in ms????? distance??? # of batons???
//void MagazineEject(int count);
//task MagazinePack();			//	pushes the batons back tight
//task MagazineSaveContents();	//	saves magine contents to a file.  where??????????????




#endif
