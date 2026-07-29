#include "types.h"

// The emblem counter the attract mode puts on screen: a task that owns two
// animations, counts frames, and draws the emblem total as digits.
//
// The translation unit runs from fn_2_1454 at 0x1454 to the end of fn_2_1CE4
// at 0x1ED4, and owns .rodata 0x48 to 0x88 and .data 0x190 to 0x2A8. It is the
// only cut available out of 0x1454: everything before 0x1ED4 leaks, and 0x1ED4
// is where task_callback_setters.c already starts.
//
// It is a C++ class written out by hand. fn_2_19D0 is the constructor and
// fn_2_1914 the destructor, both returning the object; lbl_2_data_244 is the
// vtable, which the two of them store at this+0x18. Writing them as plain
// extern "C" functions that call __construct_array and __destroy_arr directly
// reproduces what the compiler would have emitted from the class, and keeps
// the names dtk needs.
//
// The .rodata has to be claimed rather than left to the module: fn_2_1454
// converts an int to a float twice, and the two eight byte constants the
// compiler emits for that live at 0x68 and 0x70, inside the range. The .bss at
// 0x10 to 0x40 is this unit's by the same argument the rest of the boundary
// rests on, but it is left to the module and only declared here. Claiming it
// costs the sixteen bytes of .bss that sit in front of it: they belong to the
// unit before this one, which is not carved yet, and once the range after them
// is claimed dtk has no symbol left to hang them on, so the module comes out
// short. It can be claimed once 0x38 to 0x136C is written.
//
// Three things about how this one is built are worth writing down.
//
// It is compiled with -pool off. By default this compiler pools like data
// objects, so a function touching several of its own globals loads the section
// base into a register once and reaches all of them off it. The original goes
// through each symbol on its own, which is what the flag restores.
//
// It is compiled with -fp_contract off, replacing rather than appending to the
// flag the shared list already sets, because fn_2_1454 does not fuse its
// multiplies into the subtractions around them.
//
// And it is compiled with inlining off. -inline auto is happy to paste
// fn_2_1454 into both of its callers and fn_2_19D0 into fn_2_1B7C; the
// original calls all three.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Task {
	u8 padding[0x4C];
} Task;

typedef struct AnimSlot {
	void* unk0;   // 0x00
	void* motion; // 0x04
} AnimSlot;

// The two descriptors the emblem hands to its task, one per animation.
typedef struct AnimDesc {
	void* target;     // 0x00, filled in by fn_2_1CE4
	s32 unk4;         // 0x04
	u8 unk8[0x8];     // 0x08
	f32 unk10;        // 0x10
	f32 unk14;        // 0x14
	f32 unk18;        // 0x18
	const char* file; // 0x1C
	s32 unk20;        // 0x20
	s32 unk24;        // 0x24
	s32 unk28;        // 0x28
	u8 unk2C[0x1C];   // 0x2C
} AnimDesc;

typedef struct Emblem {
	const char* name;  // 0x00
	u8 unk4[0x14];     // 0x04
	void* vtable;      // 0x18
	u8 unk1C[0x2];     // 0x1C
	u16 unk1E;         // 0x1E
	u8 unk20[0x8];     // 0x20
	Task parts[2];     // 0x28
	AnimSlot* anim[2]; // 0xC0
	s32 timer;         // 0xC8
	s32 count;         // 0xCC
	u16 digits[4];     // 0xD0
	f32 x;             // 0xD8
	f32 y;             // 0xDC
} Emblem;

typedef struct Screen {
	u8 unk0[0x4];  // 0x00
	s32 width;     // 0x04
	s32 height;    // 0x08
	u8 unkC[0x34]; // 0x0C
} Screen;

typedef struct SaveState {
	u8 padding[0x22]; // 0x00
	u8 emblems;       // 0x22
} SaveState;

typedef void (*VtEntry)(void);

extern "C" Screen lbl_8029BB80;
extern "C" void* lbl_8042C388;
extern "C" void** lbl_8042C9A4;
extern "C" u8 lbl_80303EC8[];
extern "C" u8 lbl_803E774C[];
extern "C" u8 lbl_803E8150[];
extern "C" const f32 lbl_80239978[];
extern "C" const f32 lbl_80239984[];

extern "C" void __construct_array(void* base, void* ctor, void* dtor, s32 size, s32 count);
extern "C" void __destroy_arr(void* base, void* dtor, s32 size, s32 count);
extern "C" void __dt__7TObjectFv(Emblem* emblem, s32 flag);
extern "C" void dtor_800FE334(void);
extern "C" void fn_800FE3FC(void);
extern "C" void fn_80017854(void);
extern "C" void __ct__7TObjectFP7TObject(Emblem* emblem);
extern "C" s32 fn_800A8BF8(void* settings);
extern "C" void fn_800B52E8(void* handle, s32 id, s32 arg1, s32 arg2);
extern "C" void* fn_800BBF20(void* archive, s32 index, void* heap);
extern "C" void* fn_800BC46C(void* archive, s32 index, void* heap);
extern "C" void* fn_800BC580(void* archive, s32 index, void* heap);
extern "C" void fn_800BCBD4(void* archive, s32 flag);
extern "C" void* fn_800BCC84(void* archive, const char* path, s32 flag);
extern "C" void* fn_800FE464(Task* task);
extern "C" void* fn_80057644(s32 size);
extern "C" SaveState* fn_80116D2C(void* state);
extern "C" void fn_80130464(s32 type);
extern "C" void fn_801301C8(void* context);
extern "C" u32 fn_8012EF3C(void* context, u16* text);
extern "C" void fn_8012F14C(void* context);
extern "C" void fn_8012F1F8(void* context, u16* text, f32 x, f32 y, f32 sx, f32 sy, s32 flag);
extern "C" void fn_8012F3D0(void* context, u16* text);
extern "C" void fn_8012F728(void* context);
extern "C" void fn_8012FF6C(void* context);
extern "C" void fn_8012FFD4(void* context, const char* path);
extern "C" void* fn_8014FF2C(void* anim);
extern "C" void fn_8014FFBC(void* anim, void* callback, f32* step);
extern "C" AnimSlot* fn_80150588(void* motion);
extern "C" void fn_80150958(void* slot);
extern "C" void* fn_80154414(s32 index);
extern "C" void fn_801543B4(void* handle);
extern "C" void fn_80194234(s32 id, s32 value);
extern "C" void fn_80194294(s32 id, s32* value);
extern "C" void fn_801A46D0(void* archive);
extern "C" void fn_801A4C84(void* texture);
extern "C" void fn_8019EB94(void* motion, Vec3* value, s32 index);
extern "C" void fn_8019ED68(void* motion, const f32* axis, f32 angle, s32 index);
extern "C" void fn_8020C2D8(void* motion);
extern "C" void fn_80239798(void);

extern "C" void fn_2_13D0(void);
extern "C" void fn_2_13D4(void);
extern "C" void fn_2_13D8(void);
extern "C" void fn_2_13DC(void);
extern "C" void fn_2_13E0(Emblem* emblem);
extern "C" void fn_2_13F4(void* memory);
extern "C" void* fn_2_1424(u32 size);
extern "C" void fn_2_1ED4(Task* task, void* callback);
extern "C" void fn_2_1EDC(Task* task, void* callback);
extern "C" void fn_2_1EE4(Task* task, void* callback);

extern "C" void fn_2_1454(Emblem* emblem);
extern "C" void fn_2_16C0(Emblem* emblem);
extern "C" void fn_2_173C(Emblem* emblem);
extern "C" void fn_2_1844(Emblem* emblem);
extern "C" Emblem* fn_2_1914(Emblem* emblem, s16 free);

#pragma dont_inline on

static const Vec3 lbl_2_rodata_48 = { 0.0f, -7.0f, 0.0f };

extern "C" s32 lbl_2_data_190         = 300;
extern "C" f32 lbl_2_data_194         = 2.0f;
extern "C" const char* lbl_2_data_1A4 = "TAS_EMBLEM";

extern "C" AnimDesc lbl_2_data_1B4
    = { NULL, 5, { 0, 0, 0, 0, 0, 0, 0, 0 }, -1.0f, 0.1f, 1.0f, "emblem.anm", 2, 0, 14 };

extern "C" AnimDesc lbl_2_data_1FC
    = { NULL, 3, { 0, 0, 0, 0, 0, 0, 0, 0 }, -1.0f, 0.1f, 1.0f, "emblem.anm", 5, 0, 14 };

extern "C" VtEntry lbl_2_data_244[11]
    = { NULL, NULL, (VtEntry)fn_2_1914, (VtEntry)fn_2_1844, (VtEntry)fn_2_173C, (VtEntry)fn_2_16C0,
	      fn_2_13D0, fn_2_13D4, fn_2_13D8, fn_80017854, fn_2_13DC };

extern "C" char lbl_2_data_270[] = "./advertise/sonic_e.prs";
extern "C" char lbl_2_data_288[] = "./advertise/as_emblem.one";

extern "C" void* lbl_2_bss_10;
extern "C" void* lbl_2_bss_14[2];
extern "C" void* lbl_2_bss_1C[2];
extern "C" u8* lbl_2_bss_24;
extern "C" s32 lbl_2_bss_28;
extern "C" u8 lbl_2_bss_2C[0x14];

extern "C" void fn_2_1454(Emblem* emblem)
{
	f32 width;
	f32 scale;
	f32 half;

	if (emblem->count >= 100) {
		emblem->digits[0] = '0' + (emblem->count / 100) % 10;
		emblem->digits[1] = '0' + (emblem->count / 10) % 10;
		emblem->digits[2] = '0' + emblem->count % 10;
		emblem->digits[3] = 0;
	} else if (emblem->count >= 10) {
		emblem->digits[0] = '0' + (emblem->count / 10) % 10;
		emblem->digits[1] = '0' + emblem->count % 10;
		emblem->digits[2] = 0;
	} else {
		emblem->digits[0] = '0' + emblem->count % 10;
		emblem->digits[1] = 0;
	}

	width = fn_8012EF3C(lbl_803E8150, emblem->digits);
	scale = lbl_2_data_194;
	half  = 0.5f;
	width = scale * width;

	emblem->x = lbl_8029BB80.width * half - width * half;
	emblem->y = 5.0f * lbl_8029BB80.height / 6.0f - 24.0f * scale * half;
}

extern "C" void fn_2_16C0(Emblem* emblem)
{
	fn_8012F728(lbl_803E8150);
	fn_8012F3D0(lbl_803E8150, emblem->digits);
	fn_8012F1F8(
	    lbl_803E8150, emblem->digits, emblem->x, emblem->y, lbl_2_data_194, lbl_2_data_194, 0);
	fn_8012F14C(lbl_803E8150);
}

extern "C" void fn_2_173C(Emblem* emblem)
{
	s32 state14;
	s32 state6;
	s32 state8;
	s32 stateA;
	s32 stateB;

	fn_80194294(20, &state14);
	fn_80194294(6, &state6);
	fn_80194294(8, &state8);
	fn_80194294(10, &stateA);
	fn_80194294(11, &stateB);

	fn_80194234(20, 2);
	fn_80194234(6, 1);
	fn_80194234(8, 1);
	fn_80194234(10, 5);
	fn_80194234(11, 6);

	if (emblem->anim[0] != NULL) {
		fn_8014FF2C(emblem->anim[0]);
	}
	fn_80194234(8, 0);
	if (emblem->anim[1] != NULL) {
		fn_8014FF2C(emblem->anim[1]);
	}

	fn_80194234(20, state14);
	fn_80194234(6, state6);
	fn_80194234(8, state8);
	fn_80194234(10, stateA);
	fn_80194234(11, stateB);
}

extern "C" void fn_2_1844(Emblem* emblem)
{
	if (lbl_2_data_190 < emblem->timer++) {
		fn_2_13E0(emblem);
	} else {
		f32 step;

		fn_800FE464(emblem->parts);
		if (emblem->anim[1] != NULL) {
			step = 0.00833335f;
			fn_8014FFBC(emblem->anim[1], (void*)fn_80239798, &step);
		}
		if (emblem->timer == 240) {
			emblem->count++;
			if (lbl_8042C388 != NULL) {
				fn_800B52E8(lbl_8042C388, 0xE016, 0, 0);
			}
		}
		fn_2_1454(emblem);
	}
}

extern "C" Emblem* fn_2_1914(Emblem* emblem, s16 free)
{
	s32 i;

	if (emblem != NULL) {
		emblem->vtable = lbl_2_data_244;
		for (i = 0; i != 2; i++) {
			fn_80150958(emblem->anim[i]);
		}
		fn_80130464(1);
		__destroy_arr(emblem->parts, (void*)dtor_800FE334, 0x4C, 2);
		__dt__7TObjectFv(emblem, 0);
		if (free > 0) {
			fn_2_13F4(emblem);
		}
	}
	return emblem;
}

extern "C" Emblem* fn_2_19D0(Emblem* emblem, void* arg)
{
	SaveState* state;

	__ct__7TObjectFP7TObject(emblem);
	emblem->vtable = lbl_2_data_244;
	__construct_array(emblem->parts, (void*)fn_800FE3FC, (void*)dtor_800FE334, 0x4C, 2);
	emblem->name  = lbl_2_data_1A4;
	emblem->unk1E = 0xE0;

	emblem->anim[0] = fn_80150588(lbl_2_bss_14[0]);
	if (emblem->anim[0] != NULL && emblem->anim[0]->motion != NULL) {
		fn_8019ED68(emblem->anim[0]->motion, lbl_80239984, 180.0f, 0);
	}

	emblem->anim[1] = fn_80150588(lbl_2_bss_14[1]);
	if (emblem->anim[1] != NULL) {
		void* motion = emblem->anim[1]->motion;

		if (motion != NULL) {
			Vec3 offset = lbl_2_rodata_48;

			fn_8019ED68(motion, lbl_80239978, -90.0f, 0);
			fn_8019EB94(motion, &offset, 2);
		}
	}

	fn_2_1EE4(emblem->parts, emblem->anim[0]);
	fn_2_1EDC(emblem->parts, &lbl_2_data_1B4);
	fn_2_1ED4(emblem->parts, NULL);
	fn_800FE464(emblem->parts);

	emblem->timer = 0;
	state         = fn_80116D2C(lbl_803E774C);
	emblem->count = state->emblems - 1;
	if (emblem->count < 0) {
		emblem->count = 0;
	}
	fn_2_1454(emblem);
	return emblem;
}

extern "C" void fn_2_1B7C(void* arg)
{
	if (arg != NULL) {
		if (lbl_2_bss_28 != 0) {
			Emblem* emblem = (Emblem*)fn_2_1424(0xE0);

			if (emblem != NULL) {
				fn_2_19D0(emblem, arg);
			}
		} else {
			fn_80130464(1);
		}
	}
}

extern "C" void fn_2_1BE4(void)
{
	s32 i;

	if (lbl_2_bss_28 != 0) {
		if (lbl_2_bss_24 != NULL) {
			fn_801543B4(lbl_2_bss_24);
			lbl_2_bss_24 = NULL;
		}
		for (i = 0; i != 2; i++) {
			if (lbl_2_bss_1C[i] != NULL) {
				fn_8020C2D8(lbl_2_bss_1C[i]);
				lbl_2_bss_1C[i] = NULL;
			}
			if (lbl_2_bss_14[i] != NULL) {
				fn_80150958(lbl_2_bss_14[i]);
				lbl_2_bss_14[i] = NULL;
			}
		}
		if (lbl_2_bss_10 != NULL) {
			fn_801A46D0(lbl_2_bss_10);
			lbl_2_bss_10 = NULL;
		}
		fn_8012FF6C(lbl_803E8150);
	}
}

#pragma opt_common_subs off

extern "C" void fn_2_1CE4(void)
{
	s32 selected;
	void* archive;

	selected    = fn_800A8BF8(lbl_80303EC8);
	s32 emblems = fn_80116D2C(lbl_803E774C)->emblems;
	if (emblems != selected) {
		lbl_2_bss_28 = 1;
	} else {
		lbl_2_bss_28 = 0;
	}
	if (lbl_2_bss_28 == 0) {
		return;
	}

	fn_801301C8(lbl_803E8150);
	fn_8012FFD4(lbl_803E8150, lbl_2_data_270);

	archive = fn_80057644(0x58);
	if (archive != NULL) {
		archive = fn_800BCC84(archive, lbl_2_data_288, 0);
	}
	if (archive != NULL) {
		void* heap = ((void* (*)(s32))lbl_8042C9A4[0x134 / 4])(0x7D000);

		if (heap != NULL) {
			lbl_2_bss_10 = fn_800BC580(archive, 4, heap);
			if (lbl_2_bss_10 != NULL) {
				fn_801A4C84(lbl_2_bss_10);
				lbl_2_bss_14[0]       = fn_800BC46C(archive, 3, heap);
				lbl_2_bss_1C[0]       = fn_800BBF20(archive, 2, heap);
				lbl_2_bss_14[1]       = fn_800BC46C(archive, 6, heap);
				lbl_2_bss_1C[1]       = fn_800BBF20(archive, 5, heap);
				lbl_2_data_1B4.target = lbl_2_bss_1C[0];
				lbl_2_data_1FC.target = lbl_2_bss_1C[1];
			}
			((void (*)(void*))lbl_8042C9A4[0x138 / 4])(heap);
		}
		fn_800BCBD4(archive, 1);
	}

	lbl_2_bss_24 = (u8*)fn_80154414(2);
	if (lbl_2_bss_24 != NULL) {
		lbl_2_bss_24[2] = 1;
	}
}
