// Stream write callback of the reference-table plugin of fn_801460D0 (HYPOTHESIS): writes the
// library version (fn_8019D3D0) as a 32-bit value, a 4-byte header (definition id, slot count,
// whether a shared object is attached, 0), the slot bytes at 0x28 and each slot's reference
// (fn_80147DFC; its result is not checked), then the shared object's name (fn_8019A5C8, at 0x8 of
// the object at 0x30). Returns the stream, or null when a write fails. Field names are inferred.
#include "types.h"

struct Definition801462B4 {
	s32 id; // 0x0
};

struct Table801462B4 {
	Definition801462B4* definition; // 0x0
	u32 count;                      // 0x4
	void* references[8];            // 0x8
	u8 bytes[8];                    // 0x28
	void* object;                   // 0x30
};

struct Header801462B4 {
	u8 id;
	u8 count;
	u8 hasObject;
	u8 pad;
};

extern "C" {
u32 fn_8019D3D0(void);
void* fn_80193474(void* stream, void* values, s32 size);
void* fn_80197B48(void* stream, const void* data, s32 size);
void* fn_80147DFC(void* stream, void* reference);
void* fn_8019A5C8(const char* string, void* stream);

void* fn_801462B4(void* stream, s32, const void* object, s32 offset)
{
	Table801462B4* table = *(Table801462B4**)((const u8*)object + offset);
	u32 version;
	Header801462B4 header;

	if (table) {
		version = fn_8019D3D0();
		if (!fn_80193474(stream, &version, sizeof(version))) {
			return 0;
		}
		header.id        = table->definition->id;
		header.count     = table->count;
		header.hasObject = table->object != 0;
		header.pad       = 0;
		if (!fn_80197B48(stream, &header, sizeof(header))) {
			return 0;
		}
		if (table->count) {
			u32 i;
			if (!fn_80197B48(stream, table->bytes, table->count)) {
				return 0;
			}
			for (i = 0; i < table->count; i++) {
				fn_80147DFC(stream, table->references[i]);
			}
		}
		if (table->object) {
			if (!fn_8019A5C8((const char*)table->object + 8, stream)) {
				return 0;
			}
		}
	}
	return stream;
}
}
