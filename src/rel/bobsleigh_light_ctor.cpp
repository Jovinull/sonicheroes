#include "types.h"

// TObjBobsleighLight's constructor (the PS2 build's name and arguments): no
// models yet, full alpha, then the models made from the given one
// (CloneClump, inlined) and every light off.

#include "src/rel/bobsleigh_light_class.inc"

extern "C" char* CL_TObjBobsleighLight;
extern "C" const f32 bobsleighShadowBase[1];

TObjBobsleighLight::TObjBobsleighLight(TObject* parent, RpClump* model)
    : TObject(parent)
{
	ClassName = CL_TObjBobsleighLight;
	DispTime  = 0x118;
	clump     = NULL;
	clumps[0] = NULL;
	clumps[1] = NULL;
	clumps[2] = NULL;
	clumps[3] = NULL;
	clumps[4] = NULL;
	clumps[5] = NULL;
	clumps[6] = NULL;
	clumps[7] = NULL;
	unk3C     = 0;
	alpha     = bobsleighShadowBase[0];
	CloneClump(model);
	lit[0] = 0;
	lit[1] = 0;
	lit[2] = 0;
	lit[3] = 0;
	lit[4] = 0;
	lit[5] = 0;
	lit[6] = 0;
	lit[7] = 0;
}
