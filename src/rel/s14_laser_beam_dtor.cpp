// TObjS14LaserBeamSet's destructor, out of line. It deletes the object's
// children first through fn_8001867C, which is TObject::DeleteChild in the PS2
// symbols (`while (Child) delete Child;`, in game/Task.s); the vtable resets
// and the base destructors are the compiler's. The class is shared through
// s14_laser_beam_class.inc, where the destructor is declared after the class's
// first other virtual so this unit does not emit the vtable.

#define S14_LASER_BEAM_CTOR inline
#include "src/rel/s14_laser_beam_class.inc"

extern "C" void fn_8001867C(TObject* object);

TObjS14LaserBeamSet::~TObjS14LaserBeamSet()
{
	fn_8001867C(this);
}
