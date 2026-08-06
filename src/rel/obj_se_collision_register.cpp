#include "types.h"

// The record that registers OBJ SECollision  with the editor.
//
// The claim is .text 0xC0CD4 to 0xC0D68 and the .ctors word at 0x150 that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here, and each hook is named from the entry offset it
// is stored into.
//
// It carries editor fields, so the type and label slots are filled. The flags word is 0x0; its width is what sets this run's length apart
// from others of the same shape.
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
	void (*reset)(void);     // 0x10
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
extern "C" void objSecollisionCreate(void);
extern "C" ObjectEntry objSecollisionEntry;
extern "C" char objSecollisionDisplayName[];
extern "C" char objSecollisionFieldTypes[];
extern "C" const char* objSecollisionFieldNames[];

extern "C" void objSecollisionRegister(void)
{
	objSecollisionEntry.flags = 0;
	objSecollisionEntry.unk18 = 0;

	objSecollisionEntry.name   = objSecollisionDisplayName;
	objSecollisionEntry.load   = NULL;
	objSecollisionEntry.unload = NULL;
	objSecollisionEntry.create = objSecollisionCreate;
	objSecollisionEntry.reset  = NULL;

	objSecollisionEntry.flags = 0x0;
	objSecollisionEntry.unk18 = 0;
	objSecollisionEntry.unk20 = 20;
	objSecollisionEntry.unk1C = 129;
	objSecollisionEntry.unk1E = 2;
	objSecollisionEntry.unk21 = 0;

	objSecollisionEntry.fieldTypes = objSecollisionFieldTypes;
	objSecollisionEntry.fieldNames = objSecollisionFieldNames;

	if (objSecollisionEntry.fieldTypes != NULL) {
		objSecollisionEntry.flags |= 8;
	} else {
		objSecollisionEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const objSecollisionCtorEntry)(void) = objSecollisionRegister;
