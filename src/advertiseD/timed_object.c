#include "types.h"

// An attract mode object with a three state tick and a two second timeout,
// plus the pair that opens and closes the resource it needs.
//
// The translation unit runs from fn_1_1074 at 0x1074 to the end of fn_1_1278
// at 0x12A0. fn_1_10E4 is the destructor and fn_1_1154 the constructor, both
// returning the object; lbl_1_data_3E0 is the vtable, which both store at
// this+0x18. The .data it names is left to the module and only referenced
// here, so this unit emits none of its own.
//
// fn_800CC280 takes no arguments. The destructor proves it: the address of the
// vtable is built in r3 and left there across the call, which the compiler
// would not do if the callee read it.

typedef struct Timed {
	void* name;     // 0x00
	u8 unk4[0x14];  // 0x04
	void* vtable;   // 0x18
	u8 unk1C[0x2];  // 0x1C
	u16 unk1E;      // 0x1E
	u8 unk20[0x8];  // 0x20
	s32 state;      // 0x28
	s32 next;       // 0x2C
	u8 unk30[0x8];  // 0x30
	s32 unk38;      // 0x38
	u8 unk3C[0x4];  // 0x3C
	s32 unk40;      // 0x40
	s32 unk44;      // 0x44
	u8 unk48[0x38]; // 0x48
	s32 unk80;      // 0x80
	s32 unk84;      // 0x84
	s32 timer;      // 0x88
} Timed;

extern "C" void* lbl_1_data_294;
extern "C" u8 lbl_1_data_3C8[0x18];
extern "C" u8 lbl_1_data_3E0[0x2C];
extern "C" u8 lbl_1_data_414[];

extern "C" void fn_800A80DC(Timed* timed, s32 value);
extern "C" void fn_800A8620(Timed* timed, s32 flag);
extern "C" void fn_800A8828(Timed* timed);
extern "C" void fn_800CC280(void);
extern "C" void fn_800CCC6C(void* table);
extern "C" void fn_8012CA94(void* resource);
extern "C" void fn_8012CB70(void* resource);
extern "C" void fn_1_AEC(void* memory);
extern "C" void* fn_1_B1C(u32 size);
extern "C" void fn_1_C84(Timed* timed);
extern "C" void fn_1_FDC(Timed* timed);
extern "C" void fn_1_11750(s32 slot);

extern "C" Timed* fn_1_1154(Timed* timed, void* context);

#pragma dont_inline on

extern "C" void fn_1_1074(Timed* timed)
{
	switch (timed->state) {
		case 5:
			fn_1_FDC(timed);
			break;
		case 6:
			fn_1_C84(timed);
			break;
		case 7:
			if (++timed->timer > 120) {
				timed->next = 2;
			}
			break;
	}
}

extern "C" Timed* fn_1_10E4(Timed* timed, s16 free)
{
	if (timed != NULL) {
		timed->vtable = lbl_1_data_3E0;
		fn_800CC280();
		fn_800A8620(timed, 0);
		if (free > 0) {
			fn_1_AEC(timed);
		}
	}
	return timed;
}

extern "C" Timed* fn_1_1154(Timed* timed, void* context)
{
	fn_800A8828(timed);
	timed->vtable = lbl_1_data_3E0;
	timed->name   = lbl_1_data_294;
	timed->unk1E  = 0x8C;

	fn_800A80DC(timed, 3);
	fn_800A80DC(timed, 4);
	fn_800A80DC(timed, 15);

	timed->unk40 = 3;
	timed->unk44 = 15;
	timed->unk38 = 0;
	timed->state = 0;
	timed->next  = 5;

	fn_1_11750(0);
	fn_800CCC6C(lbl_1_data_414);

	timed->unk84 = 0;
	timed->unk80 = 0;
	return timed;
}

extern "C" void fn_1_1210(void* context)
{
	Timed* timed = (Timed*)fn_1_B1C(0x8C);

	if (timed != NULL) {
		fn_1_1154(timed, context);
	}
}

extern "C" void fn_1_1250(void)
{
	fn_8012CA94(lbl_1_data_3C8);
}

extern "C" void fn_1_1278(void)
{
	fn_8012CB70(lbl_1_data_3C8);
}
