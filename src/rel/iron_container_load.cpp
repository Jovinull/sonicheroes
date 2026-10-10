// ironContainerLoad, the load hook rel/iron_container_register.cpp puts in the
// editor record for TObjContIron: it reads the crate's model and its three
// kinds of debris as clumps the stage resource manager owns.

#include "types.h"

typedef struct RpClump RpClump;

struct ContainerPieceName {
	char* name;
	s32 count;
};

extern "C" RpClump* ironContainerResource;
extern "C" RpClump* ironContainerPieces[3];
extern "C" ContainerPieceName ironContainerPieceTable[3];
extern "C" char ironContainerModelName[];

RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void ironContainerLoad(void)
{
	s32 i;

	ironContainerResource = objPointerReadFromClumpAnim(ironContainerModelName);
	for (i = 0; i < 3; i++) {
		ironContainerPieces[i] = objPointerReadFromClumpAnim(ironContainerPieceTable[i].name);
	}
}
