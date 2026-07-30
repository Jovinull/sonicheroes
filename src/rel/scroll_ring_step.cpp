#include "types.h"

// TObjScrollRing's per frame step. It advances the ring's own animation, drifts
// the scroll offset unless the object is parked, and then hands its motion
// block to the shared updater.
//
// The claim is .text 0x8DB0 to 0x8E28 and nothing else. The two floats stay in
// the module's rodata and are read through the shared names below; the function
// that follows at 0x8E28 is a different hook and is left for its own change.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out, as everywhere
// else.
//
// The guard is written with the constant on the left. Both orders compare the
// same pair, but the original loads the constant into the first operand of the
// fcmpu, which is what `0.0f != drift` emits and what `drift != 0.0f` does not.

struct ScrollRing {
	u8 unk0[0x88];   // 0x00
	u8 motion[0x2];  // 0x88, handed to the shared updater
	u16 flags;       // 0x8A
	u8 unk8C[0x1C];  // 0x8C
	u8 animation[4]; // 0xA8
	f32 scroll;      // 0xAC
};

// The bit that parks the ring. A zero drift still steps the offset unless this
// is set, which is why the guard needs both halves.
#define SCROLL_RING_PARKED 2

extern "C" f32 fn_801991B4(void* animation);
extern "C" void fn_8005C16C(void* motion, s32 mode);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" const f32 scrollRingStopped;
extern "C" const f32 scrollRingDrift;

extern "C" void scrollRingStep(ScrollRing* object)
{
	if (scrollRingStopped != fn_801991B4(object->animation)
	    || (object->flags & SCROLL_RING_PARKED) == 0) {
		object->scroll += scrollRingDrift;
	}

	fn_8005C16C(object->motion, 768);
}
