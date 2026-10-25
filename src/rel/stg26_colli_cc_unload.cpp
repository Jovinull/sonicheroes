#include "game/effect/eff_bomb.h"

// The stage 26 collision objects' Unload hook (stg26ColliCcUnload here): each
// of the two objects the Load creates is deleted and forgotten.

extern "C" TObject* stg26ColliCcObject0;
extern "C" TObject* stg26ColliCcObject1;

extern "C" void stg26ColliCcUnload(void)
{
	if (stg26ColliCcObject0 != NULL) {
		delete stg26ColliCcObject0;
		stg26ColliCcObject0 = NULL;
	}
	if (stg26ColliCcObject1 != NULL) {
		delete stg26ColliCcObject1;
		stg26ColliCcObject1 = NULL;
	}
}
