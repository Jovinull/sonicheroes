#include "types.h"

// An attract mode object with a four state tick, plus its constructor and
// destructor.
//
// The translation unit runs from fn_1_6DF0 at 0x6DF0 to the end of fn_1_6EDC
// at 0x6F70. lbl_1_data_1D74 is the vtable, which both the constructor and the
// destructor store at this+0x18; it is left to the module and referenced here
// rather than emitted.
//
// The constructor tears down the child it finds at this+0x5C through that
// child's own vtable rather than by name: slot two, which is where every class
// in this module keeps its destructor.
//
// NonMatching by one instruction. That call loads the vtable into r12 in the
// original and into a scratch argument register here, and the slot load then
// differs with it; everything else in the unit reproduces. Three source forms
// were measured against it - the chained access below, an array index through
// void**, and pulling either the child or the vtable into a local first - and
// none of them moves it.

struct VObject;

typedef struct VTable {
	void* unk0;                            // 0x00
	void* unk4;                            // 0x04
	void (*destroy)(struct VObject*, s32); // 0x08
} VTable;

typedef struct VObject {
	u8 unk0[0x18];  // 0x00
	VTable* vtable; // 0x18
} VObject;

typedef struct Demo {
	u8 unk0[0x18];  // 0x00
	void* vtable;   // 0x18
	u8 unk1C[0xC];  // 0x1C
	s32 state;      // 0x28
	s32 next;       // 0x2C
	s32 counter;    // 0x30
	u8 unk34[0xC];  // 0x34
	s32 unk40;      // 0x40
	s32 unk44;      // 0x44
	s32 unk48;      // 0x48
	u8 unk4C[0x10]; // 0x4C
	VObject* child; // 0x5C
	u8 unk60[0x20]; // 0x60
	s32 unk80;      // 0x80
	s32 unk84;      // 0x84
} Demo;

extern "C" u8 lbl_1_data_1D74[0x2C];

extern "C" void fn_800A8620(Demo* demo, s32 flag);
extern "C" void fn_800A8828(Demo* demo);
extern "C" void fn_1_AEC(void* memory);
extern "C" void fn_1_11750(s32 slot);
extern "C" void fn_1_6B0C(Demo* demo);
extern "C" void fn_1_6B24(Demo* demo);
extern "C" void fn_1_6B70(Demo* demo);
extern "C" void fn_1_6C74(Demo* demo);

extern "C" void fn_1_6DF0(Demo* demo)
{
	switch (demo->state) {
		case 5:
			fn_1_6C74(demo);
			break;
		case 6:
			fn_1_6B70(demo);
			break;
		case 8:
			fn_1_6B24(demo);
			break;
		case 10:
			fn_1_6B0C(demo);
			break;
	}
	demo->counter = demo->counter + 1;
}

extern "C" Demo* fn_1_6E74(Demo* demo, s16 free)
{
	if (demo != NULL) {
		demo->vtable = lbl_1_data_1D74;
		fn_800A8620(demo, 0);
		if (free > 0) {
			fn_1_AEC(demo);
		}
	}
	return demo;
}

extern "C" Demo* fn_1_6EDC(Demo* demo)
{
	fn_800A8828(demo);
	demo->vtable = lbl_1_data_1D74;
	demo->state  = 0;
	demo->next   = 5;
	demo->unk80  = 0;
	demo->unk48  = 1;
	demo->unk40  = 1;
	demo->unk44  = 1;
	demo->unk84  = 1;
	fn_1_11750(0);

	if (demo->child != NULL) {
		demo->child->vtable->destroy(demo->child, 1);
	}
	demo->child = NULL;
	return demo;
}
