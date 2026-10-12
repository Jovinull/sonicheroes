#include "types.h"

// The unload and load hooks rel/cage_assets.cpp puts in the cage's editor
// record, in the thirteen stage modules that share it. The load reads the cage's
// three models and its three kinds of debris; the unload forgets the models
// (the stage resource manager owns them).

typedef struct RpClump RpClump;

struct CagePieceName {
	char* name;
	s32 count;
};

extern "C" char* cageModelNames[3];
extern "C" CagePieceName cagePieceTable[3];
extern "C" RpClump* cageModels[3];
extern "C" RpClump* cagePieces[3];

RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void cageUnload(void)
{
	for (int i = 0; i < 3; i++) {
		if (cageModels[i] != NULL) {
			cageModels[i] = NULL;
		}
	}
}

extern "C" void cageLoad(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		cageModels[i] = objPointerReadFromClumpAnim(cageModelNames[i]);
	}
	for (i = 0; i < 3; i++) {
		cagePieces[i] = objPointerReadFromClumpAnim(cagePieceTable[i].name);
	}
}
