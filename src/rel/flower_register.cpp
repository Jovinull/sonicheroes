#include "types.h"

// The record that registers FLOWER OBJECT with the editor.
//
// The claim is .text 0xB6320 to 0xB63D0 and the .ctors word at 0x134 that names
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
// Only stage01D carries this run.

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
extern "C" void flowerObjectLoad(void);
extern "C" void flowerObjectUnload(void);
extern "C" void flowerObjectCreate(void);
extern "C" void flowerObjectReset(void);
extern "C" ObjectEntry flowerObjectEntry;
extern "C" char flowerObjectDisplayName[];
extern "C" char flowerObjectFieldTypes[];
extern "C" const char* flowerObjectFieldNames[];

extern "C" void flowerObjectRegister(void)
{
	flowerObjectEntry.flags = 0;
	flowerObjectEntry.unk18 = 0;

	flowerObjectEntry.name   = flowerObjectDisplayName;
	flowerObjectEntry.load   = flowerObjectLoad;
	flowerObjectEntry.unload = flowerObjectUnload;
	flowerObjectEntry.create = flowerObjectCreate;
	flowerObjectEntry.reset  = flowerObjectReset;

	flowerObjectEntry.flags = 0x20000;
	flowerObjectEntry.unk18 = 0;
	flowerObjectEntry.unk20 = 30;
	flowerObjectEntry.unk1C = 50;
	flowerObjectEntry.unk1E = 2;
	flowerObjectEntry.unk21 = 0;

	flowerObjectEntry.fieldTypes = flowerObjectFieldTypes;
	flowerObjectEntry.fieldNames = flowerObjectFieldNames;

	if (flowerObjectEntry.fieldTypes != NULL) {
		flowerObjectEntry.flags |= 8;
	} else {
		flowerObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const flowerObjectCtorEntry)(void) = flowerObjectRegister;
