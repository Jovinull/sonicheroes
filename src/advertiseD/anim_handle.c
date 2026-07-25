#include "types.h"

// Four small entry points over one animation handle: stop it, start it at a
// given value, advance it, and push its value back out.
//
// The translation unit runs from fn_1_88C4 at 0x88C4 to the end of fn_1_8948
// at 0x897C, and owns .rodata 0xF38 to 0xF40. Those eight bytes are not
// written here: they are the constant the compiler emits for itself to turn a
// signed int into a float, which only fn_1_88D0 needs. It is the third of the
// three cuts available out of 0x88C4 where no private data crosses, and the
// last one before the run starts sharing lbl_1_data_3740 with what follows.
//
// fn_1_890C and fn_1_8948 are two of the three entries of the table at
// .data 0x3740; the third is fn_1_897C, which is why the unit stops there.
//
// Only the shape of the object is read from the code, so the field names say
// what the code does with them and nothing more.

typedef struct Anim {
	u8 unk0[0x28]; // 0x00
	void* handle;  // 0x28
	f32 value;     // 0x2C
	u8 unk30[0x4]; // 0x30
	s32 running;   // 0x34
} Anim;

extern void fn_8012CC20(void* handle);
extern void fn_8012CEF0(void* handle, f32 value);

void fn_1_88C4(Anim* anim)
{
	anim->running = 0;
}

void fn_1_88D0(Anim* anim, s32 value)
{
	anim->running = 1;
	anim->value   = value;
}

void fn_1_890C(Anim* anim)
{
	void* handle = anim->handle;

	if (handle != NULL && anim->running != 0) {
		fn_8012CC20(handle);
	}
}

void fn_1_8948(Anim* anim)
{
	if (anim->handle != NULL) {
		fn_8012CEF0(anim->handle, anim->value);
	}
}
