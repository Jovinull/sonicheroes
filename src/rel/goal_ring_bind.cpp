#include "types.h"

// TObjGoalRing's bind hook. It publishes the object's handle at +0x18 into the
// stage-local slot, raises bit 6 of that handle's flags, and hooks the field
// callback onto it.
//
// The claim is .text 0x0004D4F0 to 0x0004D54C and nothing else. It reads no
// constant, so it owns no rodata.
//
// The name is read from the layout: the run sits between goalRingCreate and
// the field callback it hooks, which in turn sits directly before
// goalRingRegister.
//
// What the handle at +0x18 is has not been resolved, so the field keeps a
// neutral name; only its use here is reconstructed.
//
// The second parameter reaches fn_801527A4 as its third argument. That is why
// it is moved out of r4 before r4 is reused, which reads as a dead move until
// the callee's third parameter is accounted for.
//
// The callback it hooks is still assembly. It is renamed to a shared name in
// every module's symbols.txt rather than left as fn_<id>_4D54C, because a
// module-id name in a source linked into twelve modules resolves in one and
// breaks the rest.
//
// The run is the same in the nine stage modules that carry it, checked by
// normalising the disassembly and comparing across modules.

typedef struct Handle {
	u8 unk0[0x08]; // 0x00
	u32 flags;     // 0x08
} Handle;

typedef struct GoalRing {
	u8 unk0[0x18];  // 0x00
	Handle* handle; // 0x18
} GoalRing;

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" Handle* goalRingBoundHandle;

extern "C" void goalRingFieldCallback(void);

extern "C" void fn_801527A4(Handle* handle, void* callback, void* arg);

extern "C" GoalRing* goalRingBind(GoalRing* object, void* arg)
{
	goalRingBoundHandle = object->handle;
	goalRingBoundHandle->flags |= 0x40;

	fn_801527A4(goalRingBoundHandle, (void*)goalRingFieldCallback, arg);

	return object;
}
