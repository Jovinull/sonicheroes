#ifndef GAME_RW_STREAM_CHUNK_H
#define GAME_RW_STREAM_CHUNK_H

#include "game/rw_engine.h"

// Stream chunk headers as read by fn_80192D88 and fn_80192F38 and written by fn_80192ED8.
// On the stream a header is three words: type, size, and a packed version/build word.
// Struct, field and helper names are HYPOTHESIS (inferred from the GameCube accesses);
// symbols stay fn_ addresses.

struct RwStream;

// Last header read (lbl_80290400, 0x14 bytes, defined in game/fn_80192CCC.cpp).
struct ChunkHdr {
	u32 type;
	u32 size;
	u32 version; // unpacked library version, e.g. 0x33000
	u32 build;   // build number, 0 for headers with an old-style version word
	s32 unk10;   // fn_80192CCC(type): 1 for some chunk types; meaning UNKNOWN
};

extern "C" {
extern ChunkHdr lbl_80290400;

// Returns 1 for chunk types 5-11, 14-16, 18, 20 and 26, otherwise 0.
s32 fn_80192CCC(ChunkHdr* hdr);
// Reads a chunk header into lbl_80290400 and copies the requested fields out; 0 on a short read.
s32 fn_80192D88(RwStream* stream, u32* type, u32* size, u32* version, u32* build);
// Byte-swaps `size` bytes in place, one word at a time; returns the buffer (matched unit).
void* fn_80193270(void* mem, unsigned int size);
// Reads `length` bytes from the stream; returns the number read.
u32 fn_801979AC(RwStream* stream, void* buffer, u32 length);
// Skips `length` bytes of the stream; 0 on failure.
u32 fn_80197D70(RwStream* stream, u32 length);
}

// Error code for a short header read (top bit set: no plugin ID, see RW_ERROR_NONE).
#define CHUNK_ERROR_READ ((s32)0x8000001A)
// Error code for a chunk version outside the supported range.
#define CHUNK_ERROR_VERSION ((s32)0x80000004)

// The body of fn_80192D88. fn_80192F38 contains it fully inlined, so the original file probably
// defined both (HYPOTHESIS); here it is shared through this helper instead.
static inline s32 ChunkHdrRead(RwStream* stream, u32* type, u32* size, u32* version, u32* build)
{
	u32 raw[3];
	s32 ok;

	ok = (fn_801979AC(stream, raw, 0xC) == 0xC) ? 1 : 0;
	if (!ok) {
		RwError error;
		error.pluginID  = RW_ID_CORE_PLUGIN;
		error.errorCode = fn_8019408C(CHUNK_ERROR_READ);
		fn_80193FE8(&error);
		return 0;
	}
	fn_80193270(raw, 0xC);
	lbl_80290400.type = raw[0];
	lbl_80290400.size = raw[1];
	if ((raw[2] & 0xFFFF0000) == 0) {
		lbl_80290400.version = raw[2] << 8;
		lbl_80290400.build   = 0;
	} else {
		lbl_80290400.version = (((raw[2] >> 14) & 0x3FF00) + 0x30000) | ((raw[2] >> 16) & 0x3F);
		lbl_80290400.build   = raw[2] & 0xFFFF;
	}
	lbl_80290400.unk10 = fn_80192CCC(&lbl_80290400);
	if (type != NULL)
		*type = lbl_80290400.type;
	if (size != NULL)
		*size = lbl_80290400.size;
	if (build != NULL)
		*build = lbl_80290400.build;
	if (version != NULL)
		*version = lbl_80290400.version;
	return 1;
}

#endif
