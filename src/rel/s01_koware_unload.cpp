#include "types.h"

// The breakable wall's Unload hook (s01KowareUnload here): each of its 13
// pieces' models is released.

extern "C" void* s01KowareModels[13];

extern "C" void fn_80150958(void* clump);

extern "C" void s01KowareUnload(void)
{
	for (s8 i = 0; i < 13; i++) {
		if (s01KowareModels[i] != NULL) {
			fn_80150958(s01KowareModels[i]);
			s01KowareModels[i] = NULL;
		}
	}
}
