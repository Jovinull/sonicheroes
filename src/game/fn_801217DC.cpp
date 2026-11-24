#include "types.h"

// Destructor of a two-base object (HYPOTHESIS; the class name is UNKNOWN): installs the class
// vtable lbl_80289BE8 at 0x18 and its second part (+0x2C) at 0x7C, unlinks the object from its
// owner's singly linked list (owner at 0xD4, list head at owner 0x50, link at 0xD0), runs the base
// destructor fn_80062384 and frees the object on the game heap when the delete flag is positive.
// Returns the object.

struct THeapCtrl {
	void Free(void* p);
};

struct Obj801217DC;

struct Owner801217DC {
	u8 pad0[0x50];
	Obj801217DC* head; // 0x50
};

struct Obj801217DC {
	u8 pad0[0x18];
	void* vtable; // 0x18
	u8 pad1C[0x7C - 0x1C];
	void* vtable2; // 0x7C
	u8 pad80[0xD0 - 0x80];
	Obj801217DC* next;    // 0xD0
	Owner801217DC* owner; // 0xD4
};

extern "C" {
extern THeapCtrl* lbl_8042C148;
extern u8 lbl_80289BE8[];
void fn_80062384(void* object, s16 flags);

Obj801217DC* fn_801217DC(Obj801217DC* o, s16 flags)
{
	if (o != NULL) {
		o->vtable            = lbl_80289BE8;
		o->vtable2           = lbl_80289BE8 + 0x2C;
		Owner801217DC* owner = o->owner;
		Obj801217DC* p       = owner->head;
		if (p != NULL) {
			if (p == o) {
				owner->head = o->next;
				o->next     = NULL;
			} else {
				for (; p->next != o && p->next != NULL; p = p->next) {
				}
				if (p->next == o) {
					p->next = o->next;
				}
				o->next = NULL;
			}
		}
		fn_80062384(o, 0);
		if (flags > 0) {
			lbl_8042C148->Free(o);
		}
	}
	return o;
}
}
