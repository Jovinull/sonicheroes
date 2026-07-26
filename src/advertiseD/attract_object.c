#include "types.h"

// The attract mode's main object: six choice widgets, the counters behind
// them, and the help panel it spawns.
//
// The translation unit runs from fn_1_C54C at 0xC54C to the end of fn_1_C608
// at 0xC8D0. fn_1_C54C is the destructor and fn_1_C608 the constructor, both
// returning the object; lbl_1_data_3CA8 is the vtable, which both store at
// this+0x18. The .data and .rodata they name are left to the module and only
// referenced here, so this unit emits neither.
//
// The six widgets are one array of 0x8C byte elements at this+0x9C, which is
// what __construct_array builds. They are not set up in index order: the
// original does 4, 0, 1, 3, 2, 5, and that is the order below.

typedef struct Widget {
	u8 padding[0x8C];
} Widget;

typedef struct Settings {
	u8 unk0[0x4]; // 0x00
	s32 mode;     // 0x04
} Settings;

typedef struct Attract {
	void* name;        // 0x000
	u8 unk4[0x14];     // 0x004
	void* vtable;      // 0x018
	u8 unk1C[0x2];     // 0x01C
	u16 unk1E;         // 0x01E
	u8 unk20[0x8];     // 0x020
	s32 unk28;         // 0x028
	s32 unk2C;         // 0x02C
	u8 unk30[0x8];     // 0x030
	void* unk38;       // 0x038
	u8 unk3C[0x4];     // 0x03C
	s32 unk40;         // 0x040
	s32 unk44;         // 0x044
	s32 unk48;         // 0x048
	u8 unk4C[0x34];    // 0x04C
	s32 unk80;         // 0x080
	s32 unk84;         // 0x084
	s32 unk88;         // 0x088
	s32 unk8C;         // 0x08C
	s32 unk90;         // 0x090
	s32 unk94;         // 0x094
	s32 unk98;         // 0x098
	Widget widgets[6]; // 0x09C
	u8 unk3E4[0xC];    // 0x3E4
	f32 unk3F0;        // 0x3F0
	f32 unk3F4;        // 0x3F4
	void* unk3F8;      // 0x3F8
	s32 unk3FC;        // 0x3FC
	void* anim;        // 0x400
	f32 unk404;        // 0x404
	s32 unk408;        // 0x408
} Attract;

extern "C" const f32 lbl_1_rodata_102C;
extern "C" u8 lbl_1_data_3AB4[];
extern "C" void* lbl_1_data_3CA4;
extern "C" u8 lbl_1_data_3CA8[0x2C];
extern "C" u8 lbl_80303EC8[];

extern "C" void __construct_array(void* base, void* ctor, void* dtor, s32 size, s32 count);
extern "C" void __destroy_arr(void* base, void* dtor, s32 size, s32 count);
extern "C" void fn_800A80DC(Attract* attract, s32 value);
extern "C" void fn_800A8620(Attract* attract, s32 flag);
extern "C" void fn_800A8828(Attract* attract);
extern "C" Settings* fn_800A8BF0(void* settings);
extern "C" void* fn_80126200(Attract* attract);
extern "C" void fn_1_120E0(void);
extern "C" void fn_1_12124(void);
extern "C" void* fn_1_10F40(void* help, Attract* attract);
extern "C" void fn_1_119E0(Widget* widget, s32 option);
extern "C" void fn_1_120C4(Widget* widget, s32 option);
extern "C" void fn_1_11750(s32 slot);
extern "C" void* fn_1_B1C(u32 size);
extern "C" void fn_1_AEC(void* memory);
extern "C" s32 fn_1_A714(Attract* attract);
extern "C" s32 fn_1_A76C(Attract* attract);
extern "C" s32 fn_1_A808(Attract* attract);
extern "C" s32 fn_1_A91C(Attract* attract);
extern "C" s32 fn_1_A9E0(Attract* attract);

#pragma opt_common_subs off

extern "C" Attract* fn_1_C54C(Attract* attract, s16 free)
{
	if (attract != NULL) {
		attract->vtable = lbl_1_data_3CA8;
		if ((attract->unk48 != 0 && attract->unk40 == 4)
		    || (attract->unk48 == 0 && attract->unk44 == 4)) {
			fn_1_11750(1);
		}
		__destroy_arr(attract->widgets, (void*)fn_1_120E0, 0x8C, 6);
		fn_800A8620(attract, 0);
		if (free > 0) {
			fn_1_AEC(attract);
		}
	}
	return attract;
}

#pragma opt_common_subs on

extern "C" Attract* fn_1_C608(Attract* attract, void* context)
{
	void* help;

	fn_800A8828(attract);
	attract->vtable = lbl_1_data_3CA8;
	__construct_array(attract->widgets, (void*)fn_1_12124, (void*)fn_1_120E0, 0x8C, 6);
	attract->name  = lbl_1_data_3CA4;
	attract->unk1E = 0x40C;
	attract->unk48 = 0;
	attract->unk40 = 4;
	attract->unk44 = 4;
	attract->unk28 = 0;
	attract->unk2C = 5;
	attract->unk80 = 0;
	attract->unk38 = lbl_1_data_3AB4;

	attract->unk3F8 = fn_80126200(attract);
	attract->unk3FC = 0;
	attract->unk408 = 1;
	attract->anim   = NULL;
	attract->unk404 = lbl_1_rodata_102C;

	switch (fn_800A8BF0(lbl_80303EC8)->mode) {
		case 3:
		case 8:
			attract->unk94 = 2;
			break;
		default:
			attract->unk94 = 0;
			break;
	}

	attract->unk84 = fn_1_A9E0(attract);
	attract->unk88 = fn_1_A91C(attract);
	attract->unk90 = fn_1_A76C(attract);
	attract->unk8C = fn_1_A808(attract);
	attract->unk98 = fn_1_A714(attract);

	attract->unk3F0 = lbl_1_rodata_102C;
	attract->unk3F4 = attract->unk3F0;

	fn_1_120C4(&attract->widgets[4], 0);
	fn_1_120C4(&attract->widgets[4], 1);
	fn_1_120C4(&attract->widgets[4], 2);
	fn_1_120C4(&attract->widgets[4], 3);
	fn_1_120C4(&attract->widgets[4], 4);
	fn_1_119E0(&attract->widgets[4], attract->unk94);

	fn_1_120C4(&attract->widgets[0], 0);
	fn_1_120C4(&attract->widgets[0], 1);
	fn_1_120C4(&attract->widgets[0], 2);
	fn_1_119E0(&attract->widgets[0], attract->unk84);

	fn_1_120C4(&attract->widgets[1], 0);
	fn_1_120C4(&attract->widgets[1], 1);
	fn_1_119E0(&attract->widgets[1], attract->unk88);

	fn_1_120C4(&attract->widgets[3], 0);
	fn_1_120C4(&attract->widgets[3], 1);
	fn_1_119E0(&attract->widgets[3], attract->unk90);

	fn_1_120C4(&attract->widgets[2], 0);
	fn_1_120C4(&attract->widgets[2], 1);
	fn_1_120C4(&attract->widgets[2], 2);
	fn_1_120C4(&attract->widgets[2], 3);
	fn_1_120C4(&attract->widgets[2], 4);
	fn_1_120C4(&attract->widgets[2], 5);
	fn_1_119E0(&attract->widgets[2], attract->unk8C);

	fn_1_120C4(&attract->widgets[5], 0);
	fn_1_120C4(&attract->widgets[5], 1);
	fn_1_119E0(&attract->widgets[5], attract->unk98);

	help = fn_1_B1C(0x30);
	if (help != NULL) {
		fn_1_10F40(help, attract);
	}

	fn_1_11750(5);
	fn_800A80DC(attract, 4);
	return attract;
}
