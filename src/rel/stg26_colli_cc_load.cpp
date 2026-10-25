#include "game/effect/eff_bomb.h"

// The stage 26 collision objects' Load hook (stg26ColliCcLoad here): each of
// its two objects not there yet is created as a plain TObject under the
// module's object root.

extern "C" TObject* stg26ColliCcObject0;
extern "C" TObject* stg26ColliCcObject1;
extern "C" TObject* lbl_8042C110;

extern "C" void stg26ColliCcLoad(void)
{
	if (stg26ColliCcObject0 == NULL) {
		stg26ColliCcObject0 = new TObject(lbl_8042C110);
	}
	if (stg26ColliCcObject1 == NULL) {
		stg26ColliCcObject1 = new TObject(lbl_8042C110);
	}
}
