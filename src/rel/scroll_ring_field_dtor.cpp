#include "types.h"

// The destructor of one collision field of the scroll ring
// (scrollRingFieldDtor here), handed to __destroy_new_array by
// rel/scroll_ring_dtor.cpp. The field is a collision block with a table of its
// own at 0xD8: the destructor puts the field's table back, clears the word
// before it, runs the collision block's destructor and, when asked to, frees
// the field.

typedef struct ScrollRingField {
	u8 colli[0xD4]; // 0x00
	s32 unkD4;      // 0xD4
	void* vtable;   // 0xD8
} ScrollRingField;

extern "C" void* scrollRingFieldVtable[];

extern "C" void __dt__7C_COLLIFv(void* colli, s16 flags);
extern "C" void __dl__FPv(void* memory);

extern "C" ScrollRingField* scrollRingFieldDtor(ScrollRingField* field, s16 flags)
{
	if (field != NULL) {
		field->vtable = scrollRingFieldVtable;
		field->unkD4  = 0;
		__dt__7C_COLLIFv(field, 0);
		if (flags > 0) {
			__dl__FPv(field);
		}
	}
	return field;
}
