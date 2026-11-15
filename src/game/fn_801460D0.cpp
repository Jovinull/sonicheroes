// Copy callback of a plugin whose data is a reference table (HYPOTHESIS): when the source carries
// data, creates a table for the same definition (0x38-byte header plus the definition's extra size
// at 0xC, which the header points at when present; an allocation failure records error 0x80000013
// for plugin 0x120) and copies each slot's reference (fn_80146990/fn_80146920) and byte
// (fn_801469AC/fn_801469A0) and the shared object at 0x30 (fn_80146918/fn_801468BC). Returns the
// destination, or null when the table cannot be created. Field names are inferred.
// NonMatching: the definition, count and size rotate through r26-r28 differently (10 words).
#include "game/rw_engine.h"
#include "MSL_C/string.h"

struct Definition801460D0 {
	u8 pad0[0xC];
	u32 extraSize; // 0xC
};

struct Table801460D0 {
	Definition801460D0* definition; // 0x0
	u32 count;                      // 0x4
	u8 pad8[0x34 - 0x8];
	void* extra; // 0x34: points at 0x38 when the definition has extra data
};

extern "C" {
void* fn_80146990(Table801460D0* table, u32 index);
Table801460D0* fn_80146920(Table801460D0* table, u32 index, void* reference);
u8 fn_801469AC(Table801460D0* table, u32 index);
Table801460D0* fn_801469A0(Table801460D0* table, u32 index, u8 value);
void* fn_80146918(Table801460D0* table);
Table801460D0* fn_801468BC(Table801460D0* table, void* object);
}

static inline Table801460D0* TableCreate(Definition801460D0* definition, u32 count)
{
	u32 size             = definition->extraSize + 0x38;
	Table801460D0* table = (Table801460D0*)lbl_8042C9A4->rwmalloc(size);

	if (!table) {
		RwError error;
		error.pluginID  = 0x120;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
		fn_80193FE8(&error);
		return 0;
	}
	memset(table, 0, size);
	table->definition = definition;
	table->count      = count;
	if (definition->extraSize) {
		table->extra = (u8*)table + 0x38;
	}
	return table;
}

extern "C" {
void* fn_801460D0(void* dst, const void* src, s32 offset)
{
	Table801460D0* copy;
	u32 i;
	Table801460D0* source;

	source = *(Table801460D0**)((const u8*)src + offset);

	if (!source) {
		return dst;
	}
	copy = TableCreate(source->definition, source->count);
	if (!copy) {
		return 0;
	}
	*(Table801460D0**)((u8*)dst + offset) = copy;
	for (i = 0; i < source->count; i++) {
		fn_80146920(copy, i, fn_80146990(source, i));
		fn_801469A0(copy, i, fn_801469AC(source, i));
	}
	fn_801468BC(copy, fn_80146918(source));
	return dst;
}
}
