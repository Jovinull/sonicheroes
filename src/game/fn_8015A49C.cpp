// Tears down the plugin data of object (at the offset lbl_8042C918): frees its buffer with the
// engine memory function, clears its first three words and restores the object's callbacks at
// +0x18, +0x1C and +0x10 from the copies saved at +0x10, +0x14 and +0x18 of the plugin data.
// Plugin and field names are UNKNOWN. Returns the object.
#include "game/rw_engine.h"

struct Ext8015A49C {
	void* buffer; // 0x0
	s32 f4;
	s32 f8;
	s32 fC;
	void* saved10; // 0x10
	void* saved14; // 0x14
	void* saved18; // 0x18
};

struct Object8015A49C {
	u8 pad0[0x10];
	void* f10; // 0x10
	u8 pad14[0x18 - 0x14];
	void* f18; // 0x18
	void* f1C; // 0x1C
};

extern "C" {
extern s32 lbl_8042C918;

Object8015A49C* fn_8015A49C(Object8015A49C* object)
{
	Ext8015A49C* ext = (Ext8015A49C*)((u8*)object + lbl_8042C918);
	if (ext->buffer != 0) {
		lbl_8042C9A4->rwfree(ext->buffer);
	}
	ext->buffer = 0;
	ext->f4     = 0;
	ext->f8     = 0;
	object->f18 = ext->saved10;
	object->f1C = ext->saved14;
	object->f10 = ext->saved18;
	return object;
}
}
