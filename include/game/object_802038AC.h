#ifndef GAME_OBJECT_802038AC_H
#define GAME_OBJECT_802038AC_H

#include "game/free_lists_8040EB50.h"

// Object created by fn_802038AC and destroyed by fn_80203998 (free list 2 of lbl_8040EB50).
// Its role is UNKNOWN; field names are inferred from the constructor and destructor only.
struct Object802038AC {
	void* part0;    // 0x0
	void* part4;    // 0x4
	void* part8;    // 0x8
	void* partC;    // 0xC
	void* part10;   // 0x10
	void* part14;   // 0x14: set by fn_80202E8C
	void* part18;   // 0x18: set by fn_80202E8C
	void* list;     // 0x1C
	void* part20;   // 0x20: buffer set by fn_802037C0
	void* part24;   // 0x24
	void* callback; // 0x28
	f32 value2C;    // 0x2C
	f32 value30;    // 0x30
	void* part34;   // 0x34
	u8 pad38[0xC];
	s32 index;   // 0x44
	f32 value48; // 0x48
	f32 value4C; // 0x4C
	f32 value50; // 0x50
	f32 value54; // 0x54
	u8 block[1]; // 0x58: initialised by fn_80202C84 (extent UNKNOWN)
};

#endif
