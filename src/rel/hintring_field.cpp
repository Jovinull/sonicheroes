#include "types.h"

// The field callback hintringBind hooks, in the hint ring's translation unit: the same code as
// rel/checkpoint_field.cpp, which keeps the object's four field bytes and
// takes the last from the value.

typedef struct Field {
	u8 a; // 0x00
	u8 b; // 0x01
	u8 c; // 0x02
	u8 d; // 0x03
} Field;  // 0x04

typedef struct BindObject {
	u8 unk0[0x04]; // 0x00
	Field field;   // 0x04
} BindObject;      // 0x08

extern "C" void hintringFieldCallback(BindObject* object, const u8* value)
{
	Field next = object->field;
	u8 last    = *value;

	next.d = last;

	object->field.a = next.a;
	object->field.b = next.b;
	object->field.c = next.c;
	object->field.d = last;
}
