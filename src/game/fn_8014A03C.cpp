// Copy callback of the 0x105 geometry plugin (registered by fn_8014A90C through fn_80152FDC,
// HYPOTHESIS: RpGeometryRegisterPlugin; constructor fn_8014A37C): duplicates the source's
// array of 0x14-byte entries into a new engine heap block for the destination. Returns the
// destination, or null when the allocation fails.
#include "game/geometry_plugin_105.h"
#include "game/rw_engine.h"
#include "MSL_C/string.h"

extern "C" {
void* fn_8014A03C(void* dst, const void* src, s32, s32)
{
	GeometryPlugin105Data* copy = GEOMETRY_PLUGIN_105_DATA(dst);
	const GeometryPlugin105Data* source
	    = (const GeometryPlugin105Data*)((const u8*)src + lbl_8042C86C);

	if (source->count > 0) {
		s32 size      = source->count * 0x14;
		copy->entries = (GeometryPlugin105Entry*)lbl_8042C9A4->rwmalloc(size);
		if (!copy->entries) {
			return 0;
		}
		copy->count = source->count;
		memcpy(copy->entries, source->entries, size);
	}
	return dst;
}
}
