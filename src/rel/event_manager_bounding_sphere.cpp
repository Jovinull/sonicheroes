// EventManager::changeBoundingSphere (the PS2 build's name): it gives every
// atomic of the clump a bounding sphere of radius 100 (_bsCallback).

#include "src/rel/event_manager_class.inc"

extern "C" void fn_8014FFBC(
    struct RpClump* clump, RpAtomic* (*callback)(RpAtomic*, void*), void* data);

void EventManager::changeBoundingSphere(struct RpClump* clump)
{
	fn_8014FFBC(clump, _bsCallback, NULL);
}
