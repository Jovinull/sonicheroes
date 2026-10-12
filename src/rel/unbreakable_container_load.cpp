// unbreakableContainerLoad, the load hook
// rel/unbreakable_container_register.cpp puts in the editor record for
// TObjContUnbreakable: it reads the crate's model and its three kinds of debris
// as clumps the stage resource manager owns.

#include "types.h"

typedef struct RpClump RpClump;

struct ContainerPieceName {
	char* name;
	s32 count;
};

extern "C" RpClump* unbreakableContainerResource;
extern "C" RpClump* unbreakableContainerPieces[3];
extern "C" ContainerPieceName unbreakableContainerPieceTable[3];
extern "C" char unbreakableContainerModelName[];

RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void unbreakableContainerLoad(void)
{
	s32 i;

	unbreakableContainerResource = objPointerReadFromClumpAnim(unbreakableContainerModelName);
	for (i = 0; i < 3; i++) {
		unbreakableContainerPieces[i]
		    = objPointerReadFromClumpAnim(unbreakableContainerPieceTable[i].name);
	}
}
