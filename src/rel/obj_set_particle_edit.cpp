// TObjSetParticle::EditOnChange (the PS2 build's name), the same in the
// thirteen stage modules that share the engine core: on an edit the scale is
// kept at or above zero and the particle type between 0 and 0x3F, and the
// type's field label is rewritten as the name of its bank (types from 0x32 are
// the second bank's) followed by the type's number in it. The class is shared
// through obj_set_particle_class.inc.

#define OBJ_SET_PARTICLE_CTOR inline
#include "src/rel/obj_set_particle_class.inc"

extern "C" char* objSetparticleFieldNames[];
extern "C" char objSetparticleTypeFormat[];
extern "C" char* objSetparticleTypeNames[2];
extern "C" int sprintf(char* buffer, const char* format, ...);

void TObjSetParticle::EditOnChange(SETDATA_PARAM* data)
{
	SetParticleParam* param = (SetParticleParam*)data->setBuffer;

	{
		const f32* zero;

		// The minimum's address is taken inside the test, after the scale is
		// read, as the retail orders it.
		if (param->scale < *(zero = setParticleZero)) {
			param->scale = *zero;
		}
	}
	if (param->type < 0) {
		param->type = 0;
	}
	if (param->type >= 0x40) {
		param->type = 0x3F;
	}
	if (param->type < 0x32) {
		sprintf(objSetparticleFieldNames[0], objSetparticleTypeFormat, objSetparticleTypeNames[0],
		    param->type);
	} else {
		sprintf(objSetparticleFieldNames[0], objSetparticleTypeFormat, objSetparticleTypeNames[1],
		    param->type - 0x32);
	}
}
