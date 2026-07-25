#include "types.h"

// Draws the window's frame: the body, then up to three stacked rows under it.
//
// The translation unit is the single function fn_2_346C, .text 0x346C to
// 0x38F4. Both bounds are read rather than argued: widget_rendering.c ends at
// 0x346C and window_input.c starts at 0x38F4, so this run is what is left
// between two units that already reproduce.
//
// The .rodata is left to the module. The five templates and constants this
// uses are its own, but 0.5 and 2.0 at 0x32C and 0x338 are also read from the
// run at 0x26C0, and a unit's .rodata has to be one contiguous range.
//
// Each row is drawn the same way and differs only in which flag guards it,
// which field of the object holds its width, and which buffer it renders
// into, so the three blocks at the bottom are the same shape three times.
//
// Three things about how this one is built are worth writing down.
//
// It is compiled with -fp_contract off, replacing rather than appending to
// the flag the shared list already sets, because the original does not fuse
// its multiplies into the adds around them. tww, pikmin2 and ogws all carry
// the same override for the same reason.
//
// It is also compiled with common subexpression elimination off. With it on,
// the address of the constant this file reads twice per row gets hoisted
// above the load of the row's own position, which the original does not do.
//
// Turning that off costs one thing back: the original keeps the first flag in
// a register across the two tests that share it, and without elimination the
// compiler reloads it. Reading it into hasA restores that, but only for those
// two. The third test reads the field again, because that is what the
// original does.

typedef struct Vec2 {
	f32 x;
	f32 y;
} Vec2;

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Window {
	u8 unk0[0x28];    // 0x00
	u32 unk28;        // 0x28
	u32 unk2C;        // 0x2C
	u32 unk30;        // 0x30
	u32 unk34;        // 0x34
	u8 unk38[0x4];    // 0x38
	f32 unk3C;        // 0x3C
	f32 unk40;        // 0x40
	f32 unk44;        // 0x44
	f32 unk48;        // 0x48
	f32 unk4C;        // 0x4C
	u8 unk50[0xB0];   // 0x50
	s32 unk100;       // 0x100
	f32 unk104;       // 0x104
	f32 unk108;       // 0x108
	f32 unk10C;       // 0x10C
	u8 unk110[0x400]; // 0x110
	u8 unk510[0x100]; // 0x510
	u8 unk610[0x100]; // 0x610
	u8 unk710[0x100]; // 0x710
} Window;

extern "C" u8 lbl_803E8150[];

// The module already carries these; this unit does not claim the .rodata they
// sit in, so they are named rather than written as literals.
extern "C" const f32 lbl_2_rodata_A0[];
extern "C" const Vec3 lbl_2_rodata_AC;
extern "C" const Vec2 lbl_2_rodata_B8;
extern "C" const Vec2 lbl_2_rodata_C0;
extern "C" const Vec2 lbl_2_rodata_C8;
extern "C" const f32 lbl_2_rodata_32C;
extern "C" const f32 lbl_2_rodata_338;
extern "C" const f32 lbl_2_rodata_33C;
extern "C" const f32 lbl_2_rodata_340;
extern "C" const f32 lbl_2_rodata_344;

extern "C" void fn_2_26C0(Window* window, void* arg1, u8* arg2);
extern "C" void fn_2_32F8(Window* window, Vec3* pos, Vec2* size);
extern "C" void fn_2_3368(Window* window, Vec3* pos, Vec2* size, u8 selected);
extern "C" void fn_8012F858(void* arg0, void* arg1, f32 x, f32 y, s32 arg4);

#pragma opt_common_subs off

extern "C" void fn_2_346C(Window* window)
{
	u8 colour[4];
	u32 hasA;

	colour[0] = 0;
	colour[1] = 0;
	colour[2] = 0;
	colour[3] = 0;
	fn_2_26C0(window, window->unk50, colour);

	if (window->unk28 != 0) {
		fn_2_32F8(window, (Vec3*)&window->unk3C, (Vec2*)&window->unk48);
		fn_8012F858(lbl_803E8150, window->unk110, window->unk3C + lbl_2_rodata_A0[0],
		    window->unk40 + lbl_2_rodata_A0[1], 1);
	}

	Vec3 body = lbl_2_rodata_AC;
	body.x    = window->unk3C;
	body.y    = window->unk40 + window->unk4C;
	body.z    = window->unk44;

	Vec2 size = lbl_2_rodata_B8;
	size.x    = window->unk48;

	hasA = window->unk2C;
	if (hasA != 0 && window->unk30 != 0 && window->unk34 != 0) {
		Vec2 whole = lbl_2_rodata_C0;
		whole.x    = size.x;
		whole.y    = lbl_2_rodata_33C + lbl_2_rodata_340 * size.y;
		fn_2_32F8(window, &body, &whole);
	} else if (hasA != 0 && window->unk30 != 0) {
		Vec2 whole = lbl_2_rodata_C8;
		whole.x    = size.x;
		whole.y    = lbl_2_rodata_33C + lbl_2_rodata_338 * size.y;
		fn_2_32F8(window, &body, &whole);
	}

	if (window->unk2C != 0) {
		Vec3 pos;
		Vec2 row;

		pos.x = lbl_2_rodata_344 + body.x;
		pos.y = lbl_2_rodata_344 + body.y;
		pos.z = lbl_2_rodata_32C;
		row.x = size.x - lbl_2_rodata_33C;
		row.y = size.y;
		fn_2_3368(window, &pos, &row, window->unk100 == 1);
		fn_8012F858(lbl_803E8150, window->unk510,
		    pos.x + lbl_2_rodata_32C * row.x - lbl_2_rodata_32C * window->unk104,
		    body.y + lbl_2_rodata_A0[1], 1);
	}

	if (window->unk30 != 0) {
		Vec3 pos;
		Vec2 row;

		row.x = size.x - lbl_2_rodata_33C;
		row.y = size.y;
		pos.x = lbl_2_rodata_344 + body.x;
		pos.y = size.y + (lbl_2_rodata_344 + body.y);
		pos.z = lbl_2_rodata_32C;
		fn_2_3368(window, &pos, &row, window->unk100 == 2);
		fn_8012F858(lbl_803E8150, window->unk610,
		    pos.x + lbl_2_rodata_32C * row.x - lbl_2_rodata_32C * window->unk108,
		    pos.y + lbl_2_rodata_A0[1] - lbl_2_rodata_344, 1);
	}

	if (window->unk34 != 0) {
		Vec3 pos;
		Vec2 row;

		row.x = size.x - lbl_2_rodata_33C;
		row.y = size.y;
		pos.x = lbl_2_rodata_344 + body.x;
		pos.y = size.y + (size.y + (lbl_2_rodata_344 + body.y));
		pos.z = lbl_2_rodata_32C;
		fn_2_3368(window, &pos, &row, window->unk100 == 3);
		fn_8012F858(lbl_803E8150, window->unk710,
		    pos.x + lbl_2_rodata_32C * row.x - lbl_2_rodata_32C * window->unk10C,
		    pos.y + lbl_2_rodata_A0[1] - lbl_2_rodata_344, 1);
	}
}
