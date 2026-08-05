#include "types.h"

// The record that registers EGGHAWK COLLI with the editor.
//
// The claim is .text 0x7BF88 to 0x7C020 and the .ctors word at 0xC0 that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// It installs no load or unload hook, only a create one, so those two
// slots take NULL.
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
extern "C" void egghawkColliCreate(void);
extern "C" ObjectEntry egghawkColliEntry;
extern "C" char egghawkColliDisplayName[];
extern "C" char egghawkColliFieldTypes[];
extern "C" const char* egghawkColliFieldNames[];

extern "C" void egghawkColliRegister(void)
{
	egghawkColliEntry.flags = 0;
	egghawkColliEntry.unk18 = 0;

	egghawkColliEntry.name   = egghawkColliDisplayName;
	egghawkColliEntry.load   = NULL;
	egghawkColliEntry.unload = NULL;
	egghawkColliEntry.create = egghawkColliCreate;
	egghawkColliEntry.unk10  = NULL;

	egghawkColliEntry.flags = 0x1020000;
	egghawkColliEntry.unk18 = 0;
	egghawkColliEntry.unk20 = 20;
	egghawkColliEntry.unk1C = 98;
	egghawkColliEntry.unk1E = 2;
	egghawkColliEntry.unk21 = 0;

	egghawkColliEntry.fieldTypes = egghawkColliFieldTypes;
	egghawkColliEntry.fieldNames = egghawkColliFieldNames;

	if (egghawkColliEntry.fieldTypes != NULL) {
		egghawkColliEntry.flags |= 8;
	} else {
		egghawkColliEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const egghawkColliCtorEntry)(void) = egghawkColliRegister;
