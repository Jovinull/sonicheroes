// TObjS06Chip's destructor, out of line. With a clump, it deletes the clump's
// DealMaterial if there is one and destroys the clump (fn_80150958), clearing
// both pointers; then it ends the set object when its condition has bit 0x10000
// set. The class is shared through s06_chip_class.inc, where the destructor is
// declared after the class's first other virtual so this unit does not emit the
// vtable.

#define S06_CHIP_CTOR inline
#include "src/rel/s06_chip_class.inc"

extern "C" void fn_80150958(RpClump* clump);

TObjS06Chip::~TObjS06Chip()
{
	if (clump != NULL) {
		if (material != NULL) {
			delete material;
			material = NULL;
		}
		fn_80150958(clump);
		clump = NULL;
	}
	if (TstConditionBit(0x10000)) {
		SetEnd();
	}
}
