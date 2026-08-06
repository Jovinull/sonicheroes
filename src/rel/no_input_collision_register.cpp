#include "types.h"

// The record that registers NO_INPUT_COLLISION OBJECT with the editor.
//
// The claim is .text 0x6DD8C to 0x6DE34 and the .ctors word at 0xB4 that names
// it. Only the record is taken: the three hooks it points at stay assembly and
// are reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// The flags word is 0x20000, small enough for one instruction, which is the
// whole difference from rel/s66_star_register.cpp's two-instruction load.
//
// The .ctors slot is derived: every function owning a .ctors word, sorted by run
// address, at position times four.
//
// The run is the same in thirteen of the fourteen stage modules. stage40D
// registers the same object from a different build and does not share it.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void* unk10;             // 0x10
	u32 flags;               // 0x14
	u32 unk18;               // 0x18
	s16 unk1C;               // 0x1C
	s16 unk1E;               // 0x1E
	u8 unk20;                // 0x20
	u8 unk21;                // 0x21
	u8 pad22[2];             // 0x22
	const char* fieldTypes;  // 0x24
	const char** fieldNames; // 0x28
} ObjectEntry;               // 0x2C

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void noInputCollisionObjectLoad(void);
extern "C" void noInputCollisionObjectUnload(void);
extern "C" void noInputCollisionObjectCreate(void);
extern "C" ObjectEntry noInputCollisionObjectEntry;
extern "C" char noInputCollisionObjectDisplayName[];
extern "C" char noInputCollisionObjectFieldTypes[];
extern "C" const char* noInputCollisionObjectFieldNames[];

extern "C" void noInputCollisionObjectRegister(void)
{
	noInputCollisionObjectEntry.flags = 0;
	noInputCollisionObjectEntry.unk18 = 0;

	noInputCollisionObjectEntry.name   = noInputCollisionObjectDisplayName;
	noInputCollisionObjectEntry.load   = noInputCollisionObjectLoad;
	noInputCollisionObjectEntry.unload = noInputCollisionObjectUnload;
	noInputCollisionObjectEntry.create = noInputCollisionObjectCreate;
	noInputCollisionObjectEntry.unk10  = NULL;

	noInputCollisionObjectEntry.flags = 0x20000;
	noInputCollisionObjectEntry.unk18 = 0;
	noInputCollisionObjectEntry.unk20 = 30;
	noInputCollisionObjectEntry.unk1C = 97;
	noInputCollisionObjectEntry.unk1E = 2;
	noInputCollisionObjectEntry.unk21 = 0;

	noInputCollisionObjectEntry.fieldTypes = noInputCollisionObjectFieldTypes;
	noInputCollisionObjectEntry.fieldNames = noInputCollisionObjectFieldNames;

	if (noInputCollisionObjectFieldTypes != NULL) {
		noInputCollisionObjectEntry.flags |= 8;
	} else {
		noInputCollisionObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const noInputCollisionObjectCtorEntry)(void)
    = noInputCollisionObjectRegister;
