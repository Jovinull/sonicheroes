#include "types.h"

// The field callback the checkpoint's bind hook installs. It replaces the last
// byte of the object's four byte field with the one it is handed.
//
// The claim is .text 0x00010A94 to 0x00010ACC and nothing else. It reads no
// constant, so it owns no rodata.
//
// The field is read whole, changed and written back rather than being poked in
// place, which is why the original stages it through the frame: CodeWarrior
// copies a four byte structure member by member.
//
// The run is the same in the twelve stage modules that carry it, checked by
// normalising the disassembly and comparing across modules.

typedef struct Field {
	u8 a; // 0x00
	u8 b; // 0x01
	u8 c; // 0x02
	u8 d; // 0x03
} Field;  // 0x04

typedef struct Checkpoint {
	u8 unk0[0x04]; // 0x00
	Field field;   // 0x04
} Checkpoint;      // 0x08

extern "C" void checkpointFieldCallback(Checkpoint* object, const u8* value)
{
	Field next = object->field;
	u8 last    = *value;

	next.d = last;

	object->field.a = next.a;
	object->field.b = next.b;
	object->field.c = next.c;
	object->field.d = last;
}
