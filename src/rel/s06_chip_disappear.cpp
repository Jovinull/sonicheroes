// TObjS06Chip::Disappear (the PS2 build's name): with its model still there, the
// chip deletes its material handler and destroys the model, forgetting both;
// then it raises bit 0 of its signal.

#define S06_CHIP_CTOR inline
#include "src/rel/s06_chip_class.inc"

extern "C" void fn_80150958(RpClump* clump);

void TObjS06Chip::Disappear()
{
	if (clump != NULL) {
		if (material != NULL) {
			delete material;
			material = NULL;
		}
		fn_80150958(clump);
		clump = NULL;
	}
	Signal |= 1;
}
