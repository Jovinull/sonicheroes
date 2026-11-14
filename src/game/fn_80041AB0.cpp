// Returns the signed byte selected by an object's own index byte (entry [0x3B] of its 0x110
// byte table) for the object registered under the given id (HYPOTHESIS): the id is first looked
// up among the four ids of lbl_80241CB0 (objects lbl_80303DC8), then among the six ids of
// lbl_80241CC0 (the object at 0x258 of the entries of lbl_802AD0D0). Returns -1 for an unknown
// id. Field names are inferred from this function only.
#include "types.h"

struct Object80041AB0 {
	u8 pad0[0x3B];
	s8 tableIndex; // 0x3B
	u8 pad3C[0x110 - 0x3C];
	s8 table[1]; // 0x110 (extent UNKNOWN)
};

struct Owner80041AB0 {
	u8 pad0[0x258];
	Object80041AB0* object; // 0x258
};

extern "C" {
extern s32 lbl_80241CB0[4];
extern s32 lbl_80241CC0[6];
extern Object80041AB0* lbl_80303DC8[4];
extern Owner80041AB0* lbl_802AD0D0[8];

s32 fn_80041AB0(s32 id)
{
	s32 i;

	for (i = 0; i < 4; i++) {
		if (id == lbl_80241CB0[i]) {
			Object80041AB0* object = lbl_80303DC8[i];
			return object->table[object->tableIndex];
		}
	}
	for (i = 0; i < 6; i++) {
		if (id == lbl_80241CC0[i]) {
			Object80041AB0* object = lbl_802AD0D0[i]->object;
			return object->table[object->tableIndex];
		}
	}
	return -1;
}
}
