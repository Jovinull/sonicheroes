#include "types.h"

// The record that registers CHAO OBJECT with the editor.
//
// The claim is .text 0xB7870 to 0xB7920 and the .ctors word at 0x138 that names
// it. Only the record is taken: the four hooks it points at stay assembly and
// are reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// This record fills the slot at +0x10 that the three-hook records leave NULL.
// rel/cannon_register.cpp already reads that slot as the reset hook, which is
// what names the fourth pointer here.
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
extern "C" void chaoObjectLoad(void);
extern "C" void chaoObjectUnload(void);
extern "C" void chaoObjectCreate(void);
extern "C" void chaoObjectReset(void);
extern "C" ObjectEntry chaoObjectEntry;
extern "C" char chaoObjectDisplayName[];
extern "C" char chaoObjectFieldTypes[];
extern "C" const char* chaoObjectFieldNames[];

extern "C" void chaoObjectRegister(void)
{
	chaoObjectEntry.flags = 0;
	chaoObjectEntry.unk18 = 0;

	chaoObjectEntry.name   = chaoObjectDisplayName;
	chaoObjectEntry.load   = chaoObjectLoad;
	chaoObjectEntry.unload = chaoObjectUnload;
	chaoObjectEntry.create = chaoObjectCreate;
	chaoObjectEntry.reset  = chaoObjectReset;

	chaoObjectEntry.flags = 0x20000;
	chaoObjectEntry.unk18 = 0;
	chaoObjectEntry.unk20 = 30;
	chaoObjectEntry.unk1C = 35;
	chaoObjectEntry.unk1E = 2;
	chaoObjectEntry.unk21 = 0;

	chaoObjectEntry.fieldTypes = chaoObjectFieldTypes;
	chaoObjectEntry.fieldNames = chaoObjectFieldNames;

	if (chaoObjectEntry.fieldTypes != NULL) {
		chaoObjectEntry.flags |= 8;
	} else {
		chaoObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const chaoObjectCtorEntry)(void) = chaoObjectRegister;
