#include "types.h"

// The record that registers HERMITCRAB OBJECT with the editor.
//
// The claim is .text 0xC83D0 to 0xC8480 and the .ctors word at 0x160 that names
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
extern "C" void hermitcrabObjectLoad(void);
extern "C" void hermitcrabObjectUnload(void);
extern "C" void hermitcrabObjectCreate(void);
extern "C" void hermitcrabObjectReset(void);
extern "C" ObjectEntry hermitcrabObjectEntry;
extern "C" char hermitcrabObjectDisplayName[];
extern "C" char hermitcrabObjectFieldTypes[];
extern "C" const char* hermitcrabObjectFieldNames[];

extern "C" void hermitcrabObjectRegister(void)
{
	hermitcrabObjectEntry.flags = 0;
	hermitcrabObjectEntry.unk18 = 0;

	hermitcrabObjectEntry.name   = hermitcrabObjectDisplayName;
	hermitcrabObjectEntry.load   = hermitcrabObjectLoad;
	hermitcrabObjectEntry.unload = hermitcrabObjectUnload;
	hermitcrabObjectEntry.create = hermitcrabObjectCreate;
	hermitcrabObjectEntry.reset  = hermitcrabObjectReset;

	hermitcrabObjectEntry.flags = 0x20000;
	hermitcrabObjectEntry.unk18 = 0;
	hermitcrabObjectEntry.unk20 = 30;
	hermitcrabObjectEntry.unk1C = 267;
	hermitcrabObjectEntry.unk1E = 2;
	hermitcrabObjectEntry.unk21 = 0;

	hermitcrabObjectEntry.fieldTypes = hermitcrabObjectFieldTypes;
	hermitcrabObjectEntry.fieldNames = hermitcrabObjectFieldNames;

	if (hermitcrabObjectEntry.fieldTypes != NULL) {
		hermitcrabObjectEntry.flags |= 8;
	} else {
		hermitcrabObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const hermitcrabObjectCtorEntry)(void)
    = hermitcrabObjectRegister;
