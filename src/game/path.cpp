#include "types.h"

// Reconstruction fragment for fn_80012EA0, whose exact code range ends at
// 0x80012FC8. Its extab/extabindex entries prove the function range, not an
// original translation-unit boundary.
//
// This is the GameCube counterpart of the RenderWare platform pathname-create
// callback. The PS2 counterpart retains C linkage inside a C++-compiled
// platform unit, so this fragment uses C++ with an explicit C ABI.

typedef struct ObjectDispatch {
	void* (*allocate)(u32);
	void (*destroy)(void*);
} ObjectDispatch;

typedef struct StringFunctions {
	u8 unk0[0xF8];
	void (*copy)(s8*, const s8*);
	u8 unkFC[0x10];
	s8* (*find)(s8*, int);
	u8 unk110[0x10];
	u32 (*length)(const s8*);
} StringFunctions;

extern "C" StringFunctions* lbl_8042C9A4;
extern "C" ObjectDispatch* fn_801971A4(void);

extern "C" s8* fn_80012EA0(const s8* path)
{
	s8* normalized = (s8*)(lbl_8042C9A4->length(path) + 1);
	normalized     = (s8*)fn_801971A4()->allocate((u32)normalized);

	if (normalized != NULL) {
		s8* separator;

		if (*path == '.') {
			path++;
		}
		if (*path == '/') {
			path++;
		}
		if (*path == '\\') {
			path++;
		}
		if (*path == ':') {
			path++;
		}

		lbl_8042C9A4->copy(normalized, path);

		while ((separator = lbl_8042C9A4->find(normalized, '\\')) != NULL) {
			*separator = '/';
		}
		while ((separator = lbl_8042C9A4->find(normalized, ':')) != NULL) {
			*separator = '/';
		}
	}

	return normalized;
}
