#include "types.h"

// The record that registers KEY OBJECT with the editor.
//
// The claim is .text 0xC20F4 to 0xC218C and the .ctors word at 0x154 that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// It shows no editor fields, so the type and label slots take NULL and
// the trailing test folds bit 3 out rather than in.
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
extern "C" void keyObjectLoad(void);
extern "C" void keyObjectUnload(void);
extern "C" void keyObjectCreate(void);
extern "C" ObjectEntry keyObjectEntry;
extern "C" char keyObjectDisplayName[];

extern "C" void keyObjectRegister(void)
{
	keyObjectEntry.flags = 0;
	keyObjectEntry.unk18 = 0;

	keyObjectEntry.name   = keyObjectDisplayName;
	keyObjectEntry.load   = keyObjectLoad;
	keyObjectEntry.unload = keyObjectUnload;
	keyObjectEntry.create = keyObjectCreate;
	keyObjectEntry.unk10  = NULL;

	keyObjectEntry.flags = 0x20000;
	keyObjectEntry.unk18 = 0;
	keyObjectEntry.unk20 = 30;
	keyObjectEntry.unk1C = 103;
	keyObjectEntry.unk1E = 2;
	keyObjectEntry.unk21 = 0;

	keyObjectEntry.fieldTypes = NULL;
	keyObjectEntry.fieldNames = NULL;

	if (keyObjectEntry.fieldTypes != NULL) {
		keyObjectEntry.flags |= 8;
	} else {
		keyObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const keyObjectCtorEntry)(void) = keyObjectRegister;
