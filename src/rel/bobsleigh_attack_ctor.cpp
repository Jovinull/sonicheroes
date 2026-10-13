#include "types.h"

// TObjBobsleighAttack's constructor (the PS2 build's name and argument): the
// one-shape volume a bobsleigh hits with, its character id picked by the
// bobsleigh's team.

#include "src/rel/bobsleigh_volume_ctor.inc"

extern "C" void* bobsleighAttackVtable[];
extern "C" char* CL_TObjBobsleighAttack;
extern "C" CCL_INFO bobsleighAttackCclInfo;

extern "C" BobsleighVolume* __ct__19TObjBobsleighAttackFP7TObject(
    BobsleighVolume* object, BobsleighParent* parent)
{
	__ct__7TObjectFP7TObject(object, parent);
	__ct__7C_COLLIFv(object->colli);
	object->vtable    = bobsleighAttackVtable;
	object->className = CL_TObjBobsleighAttack;
	object->dispTime  = 0xB4;
	object->done      = 0;
	Init__7C_COLLIFP8CCL_INFOiUc(object->colli, &bobsleighAttackCclInfo, 1, 1);
	switch (parent->team) {
		case 0:
			object->characterId = 7;
			break;
		case 1:
			object->characterId = 8;
			break;
		case 2:
			object->characterId = 9;
			break;
		case 3:
			object->characterId = 0xA;
			break;
	}
	return object;
}
