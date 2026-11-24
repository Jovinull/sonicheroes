#include "types.h"

// Returns the reference stored at slot `index` of the table (+8 + index * 4); the getter that
// pairs with the setter fn_80146920. The table's type is UNKNOWN.

struct Table80146990 {
	u8 pad0[0x8];
	void* entries[1]; // 0x08
};

extern "C" void* fn_80146990(Table80146990* table, s32 index)
{
	return table->entries[index];
}
