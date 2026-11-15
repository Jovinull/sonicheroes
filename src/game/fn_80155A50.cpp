// Appends a 0x14-byte record to a growable array (HYPOTHESIS: a world-builder triangle list):
// when full, the array grows by one entry (engine realloc, or malloc for the first), raising
// error 0x80000013 of plugin 2 and returning null when that fails. The new record stores the word
// and the seven halfwords. Returns the array. Names are inferred from this function only.
#include "game/rw_engine.h"

struct Record80155A50 {
	u16 a0; // 0x0
	u16 a1; // 0x2
	u16 a2; // 0x4
	u8 pad6[0x2];
	s32 value; // 0x8
	u16 b0;    // 0xC
	u16 b1;    // 0xE
	u16 b2;    // 0x10
	u16 b3;    // 0x12
};

struct RecordArray80155A50 {
	u32 max;                 // 0x0
	u32 count;               // 0x4
	Record80155A50* records; // 0x8
};

#define PLUGIN_ID_80155A50 2

extern "C" {
RecordArray80155A50* fn_80155A50(
    RecordArray80155A50* array, s32 value, u16 a0, u16 a1, u16 a2, u16 b0, u16 b1, u16 b2, u16 b3)
{
	if (array->count >= array->max) {
		u32 size = (array->count + 1) * sizeof(Record80155A50);
		Record80155A50* records;
		if (array->count != 0) {
			records = (Record80155A50*)lbl_8042C9A4->rwrealloc(array->records, size);
		} else {
			records = (Record80155A50*)lbl_8042C9A4->rwmalloc(size);
		}
		if (records == 0) {
			RwError error;
			error.pluginID  = PLUGIN_ID_80155A50;
			error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
			fn_80193FE8(&error);
			return 0;
		}
		array->records = records;
		array->max     = array->count + 1;
	}
	array->records[array->count].value = value;
	array->records[array->count].a0    = a0;
	array->records[array->count].a1    = a1;
	array->records[array->count].a2    = a2;
	array->records[array->count].b0    = b0;
	array->records[array->count].b1    = b1;
	array->records[array->count].b2    = b2;
	array->records[array->count].b3    = b3;
	array->count++;
	return array;
}
}
