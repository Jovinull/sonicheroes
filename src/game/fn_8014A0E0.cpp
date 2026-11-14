// Stream write callback of the 0x105 geometry plugin (HYPOTHESIS; see fn_8014A03C): writes the
// entry count (fn_80193474, HYPOTHESIS: RwStreamWriteInt32), then each 0x14-byte entry with its
// halfwords widened and its link pointer at 0x10 stored as an entry index, converted by
// fn_80193174 (HYPOTHESIS: RwMemLittleEndian32) and written with fn_80197B48 (HYPOTHESIS:
// RwStreamWrite). Returns the stream, or null when a write fails.
#include "types.h"

struct Entry8014A0E0 {
	u32 id;              // 0x0
	s16 a;               // 0x4
	s16 b;               // 0x6
	f32 value;           // 0x8
	u8 padC[0x4];        // 0xC
	Entry8014A0E0* link; // 0x10
};

// Stream form of an entry.
struct StreamEntry8014A0E0 {
	u32 id;
	s32 a;
	s32 b;
	f32 value;
	s32 linkIndex;
};

struct PluginData8014A0E0 {
	s32 count;              // 0x0
	void* callback;         // 0x4
	Entry8014A0E0* entries; // 0x8
};

extern "C" {
extern s32 lbl_8042C86C;

void* fn_80193474(void* stream, s32* values, s32 size);
void* fn_80193174(void* data, s32 size);
void* fn_80197B48(void* stream, const void* data, s32 size);

void* fn_8014A0E0(void* stream, s32, const void* object)
{
	PluginData8014A0E0* data = (PluginData8014A0E0*)((const u8*)object + lbl_8042C86C);
	s32 count                = data->count;
	s32 i;

	if (!fn_80193474(stream, &count, sizeof(count))) {
		return 0;
	}
	for (i = 0; i < count; i++) {
		StreamEntry8014A0E0 out;
		out.id        = data->entries[i].id;
		out.a         = data->entries[i].a;
		out.b         = data->entries[i].b;
		out.value     = data->entries[i].value;
		out.linkIndex = data->entries[i].link - data->entries;
		fn_80193174(&out, sizeof(out));
		if (!fn_80197B48(stream, &out, sizeof(out))) {
			return 0;
		}
	}
	return stream;
}
}
