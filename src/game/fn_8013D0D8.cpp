// Clears the plugin data of object (at the offset lbl_8042C820): frees its two buffers (+0x0 and
// +0x4) with the engine memory function and zeroes them and the word at +0x8. Plugin and field names
// are UNKNOWN. Returns the object.
#include "game/rw_engine.h"

struct Ext8013D0D8 {
	void* buffer0; // 0x0
	void* buffer1; // 0x4
	s32 f8;        // 0x8
};

extern "C" {
extern s32 lbl_8042C820;

void* fn_8013D0D8(void* object)
{
	Ext8013D0D8* ext = (Ext8013D0D8*)((u8*)object + lbl_8042C820);
	if (ext->buffer0 != 0) {
		lbl_8042C9A4->rwfree(ext->buffer0);
		ext->buffer0 = 0;
	}
	if (ext->buffer1 != 0) {
		lbl_8042C9A4->rwfree(ext->buffer1);
		ext->buffer1 = 0;
	}
	ext->f8 = 0;
	return object;
}
}
