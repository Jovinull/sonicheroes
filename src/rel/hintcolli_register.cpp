#include "types.h"

// The record that registers HINTCOLLI OBJECT with the editor.
//
// The claim is .text 0xC0008 to 0xC00B8 and the .ctors word at 0x14C that names
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
extern "C" void hintcolliObjectLoad(void);
extern "C" void hintcolliObjectUnload(void);
extern "C" void hintcolliObjectCreate(void);
extern "C" void hintcolliObjectReset(void);
extern "C" ObjectEntry hintcolliObjectEntry;
extern "C" char hintcolliObjectDisplayName[];
extern "C" char hintcolliObjectFieldTypes[];
extern "C" const char* hintcolliObjectFieldNames[];

extern "C" void hintcolliObjectRegister(void)
{
	hintcolliObjectEntry.flags = 0;
	hintcolliObjectEntry.unk18 = 0;

	hintcolliObjectEntry.name   = hintcolliObjectDisplayName;
	hintcolliObjectEntry.load   = hintcolliObjectLoad;
	hintcolliObjectEntry.unload = hintcolliObjectUnload;
	hintcolliObjectEntry.create = hintcolliObjectCreate;
	hintcolliObjectEntry.reset  = hintcolliObjectReset;

	hintcolliObjectEntry.flags = 0x20000;
	hintcolliObjectEntry.unk18 = 0;
	hintcolliObjectEntry.unk20 = 30;
	hintcolliObjectEntry.unk1C = 86;
	hintcolliObjectEntry.unk1E = 2;
	hintcolliObjectEntry.unk21 = 0;

	hintcolliObjectEntry.fieldTypes = hintcolliObjectFieldTypes;
	hintcolliObjectEntry.fieldNames = hintcolliObjectFieldNames;

	if (hintcolliObjectEntry.fieldTypes != NULL) {
		hintcolliObjectEntry.flags |= 8;
	} else {
		hintcolliObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const hintcolliObjectCtorEntry)(void) = hintcolliObjectRegister;
