// Destructor of the main sound stream object (vtable lbl_80255068; the class name is UNKNOWN; see
// fn_800CC1C4): stops and un-pauses its ADX player (+0x44), resets and deletes its attached
// stream (+0x4C), clears the state and paused bit, destroys the player, clears its slot in
// lbl_8042B624 (index +0x28), runs the TObject destructor and frees the object when flags > 0.
// Returns the object.
#include "types.h"

struct Attached800CA430 {
	~Attached800CA430() { }

	s8 state; // 0x0
	u8 pad1[7];
	void* handle; // 0x8
};

struct Stream800CA430 {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	s8 slot;  // 0x28
	s8 state; // 0x29
	u8 pad2A;
	u8 flags; // 0x2B (bit 0: paused)
	u8 pad2C[0x44 - 0x2C];
	void* player; // 0x44 (ADXT handle)
	u8 pad48[4];
	Attached800CA430* attached; // 0x4C
};

struct THeapCtrl;

extern "C" {
extern void* lbl_80255068[];
extern Stream800CA430* lbl_8042B624[2];
extern THeapCtrl* lbl_8042C148;
void ADXT_Stop(void* handle);
void ADXT_Pause(void* handle, s32 on);
void ADXT_ResetEntry(void* handle);
void ADXT_Destroy(void* handle);
void __dl__FPv(void* p);
void __dt__7TObjectFv(void* o, s32 flags);
void Free__9THeapCtrlFPv(THeapCtrl* heap, void* p);
}

// Same reset as in fn_800CC1C4.
static inline void StopStream(Stream800CA430* s)
{
	Attached800CA430* attached;

	ADXT_Stop(s->player);
	ADXT_Pause(s->player, 0);
	attached = s->attached;
	if (attached != NULL) {
		ADXT_ResetEntry(attached->handle);
		attached->state = -1;
	}
	s->state = 0;
	s->flags &= ~1;
}

extern "C" Stream800CA430* fn_800CA430(Stream800CA430* s, s16 flags)
{
	if (s != NULL) {
		s->vtable = lbl_80255068;
		StopStream(s);
		if (s->attached != NULL) {
			delete s->attached;
		}
		if (s->player != NULL) {
			ADXT_Destroy(s->player);
		}
		lbl_8042B624[s->slot] = NULL;
		__dt__7TObjectFv(s, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, s);
		}
	}
	return s;
}
