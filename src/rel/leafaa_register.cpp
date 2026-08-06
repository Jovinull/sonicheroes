#include "types.h"

// The record that registers LEAFAA with the editor.
//
// The claim is .text 0x7AE00 to 0x7AEB0 and the .ctors word that names it.
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
extern "C" void leafaaLoad(void);
extern "C" void leafaaUnload(void);
extern "C" void leafaaCreate(void);
extern "C" void leafaaReset(void);
extern "C" ObjectEntry leafaaEntry;
extern "C" char leafaaDisplayName[];
extern "C" char leafaaFieldTypes[];
extern "C" const char* leafaaFieldNames[];

extern "C" void leafaaRegister(void)
{
	leafaaEntry.flags = 0;
	leafaaEntry.unk18 = 0;

	leafaaEntry.name   = leafaaDisplayName;
	leafaaEntry.load   = leafaaLoad;
	leafaaEntry.unload = leafaaUnload;
	leafaaEntry.create = leafaaCreate;
	leafaaEntry.reset  = leafaaReset;

	leafaaEntry.flags = 0x1000;
	leafaaEntry.unk18 = 0;
	leafaaEntry.unk20 = 0xa;
	leafaaEntry.unk1C = 0x98b;
	leafaaEntry.unk1E = 2;
	leafaaEntry.unk21 = 0;

	leafaaEntry.fieldTypes = leafaaFieldTypes;
	leafaaEntry.fieldNames = leafaaFieldNames;

	if (leafaaFieldTypes != NULL) {
		leafaaEntry.flags |= 8;
	} else {
		leafaaEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const leafaaCtorEntry)(void) = leafaaRegister;
