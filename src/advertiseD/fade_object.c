#include "types.h"

// The object the three steppers in fade_step.c drive: it holds a state, the
// pair of positions it is moving between, and the handle it pushes the current
// one into.
//
// The translation unit runs from fn_1_ECD0 at 0xECD0 to the end of fn_1_EEE4
// at 0xEF8C. fn_1_EE7C is the destructor and fn_1_EEE4 the constructor, both
// returning the object; lbl_1_data_79B0 is the vtable, which both store at
// this+0x18. The two index tables at .rodata 0x1950 and 0x1978 and the block
// at .data 0x75FC are left to the module and only referenced here, so this
// unit emits neither section.
//
// fn_1_ECD0 has no prologue at all - it only loads and stores, so it is a leaf
// and the compiler gives it no frame.
//
// The constructor ignores its second argument. Every caller passes one, which
// is why it is kept.

typedef struct Position {
	s32 unk0;  // 0x00
	f32 value; // 0x04
} Position;

typedef struct IndexPair {
	s32 from; // 0x00
	s32 to;   // 0x04
} IndexPair;

typedef struct Block {
	u8 unk0[0xD0];  // 0x000
	u8 first[0x8];  // 0x0D0
	u8 unkD8[0x60]; // 0x0D8 is the pointer below, see the note
	u8 second[0x8]; // 0x138
} Block;

typedef struct Fade {
	u8 unk0[0x18]; // 0x00
	void* vtable;  // 0x18
	u8 unk1C[0xC]; // 0x1C
	void* handle;  // 0x28
	f32 from;      // 0x2C
	f32 to;        // 0x30
	s32 kind;      // 0x34
	s32 state;     // 0x38
	s32 previous;  // 0x3C
	s32 index;     // 0x40
	s32 target;    // 0x44
} Fade;

extern "C" const IndexPair lbl_1_rodata_1950[];
extern "C" const IndexPair lbl_1_rodata_1978[];
extern "C" const f32 lbl_1_rodata_19A4;
extern "C" u8 lbl_1_data_75FC[];
extern "C" u8 lbl_1_data_79B0[0x2C];

extern "C" void dtor_800186D0(Fade* fade, s32 flag);
extern "C" void fn_80018818(Fade* fade);
extern "C" void fn_8012CC20(void* handle);
extern "C" void fn_8012CEF0(void* handle, f32 value);
extern "C" void fn_1_AEC(void* memory);
extern "C" void fn_1_EC2C(Fade* fade);
extern "C" void fn_1_EC70(Fade* fade);
extern "C" void fn_1_EC74(Fade* fade);
extern "C" void fn_1_ECD0(Fade* fade, s32 state);

#define POSITIONS (*(Position**)(lbl_1_data_75FC + 0xD8))

#pragma dont_inline on

extern "C" void fn_1_ECD0(Fade* fade, s32 state)
{
	fade->state    = state;
	fade->previous = state;

	switch (fade->state) {
		case 1:
			fade->index = fade->target;
			fade->from  = POSITIONS[lbl_1_rodata_1950[fade->index].from].value;
			fade->to    = POSITIONS[lbl_1_rodata_1950[fade->index].to].value;
			break;
		case 2:
			break;
		case 3:
			fade->from = POSITIONS[lbl_1_rodata_1978[fade->index].from].value;
			fade->to   = POSITIONS[lbl_1_rodata_1978[fade->index].to].value;
			break;
	}
}

extern "C" void fn_1_EDB8(Fade* fade)
{
	if (fade->handle != NULL) {
		fn_8012CC20(fade->handle);
	}
}

extern "C" void fn_1_EDE4(Fade* fade)
{
	if (fade->previous != fade->state) {
		fn_1_ECD0(fade, fade->previous);
	}

	switch (fade->state) {
		case 1:
			fn_1_EC74(fade);
			break;
		case 2:
			fn_1_EC70(fade);
			break;
		case 3:
			fn_1_EC2C(fade);
			break;
	}

	if (fade->handle != NULL) {
		fn_8012CEF0(fade->handle, fade->from);
	}
}

extern "C" Fade* fn_1_EE7C(Fade* fade, s16 free)
{
	if (fade != NULL) {
		fade->vtable = lbl_1_data_79B0;
		dtor_800186D0(fade, 0);
		if (free > 0) {
			fn_1_AEC(fade);
		}
	}
	return fade;
}

extern "C" Fade* fn_1_EEE4(Fade* fade, void* owner, s32 kind)
{
	fn_80018818(fade);
	fade->vtable   = lbl_1_data_79B0;
	fade->from     = lbl_1_rodata_19A4;
	fade->kind     = kind;
	fade->state    = 0;
	fade->previous = 1;

	if (kind == 0) {
		fade->handle = lbl_1_data_75FC + 0xD0;
		fade->index  = 0;
		fade->target = 1;
	} else {
		fade->handle = lbl_1_data_75FC + 0x138;
		fade->index  = 0;
		fade->target = 0;
	}
	return fade;
}
