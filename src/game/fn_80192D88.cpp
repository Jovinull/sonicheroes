// Reads a chunk header (HYPOTHESIS: _rwStreamReadChunkHeader): reads the 12-byte header, converts
// it to native byte order, unpacks the library ID into the version and build number, records the
// header in lbl_80290400 together with its "complex chunk" flag (fn_80192CCC) and copies the
// requested fields out. A short read raises error 0x8000001A (read error) of plugin 1. Returns 1,
// or 0 on a short read.
#include "game/rw_engine.h"

// Last chunk header read (HYPOTHESIS: RwChunkHeaderInfo).
struct RwChunkHeaderInfo80192D88 {
	u32 type;      // 0x0
	u32 length;    // 0x4
	u32 version;   // 0x8
	u32 buildNum;  // 0xC
	s32 isComplex; // 0x10
};

// Raw chunk header as stored in the stream.
struct RwChunkMark80192D88 {
	u32 type;
	u32 length;
	u32 libraryID;
};

#define RW_ERROR_READ_80192D88 ((s32)0x8000001A)

extern "C" {
extern RwChunkHeaderInfo80192D88 lbl_80290400;
// HYPOTHESIS: RwStreamRead, RwMemNative32 and _rwStreamChunkIsComplex.
u32 fn_801979AC(void* stream, void* buffer, u32 length);
void* fn_80193270(void* mem, u32 size);
s32 fn_80192CCC(RwChunkHeaderInfo80192D88* info);

s32 fn_80192D88(void* stream, u32* type, u32* length, u32* version, u32* buildNum)
{
	RwChunkMark80192D88 mark;
	s32 ok = (fn_801979AC(stream, &mark, sizeof(mark)) == sizeof(mark)) ? 1 : 0;
	if (!ok) {
		RwError error;
		error.pluginID  = 1;
		error.errorCode = fn_8019408C(RW_ERROR_READ_80192D88);
		fn_80193FE8(&error);
		return 0;
	}
	fn_80193270(&mark, sizeof(mark));

	lbl_80290400.type   = mark.type;
	lbl_80290400.length = mark.length;
	if ((mark.libraryID & 0xFFFF0000) == 0) {
		lbl_80290400.version  = mark.libraryID << 8;
		lbl_80290400.buildNum = 0;
	} else {
		lbl_80290400.version
		    = (((mark.libraryID >> 14) & 0x3FF00) + 0x30000) | ((mark.libraryID >> 16) & 0x3F);
		lbl_80290400.buildNum = mark.libraryID & 0xFFFF;
	}
	lbl_80290400.isComplex = fn_80192CCC(&lbl_80290400);

	if (type != 0) {
		*type = lbl_80290400.type;
	}
	if (length != 0) {
		*length = lbl_80290400.length;
	}
	if (buildNum != 0) {
		*buildNum = lbl_80290400.buildNum;
	}
	if (version != 0) {
		*version = lbl_80290400.version;
	}
	return 1;
}
}
