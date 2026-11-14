// Calls callback(entry, data) for each entry of the pointer array kept in the plugin data of object
// (at the offset lbl_8042C918: array at +0x0, count at +0x8), stopping early when it returns null.
// Plugin and field names are UNKNOWN. Returns the object.
#include "game/rw_engine.h"

struct Ext8015BCF4 {
	void** entries; // 0x0
	s32 f4;
	s32 count; // 0x8
};

typedef void* (*Callback8015BCF4)(void* entry, void* data);

extern "C" {
extern s32 lbl_8042C918;

void* fn_8015BCF4(void* object, Callback8015BCF4 callback, void* data)
{
	Ext8015BCF4* ext = (Ext8015BCF4*)((u8*)object + lbl_8042C918);
	void** entry     = ext->entries;
	s32 count        = ext->count;
	while (count != 0) {
		if (callback(*entry, data) == 0) {
			return object;
		}
		entry++;
		count--;
	}
	return object;
}
}
