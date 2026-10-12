#include "types.h"

// The unload and load hooks rel/ironball_register.cpp puts in the editor record
// for TObjIronball: the load reads the ball's four models, the unload forgets
// them (the stage resource manager owns them). The load's loop leaves on `i ==
// 4` with a break and then clears what it did not read, which is how the
// original's exit test and its unreachable fill come out.

typedef struct RpClump RpClump;

extern "C" char* ironballModelNames[4];
extern "C" RpClump* ironballModels[4];

RpClump* objPointerReadFromClumpAnim(char* name);

extern "C" void ironballUnload(void)
{
	ironballModels[0] = NULL;
	ironballModels[1] = NULL;
	ironballModels[2] = NULL;
	ironballModels[3] = NULL;
}

extern "C" void ironballLoad(void)
{
	int i;

	i = 0;
	while (TRUE) {
		ironballModels[i] = objPointerReadFromClumpAnim(ironballModelNames[i]);
		i++;
		if (i == 4) {
			break;
		}
	}
	for (; i < 4; i++) {
		ironballModels[i] = NULL;
	}
}
