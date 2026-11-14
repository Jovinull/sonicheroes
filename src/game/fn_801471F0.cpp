// Allocates a cleared 0x30-byte record with the engine memory function, with +0x4 set to 1. On
// failure records error 0x80000013 (out of memory, 0x30 bytes) for plugin 0x120 and returns null.
// Names are UNKNOWN.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define PLUGIN_ID_801471F0 0x120

struct Record801471F0 {
	s32 f0;
	s32 f4;
	u8 pad8[0x28 - 0x8];
	void* f28;
	void* f2C;
};

extern "C" {
Record801471F0* fn_801471F0(void)
{
	Record801471F0* record = (Record801471F0*)lbl_8042C9A4->rwmalloc(sizeof(Record801471F0));
	if (record == 0) {
		RwError error;
		error.pluginID  = PLUGIN_ID_801471F0;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, sizeof(Record801471F0));
		fn_80193FE8(&error);
		return 0;
	}
	memset(record, 0, sizeof(Record801471F0));
	record->f0  = 0;
	record->f4  = 1;
	record->f2C = 0;
	record->f28 = 0;
	return record;
}
}
