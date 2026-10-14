#include "game/enemy/e_database.h"

// TEnemyGadgetLaser::Finalize and Initialize (the PS2 build's names), static:
// the laser's nine models are found in the searcher files (enemy database
// kind 2); finalizing has nothing to release.

class TEnemyGadgetLaser
{
public:
	static void Finalize();
	static void Initialize();

	static RpClump* pClumpStatic[9];
};

extern "C" u32 laserModelIds[9];

void TEnemyGadgetLaser::Finalize() { }

void TEnemyGadgetLaser::Initialize()
{
	int i;

	for (i = 0; i < 9; i++) {
		pClumpStatic[i]
		    = TEnemyDataBase::GetInstance()->SearchClump((eEnemyDataBase)2, laserModelIds[i]);
	}
}
