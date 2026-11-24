#include "types.h"

// Destructor (HYPOTHESIS; the class name is UNKNOWN): installs the class vtable lbl_8025AE78;
// unregisters the handle at 0x12C from the list at word 0x7258 of lbl_8042C1D0 (fn_8015BBF8),
// releases it (fn_80150958) and clears it; unlinks the object from the per-kind list (kind byte
// 0xF0, heads lbl_803E7258, next 0xE8, previous 0xEC; a head's previous pointer is the tail) and
// decrements the kind's count in lbl_8042C5B4; then runs the C_COLLI destructor of the member at
// 0x28 and the TObject destructor, and frees the object on the game heap when the delete flag is
// positive. Returns the object.

struct THeapCtrl {
	void Free(void* p);
};

struct Stage8010A8DC {
	u8 pad0[0x7258];
	void* list7258; // 0x7258
};

struct Obj8010A8DC {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x28 - 0x1C];
	u8 colli[0xE8 - 0x28]; // 0x28: C_COLLI
	Obj8010A8DC* next;     // 0xE8
	Obj8010A8DC* prev;     // 0xEC
	s8 kind;               // 0xF0
	u8 padF1[0x12C - 0xF1];
	void* handle; // 0x12C
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern Stage8010A8DC* lbl_8042C1D0;
extern u8 lbl_8025AE78[];
extern Obj8010A8DC* lbl_803E7258[4];
extern u8 lbl_8042C5B4[4];
void fn_8015BBF8(void* list, void* handle);
void fn_80150958(void* handle);
void __dt__7C_COLLIFv(void* colli, s16 flags);
void __dt__7TObjectFv(void* object, s16 flags);

Obj8010A8DC* fn_8010A8DC(Obj8010A8DC* o, s16 flags)
{
	if (o != NULL) {
		o->vtable = lbl_8025AE78;
		if (o->handle != NULL) {
			fn_8015BBF8(lbl_8042C1D0->list7258, o->handle);
			fn_80150958(o->handle);
			o->handle = NULL;
		}
		if (o->prev != NULL) {
			if (lbl_803E7258[o->kind] == o) {
				lbl_803E7258[o->kind] = o->next;
			} else {
				o->prev->next     = o->next;
				Obj8010A8DC* head = lbl_803E7258[o->kind];
				if (head != NULL && head->prev == o) {
					head->prev = o->prev;
				}
			}
			lbl_8042C5B4[o->kind]--;
		}
		if (o->next != NULL) {
			o->next->prev = o->prev;
		}
		o->prev = NULL;
		o->next = NULL;
		__dt__7C_COLLIFv(o->colli, 0);
		__dt__7TObjectFv(o, 0);
		if (flags > 0) {
			lbl_8042C148->Free(o);
		}
	}
	return o;
}
}
