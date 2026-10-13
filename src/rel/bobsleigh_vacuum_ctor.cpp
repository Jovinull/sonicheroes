#include "types.h"

// TObjBobsleighVacuum's constructor (the PS2 build's name and argument): the
// two-shape volume that pulls the bobsleigh in, with a larger first shape for
// a bobsleigh of kind 6.

#include "src/rel/bobsleigh_volume_ctor.inc"

extern "C" void* bobsleighVacuumVtable[];
extern "C" char* CL_TObjBobsleighVacuum;
extern "C" CCL_INFO bobsleighVacuumCclInfo;
extern "C" f32 bobsleighVacuumWideRadius;

extern "C" BobsleighVolume* __ct__19TObjBobsleighVacuumFP7TObject(
    BobsleighVolume* object, void* parent)
{
	__ct__7TObjectFP7TObject(object, parent);
	__ct__7C_COLLIFv(object->colli);
	object->vtable    = bobsleighVacuumVtable;
	object->className = CL_TObjBobsleighVacuum;
	object->dispTime  = 0xB4;
	object->done      = 0;
	Init__7C_COLLIFP8CCL_INFOiUc(object->colli, &bobsleighVacuumCclInfo, 2, 4);
	if (object->parent->kind == 6) {
		object->info->a = bobsleighVacuumWideRadius;
	}
	CalcRange__7C_COLLIFv(object->colli);
	return object;
}
