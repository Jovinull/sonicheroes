// Finds one of eight records whose pointer field is nonzero.
#include "types.h"

struct Fn80020370Entry {
	u32 unk00;
	void* unk04;
};

struct Fn80020370Object {
	u8 pad00[0x14];
	Fn80020370Entry entries[8];
};

extern "C" Fn80020370Entry* fn_80020370(Fn80020370Object* object, s32 index)
{
	if (index < 0) {
		return NULL;
	}
	if (index > 7) {
		return NULL;
	}
	Fn80020370Entry* entry = &object->entries[index];
	if (entry->unk04 != NULL) {
		return entry;
	}
	return NULL;
}
