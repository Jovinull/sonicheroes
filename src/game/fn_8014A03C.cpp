// Copy callback of the 0x105 geometry plugin (registered by fn_8014A90C through fn_80152FDC,
// HYPOTHESIS: RpGeometryRegisterPlugin; constructor fn_8014A37C): duplicates the source's
// array of 0x14-byte entries into a new engine heap block for the destination. Returns the
// destination, or null when the allocation fails.
#include "game/rw_engine.h"
#include "MSL_C/string.h"

// Plugin data inside a geometry (layout from the constructor fn_8014A37C).
struct PluginData8014A03C {
	s32 count;      // 0x0
	void* callback; // 0x4
	void* entries;  // 0x8: count entries of 0x14 bytes
};

extern "C" {
// Offset of the plugin data inside a geometry.
extern s32 lbl_8042C86C;

void* fn_8014A03C(void* dst, const void* src, s32, s32)
{
	PluginData8014A03C* copy         = (PluginData8014A03C*)((u8*)dst + lbl_8042C86C);
	const PluginData8014A03C* source = (const PluginData8014A03C*)((const u8*)src + lbl_8042C86C);

	if (source->count > 0) {
		s32 size      = source->count * 0x14;
		copy->entries = lbl_8042C9A4->rwmalloc(size);
		if (!copy->entries) {
			return 0;
		}
		copy->count = source->count;
		memcpy(copy->entries, source->entries, size);
	}
	return dst;
}
}
