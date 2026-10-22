#include "types.h"

// TObjHintRing's destructor (the PS2 build's name, by its place in the PS2
// order): it releases the ring and inside models and deletes the four hint
// balls (HintBall's implicit destructor inlined), ends the placement when its
// condition bit 0x10000 is set, then the set-object base and the object base
// run down and the object is freed when the delete flag asks for it.

#include "src/rel/hint_ball_class.inc"

typedef struct RpClump RpClump;

typedef struct HintRingFrame {
	u8 unk00[0x18];
	u32 flags; // 0x18
} HintRingFrame;

typedef struct HintRing {
	u8 unk00[0x18];       // 0x00
	void** vtable;        // 0x18
	u8 unk1C[0xC];        // 0x1C
	HintRingFrame* frame; // 0x28, the set object's
	void** setObjVtable;  // 0x2C
	u8 unk30[0x2C];       // 0x30
	RpClump* ring;        // 0x5C
	u8 unk60[0x8];        // 0x60
	RpClump* inside;      // 0x68
	u8 unk6C[0x8];        // 0x6C
	HintBall* balls[4];   // 0x74
} HintRing;

extern "C" void* lbl_8042C148;
extern "C" void* hintringVtable[];

extern "C" void fn_80150958(RpClump* clump);
extern "C" void SetEnd__10TObjSetObjFv(void* setObj);
extern "C" void __dt__10TObjSetObjFv(void* setObj, s32 flags);
extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" HintRing* __dt__12TObjHintRingFv(HintRing* ring, s16 flags)
{
	if (ring != NULL) {
		ring->vtable       = hintringVtable;
		ring->setObjVtable = hintringVtable + 0xB;
		if (ring->ring != NULL) {
			fn_80150958(ring->ring);
			ring->ring = NULL;
		}
		if (ring->inside != NULL) {
			fn_80150958(ring->inside);
			ring->inside = NULL;
		}
		if (ring->balls[0] != NULL) {
			delete ring->balls[0];
		}
		if (ring->balls[1] != NULL) {
			delete ring->balls[1];
		}
		if (ring->balls[2] != NULL) {
			delete ring->balls[2];
		}
		if (ring->balls[3] != NULL) {
			delete ring->balls[3];
		}
		if (ring->frame->flags & 0x10000) {
			SetEnd__10TObjSetObjFv(&ring->frame);
		}
		__dt__10TObjSetObjFv(&ring->frame, 0);
		__dt__7TObjectFv(ring, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, ring);
		}
	}
	return ring;
}
