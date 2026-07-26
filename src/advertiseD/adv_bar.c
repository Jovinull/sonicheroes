#include "types.h"

// TAdvBar: the attract mode bar. The class names itself  -  the constructor
// stores the string "TAdvBar" at this+0x0, which is where the file name comes
// from rather than from guessing at what it draws.
//
// The translation unit runs from fn_1_10D1C at 0x10D1C to the end of
// fn_1_10E1C at 0x10E44. fn_1_10D1C is the destructor and fn_1_10D84 the
// constructor, both returning the object; lbl_1_data_7D6C is the vtable, which
// both of them store at this+0x18. Two of that vtable's entries live in the
// run before this one, so the .data is left to the module and only referenced
// here: this unit emits none of its own.
//
// fn_1_10DF4 and fn_1_10E1C open and close the resource the bar needs, named
// by the descriptor at .data 0x7D54 ("./advertise/%s/adv_bar.one").

typedef struct BarEntry {
	const char* name; // 0x00
	f32 value;        // 0x04
} BarEntry;

typedef struct BarDesc {
	s32 unk0;          // 0x00
	s32 unk4;          // 0x04
	BarEntry* entries; // 0x08
	u8 unkC[0x5C];     // 0x0C
} BarDesc;

typedef struct AdvBar {
	const char* name; // 0x00
	u8 unk4[0x14];    // 0x04
	void* vtable;     // 0x18
	u8 unk1C[0x2];    // 0x1C
	u16 unk1E;        // 0x1E
	u8 unk20[0x8];    // 0x20
	BarDesc* desc;    // 0x28
	f32 unk2C;        // 0x2C
} AdvBar;

extern "C" const char* lbl_1_data_7CBC;
extern "C" BarDesc lbl_1_data_7CD0;
extern "C" u8 lbl_1_data_7D54[0x18];
extern "C" u8 lbl_1_data_7D6C[0x2C];

extern "C" void dtor_800186D0(AdvBar* bar, s32 flag);
extern "C" void fn_80018818(AdvBar* bar);
extern "C" void fn_8012CA94(void* resource);
extern "C" void fn_8012CB70(void* resource);
extern "C" void fn_1_AEC(void* memory);

extern "C" AdvBar* fn_1_10D1C(AdvBar* bar, s16 free)
{
	if (bar != NULL) {
		bar->vtable = lbl_1_data_7D6C;
		dtor_800186D0(bar, 0);
		if (free > 0) {
			fn_1_AEC(bar);
		}
	}
	return bar;
}

extern "C" AdvBar* fn_1_10D84(AdvBar* bar)
{
	fn_80018818(bar);
	bar->vtable = lbl_1_data_7D6C;
	bar->name   = lbl_1_data_7CBC;
	bar->unk1E  = 0x30;
	bar->desc   = &lbl_1_data_7CD0;
	bar->unk2C  = bar->desc->entries->value;
	return bar;
}

extern "C" void fn_1_10DF4(void)
{
	fn_8012CA94(lbl_1_data_7D54);
}

extern "C" void fn_1_10E1C(void)
{
	fn_8012CB70(lbl_1_data_7D54);
}
