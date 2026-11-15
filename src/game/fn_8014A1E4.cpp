// Stream read callback of the 0x105 geometry plugin (HYPOTHESIS; counterpart of fn_8014A0E0):
// reads the entry count (fn_80193884, HYPOTHESIS: RwStreamReadInt32), creates the entry array
// (fn_8014A3A0) and reads each 0x14-byte entry in stream form, converting it from little-endian
// (fn_80193270) and rebuilding the halfwords, the inverse of the value (with the .sdata2 constant
// lbl_8042F2B4, HYPOTHESIS 1.0f) and the link from its index. Returns the stream, or null on a
// short read or allocation failure.
#include "game/geometry_plugin_105.h"

// Stream form of an entry.
struct StreamEntry8014A1E4 {
	u32 id;
	s32 a;
	s32 b;
	f32 value;
	s32 linkIndex;
};

extern "C" {
extern f32 lbl_8042F2B4;

void* fn_80193884(void* stream, s32* values, s32 size);
void* fn_8014A3A0(void* geometry, s32 count);
u32 fn_801979AC(void* stream, void* buffer, u32 length);
void* fn_80193270(void* mem, u32 size);

void* fn_8014A1E4(void* stream, s32, void* geometry)
{
	GeometryPlugin105Data* data = GEOMETRY_PLUGIN_105_DATA(geometry);
	s32 count;

	if (!fn_80193884(stream, &count, sizeof(count))) {
		return 0;
	}
	if (count > 0) {
		s32 i;
		if (!fn_8014A3A0(geometry, count)) {
			return 0;
		}
		for (i = 0; i < count; i++) {
			StreamEntry8014A1E4 in;
			if (fn_801979AC(stream, &in, sizeof(in)) != sizeof(in)) {
				return 0;
			}
			fn_80193270(&in, sizeof(in));
			data->entries[i].id           = in.id;
			data->entries[i].a            = in.a;
			data->entries[i].b            = in.b;
			data->entries[i].value        = in.value;
			data->entries[i].inverseValue = lbl_8042F2B4 / in.value;
			data->entries[i].link         = &data->entries[in.linkIndex];
		}
	}
	return stream;
}
}
