#include "types.h"

// The stage select panel: three choice widgets, five children it builds, and
// the two dispatchers that drive it per state.
//
// The translation unit runs from fn_1_A098 at 0xA098 to the end of fn_1_A208
// at 0xA460. fn_1_A178 is the destructor and fn_1_A208 the constructor, both
// returning the object; lbl_1_data_3818 is the vtable, which both store at
// this+0x18. The .data it names is left to the module and only referenced
// here, so this unit emits none of its own.
//
// The three widgets are at this+0x80, 0x10C and 0x198, one 0x8C byte element
// apart. The constructor builds them front to back and the destructor tears
// them down back to front, which is what the two orders below say.
//
// fn_80018818 is declared here with the parent it is handed. The other units
// that call it - adv_bar.c, adv_help.c, fade_object.c - declare it with one
// parameter, because at their call sites the second register already holds
// what it needs and no instruction moves it. Here the caller has to load it,
// so the parameter has to be spelled out.

typedef struct Widget {
	u8 padding[0x8C];
} Widget;

typedef struct Select {
	void* name;        // 0x000
	u8 unk4[0x14];     // 0x004
	void* vtable;      // 0x018
	u8 unk1C[0x2];     // 0x01C
	u16 unk1E;         // 0x01E
	u8 unk20[0x8];     // 0x020
	s32 state;         // 0x028
	s32 unk2C;         // 0x02C
	u8 unk30[0x8];     // 0x030
	void* unk38;       // 0x038
	u8 unk3C[0x4];     // 0x03C
	s32 unk40;         // 0x040
	s32 unk44;         // 0x044
	s32 unk48;         // 0x048
	u8 unk4C[0x14];    // 0x04C
	s32 unk60;         // 0x060
	s32 unk64;         // 0x064
	s32 unk68;         // 0x068
	u8 unk6C[0x14];    // 0x06C
	Widget widgets[3]; // 0x080
	s32 slot;          // 0x224
	s32 mode;          // 0x228
	s32 page;          // 0x22C
	void* cursor;      // 0x230
	void* unk234;      // 0x234
	void* unk238;      // 0x238
	void* unk23C;      // 0x23C
	void* unk240;      // 0x240
	u8 unk244[0x58];   // 0x244
	s32 unk29C;        // 0x29C
} Select;

extern "C" u8 lbl_1_data_3060[];
extern "C" void* lbl_1_data_36DC;
extern "C" u8 lbl_1_data_3818[0x2C];

extern "C" void fn_800A80DC(Select* select, s32 value);
extern "C" void fn_800A8620(Select* select, s32 flag);
extern "C" void fn_800A8828(Select* select);
extern "C" void* fn_80018818(void* object, Select* parent);
extern "C" void* fn_1_89E4(void* object, Select* parent);
extern "C" void* fn_1_8B8C(void* object, Select* parent, s32 index);
extern "C" void* fn_1_8E18(void* object, Select* parent);
extern "C" void* fn_1_8FA8(void* object, Select* parent);
extern "C" void* fn_1_B1C(u32 size);
extern "C" void fn_1_AEC(void* memory);
extern "C" void fn_1_905C(Select* select);
extern "C" void fn_1_945C(Select* select);
extern "C" void fn_1_9BB0(Select* select, s32 page);
extern "C" void fn_1_9BD4(Select* select, s32 slot);
extern "C" void fn_1_9BF8(Select* select, s32 mode);
extern "C" void fn_1_9C30(Select* select);
extern "C" void fn_1_9CA4(Select* select);
extern "C" void fn_1_9CCC(Select* select);
extern "C" void fn_1_9E20(Select* select);
extern "C" void fn_1_119D4(Widget* widget);
extern "C" void fn_1_119E0(Widget* widget, s32 option);
extern "C" void fn_1_120C4(Widget* widget, s32 option);
extern "C" void fn_1_120E0(Widget* widget, s32 flag);
extern "C" void fn_1_12124(Widget* widget);

extern "C" void fn_1_A098(Select* select, s32 state)
{
	switch (state) {
		case 5:
			fn_1_945C(select);
			break;
		case 6:
			fn_1_945C(select);
			fn_1_9BB0(select, 0);
			break;
		case 7:
			fn_1_9C30(select);
			select->unk29C = 0;
			break;
	}
}

extern "C" void fn_1_A10C(Select* select)
{
	switch (select->state) {
		case 5:
			fn_1_9E20(select);
			break;
		case 6:
			fn_1_9CCC(select);
			break;
		case 7:
			fn_1_9CA4(select);
			break;
	}
	fn_1_905C(select);
}

extern "C" Select* fn_1_A178(Select* select, s16 free)
{
	if (select != NULL) {
		select->vtable = lbl_1_data_3818;
		fn_1_120E0(&select->widgets[2], -1);
		fn_1_120E0(&select->widgets[1], -1);
		fn_1_120E0(&select->widgets[0], -1);
		fn_800A8620(select, 0);
		if (free > 0) {
			fn_1_AEC(select);
		}
	}
	return select;
}

extern "C" Select* fn_1_A208(Select* select, void* context)
{
	void* child;
	s32 i;

	fn_800A8828(select);
	select->vtable = lbl_1_data_3818;
	fn_1_12124(&select->widgets[0]);
	fn_1_12124(&select->widgets[1]);
	fn_1_12124(&select->widgets[2]);
	select->name  = lbl_1_data_36DC;
	select->unk1E = 0x2A0;

	child = fn_1_B1C(0x34);
	if (child != NULL) {
		fn_1_8FA8(child, select);
	}

	child = fn_1_B1C(0x3C);
	if (child != NULL) {
		child = fn_1_8E18(child, select);
	}
	select->unk234 = child;

	child = fn_1_B1C(0x38);
	if (child != NULL) {
		child = fn_1_8B8C(child, select, 0);
	}
	select->unk238 = child;

	child = fn_1_B1C(0x38);
	if (child != NULL) {
		child = fn_1_8B8C(child, select, 1);
	}
	select->unk23C = child;

	child = fn_1_B1C(0x38);
	if (child != NULL) {
		child = fn_1_89E4(child, select);
	}
	select->unk240 = child;

	select->unk40 = 0xF;
	select->unk44 = 4;
	select->unk48 = 1;
	select->state = 0;
	select->unk38 = lbl_1_data_3060;
	select->slot  = 0;
	select->mode  = 0;
	select->page  = 0;

	child = fn_1_B1C(0x28);
	if (child != NULL) {
		child = fn_80018818(child, select);
	}
	select->cursor = child;

	fn_1_119D4(&select->widgets[0]);
	for (i = 0; i != 22; i++) {
		fn_1_120C4(&select->widgets[0], i);
	}
	fn_1_119E0(&select->widgets[0], 0);
	fn_1_9BD4(select, 0);

	fn_1_119D4(&select->widgets[1]);
	fn_1_120C4(&select->widgets[1], 0);
	fn_1_120C4(&select->widgets[1], 1);
	fn_1_120C4(&select->widgets[1], 2);
	fn_1_120C4(&select->widgets[1], 3);
	fn_1_119E0(&select->widgets[1], 0);
	fn_1_9BF8(select, 0);

	fn_1_120C4(&select->widgets[2], 0);
	fn_1_120C4(&select->widgets[2], 1);
	fn_1_9BB0(select, 0);

	select->unk2C = 1;
	select->unk60 = 5;
	select->unk64 = 0;
	select->unk68 = 1;
	fn_800A80DC(select, 4);
	return select;
}
