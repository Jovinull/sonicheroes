// Reference-counted records of a module registered under plugin ID 0x120 (HYPOTHESIS; names
// inferred). These functions share one unit because fn_80147288 and fn_80147178 call each other
// and the compiler inlines that recursion several levels deep, which needs both definitions here.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

#define PLUGIN_ID_80147178 0x120

struct Record80147178 {
	s32 type;     // 0x0: index into the type table lbl_803EC488 (0: none)
	u32 refCount; // 0x4
	u8 pad8[0x28 - 0x8];
	RwLLLink link; // 0x28: null next when the record is not linked
};

// Per-type entry of lbl_803EC488 (0x14 bytes; only the destroy callback is known).
struct RecordType80147178 {
	u8 pad0[0x4];
	void (*destroy)(Record80147178* record); // 0x4
	u8 pad8[0x14 - 0x8];
};

extern "C" {
extern RecordType80147178 lbl_803EC488[];
// Offset of the module globals inside the engine instance (HYPOTHESIS).
extern s32 lbl_8042BCE0;

void fn_80147288(Record80147178* record);

#define MODULE_80147178_VALUE (*(s32*)((u8*)lbl_8042C9A4 + lbl_8042BCE0 + 8))

// Type entry of a record, addressed by byte offset as retail does.
#define RECORD_TYPE_80147178(type)                                                                 \
	((RecordType80147178*)((u8*)lbl_803EC488 + (type) * sizeof(RecordType80147178)))

// Unlinks a record from its list when it is linked, then releases the list's reference
// (fn_80147288). Returns the record.
Record80147178* fn_80147178(Record80147178* record)
{
	if (record->link.next != 0) {
		RW_LL_LINK_REMOVE(&record->link);
		fn_80147288(record);
	}
	return record;
}

// Stores the module value at offset 8 of the module globals.
void fn_801471C8(s32 value)
{
	MODULE_80147178_VALUE = value;
}

// Returns the module value at offset 8 of the module globals.
s32 fn_801471DC(void)
{
	return MODULE_80147178_VALUE;
}

// Allocates a cleared 0x30-byte record with the engine memory function, with one reference. On
// failure records error 0x80000013 (out of memory, 0x30 bytes) for plugin 0x120 and returns null.
Record80147178* fn_801471F0(void)
{
	Record80147178* record = (Record80147178*)lbl_8042C9A4->rwmalloc(0x30);
	if (record == 0) {
		RwError error;
		error.pluginID  = PLUGIN_ID_80147178;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, 0x30);
		fn_80193FE8(&error);
		return 0;
	}
	memset(record, 0, 0x30);
	record->type      = 0;
	record->refCount  = 1;
	record->link.prev = 0;
	record->link.next = 0;
	return record;
}

// Releases one reference to a record; the last one unlinks it (fn_80147178) and destroys it with
// its type's destroy callback, or frees it with the engine memory function.
void fn_80147288(Record80147178* record)
{
	record->refCount--;
	if (record->refCount == 0) {
		fn_80147178(record);
		if (record->type != 0 && RECORD_TYPE_80147178(record->type)->destroy != 0) {
			RECORD_TYPE_80147178(record->type)->destroy(record);
		} else {
			lbl_8042C9A4->rwfree(record);
		}
	}
}
}
