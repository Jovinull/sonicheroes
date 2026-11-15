// Reads an object of a registered type from a stream (HYPOTHESIS): finds the struct chunk (type 1,
// fn_80192F38, HYPOTHESIS: RwStreamFindChunk), reads the little-endian type index (fn_801979AC,
// fn_80193270), reads the object's name (fn_8019A688, HYPOTHESIS: a string-chunk reader), finds
// the extension chunk (type 3) and lets the type's read callback (word 0x8 of its 0x14-byte entry
// in lbl_803EC488, registered by fn_80146C2C) build the object from the chunk's version and length,
// then names it (fn_801478CC). Returns the object, or null when any step fails.
#include "types.h"

typedef void* (*ReadCallBack80147528)(void* stream, s32 type, u32 version, u32 length);

struct TypeEntry80147528 {
	s32 type;                  // 0x0
	s32 word4;                 // 0x4
	ReadCallBack80147528 read; // 0x8
	s32 wordC;                 // 0xC
	s32 word10;                // 0x10
};

extern "C" {
extern TypeEntry80147528 lbl_803EC488[];

s32 fn_80192F38(void* stream, u32 type, u32* length, u32* version);
u32 fn_801979AC(void* stream, void* buffer, u32 length);
void* fn_80193270(void* mem, u32 size);
char* fn_8019A688(char* name, void* stream);
void* fn_801478CC(void* object, const char* name);

void* fn_80147528(void* stream)
{
	s32 type;
	u32 version;
	u32 length;
	char name[32];
	TypeEntry80147528* entry;
	void* object;

	if (!fn_80192F38(stream, 1, 0, 0) || !fn_801979AC(stream, &type, sizeof(type))) {
		return 0;
	}
	fn_80193270(&type, sizeof(type));
	entry = &lbl_803EC488[type];
	if (!entry->read) {
		return 0;
	}
	if (!fn_8019A688(name, stream)) {
		return 0;
	}
	if (!fn_80192F38(stream, 3, &length, &version)) {
		return 0;
	}
	object = entry->read(stream, type, version, length);
	if (!object) {
		return 0;
	}
	fn_801478CC(object, name);
	return object;
}
}
