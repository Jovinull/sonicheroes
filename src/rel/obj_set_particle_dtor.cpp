// TObjSetParticle's destructor, out of line. With a particle that is still
// alive, it releases it through fn_8005FD8C and clears the pointer. fn_80017800
// is TObject::CheckAlive (PS2 symbols, game/Task.s): it walks the object and
// its parents and fails on the first with the kill bit in Signal. The class is
// shared through obj_set_particle_class.inc, where the destructor is declared
// after the class's first other virtual so this unit does not emit the vtable.

#define OBJ_SET_PARTICLE_CTOR inline
#include "src/rel/obj_set_particle_class.inc"

extern "C" s32 fn_80017800(void* object);
extern "C" void fn_8005FD8C(void* particle, s32 arg);

TObjSetParticle::~TObjSetParticle()
{
	if (particle != NULL) {
		if (fn_80017800(particle)) {
			fn_8005FD8C(particle, 0);
			particle = NULL;
		}
	}
}
