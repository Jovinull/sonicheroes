// Clears the plugin data of target (at the offset lbl_8042C918) when it has an owner (+0xC set): frees
// its buffer with the engine memory function and zeroes its first four words. Returns result, or
// null when the plugin data was not in use. Plugin and field names are UNKNOWN.
#include "game/rw_engine.h"

struct Ext8015B93C {
	void* buffer; // 0x0
	s32 f4;
	s32 f8;
	void* owner; // 0xC
};

extern "C" {
extern s32 lbl_8042C918;

void* fn_8015B93C(void* result, void* target)
{
	Ext8015B93C* ext = (Ext8015B93C*)((u8*)target + lbl_8042C918);
	if (ext->owner != 0) {
		if (ext->buffer != 0) {
			lbl_8042C9A4->rwfree(ext->buffer);
		}
		ext->buffer = 0;
		ext->f4     = 0;
		ext->f8     = 0;
		ext->owner  = 0;
		return result;
	}
	return 0;
}
}
