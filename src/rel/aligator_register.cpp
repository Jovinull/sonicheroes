#include "types.h"

// The record that registers ALIGATOR with the editor.
//
// The claim is .text 0x9336C to 0x9341C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage09D carries this run.

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

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void aligatorLoad(void);
extern "C" void aligatorUnload(void);
extern "C" void aligatorCreate(void);
extern "C" void aligatorReset(void);
extern "C" ObjectEntry aligatorEntry;
extern "C" char aligatorDisplayName[];
extern "C" char aligatorFieldTypes[];
extern "C" const char* aligatorFieldNames[];

extern "C" void aligatorRegister(void)
{
	aligatorEntry.flags = 0;
	aligatorEntry.unk18 = 0;

	aligatorEntry.name   = aligatorDisplayName;
	aligatorEntry.load   = aligatorLoad;
	aligatorEntry.unload = aligatorUnload;
	aligatorEntry.create = aligatorCreate;
	aligatorEntry.reset  = aligatorReset;

	aligatorEntry.flags = 0x480;
	aligatorEntry.unk18 = 0;
	aligatorEntry.unk20 = 0xf;
	aligatorEntry.unk1C = 0x90e;
	aligatorEntry.unk1E = 2;
	aligatorEntry.unk21 = 0;

	aligatorEntry.fieldTypes = aligatorFieldTypes;
	aligatorEntry.fieldNames = aligatorFieldNames;

	if (aligatorFieldTypes != NULL) {
		aligatorEntry.flags |= 8;
	} else {
		aligatorEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const aligatorCtorEntry)(void) = aligatorRegister;
