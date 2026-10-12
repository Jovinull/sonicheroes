// EventManager::_bsCallback (the PS2 build's name), changeBoundingSphere's
// callback for each atomic: it gives the atomic's bounding sphere (brought up
// to date first, as RpAtomicGetBoundingSphere does) a radius of 100.
//
// The radius is the module's .rodata word eventSphereRadius, at a 4-byte
// boundary of the event's constants: the unit only refers to it (as a literal
// it would get a pool of its own, 8-aligned, and move).

#include "src/rel/event_manager_class.inc"

extern "C" void fn_8014F854(RpAtomic* atomic);
extern "C" const f32 eventSphereRadius[1];

RpAtomic* EventManager::_bsCallback(RpAtomic* atomic, void* data)
{
	if (atomic->interpolator.flags & 2) {
		fn_8014F854(atomic);
	}
	RwSphere* sphere = &atomic->boundingSphere;
	sphere->radius   = eventSphereRadius[0];
	return atomic;
}
