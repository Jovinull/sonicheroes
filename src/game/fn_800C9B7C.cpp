// Destructor of a sound stream object (vtable lbl_80254FF0; the class name is UNKNOWN; see
// fn_800CB15C): stops and un-pauses its ADX player (+0x3C), resets its ids and state, destroys the
// player, clears its slot in lbl_8042B634 (index +0x28), runs the TObject destructor and frees the
// object when flags > 0. Returns the object.
#include "types.h"

struct Stream800C9B7C {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	s8 slot;       // 0x28
	s8 state;      // 0x29
	s8 unknown2A;  // 0x2A
	u8 flags;      // 0x2B (bit 0: paused)
	s32 unknown2C; // 0x2C
	s32 unknown30; // 0x30
	u8 pad34[0x3C - 0x34];
	void* player; // 0x3C (ADXT handle)
};

struct THeapCtrl;

extern "C" {
extern void* lbl_80254FF0[];
extern Stream800C9B7C* lbl_8042B634[2];
extern THeapCtrl* lbl_8042C148;
void ADXT_Stop(void* handle);
void ADXT_Pause(void* handle, s32 on);
void ADXT_Destroy(void* handle);
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);
}

// Same body as the per-stream reset in fn_800CB15C.
static inline void StopStream(Stream800C9B7C* s)
{
	ADXT_Stop(s->player);
	ADXT_Pause(s->player, 0);
	s->unknown2C = -1;
	s->unknown30 = -1;
	s->unknown2A = -1;
	s->state     = 0;
	s->flags &= ~1;
}

extern "C" Stream800C9B7C* fn_800C9B7C(Stream800C9B7C* s, s16 flags)
{
	if (s != NULL) {
		s->vtable = lbl_80254FF0;
		StopStream(s);
		if (s->player != NULL) {
			ADXT_Destroy(s->player);
		}
		lbl_8042B634[s->slot] = NULL;
		__dt__7TObjectFv(s, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, s);
		}
	}
	return s;
}
