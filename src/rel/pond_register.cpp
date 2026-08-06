#include "types.h"

// The record that registers POND with the editor.
//
// The claim is .text 0x7EEB4 to 0x7EF64 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "iFF" is the field type string: one character per parameter the
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
extern "C" void pondLoad(void);
extern "C" void pondUnload(void);
extern "C" void pondCreate(void);
extern "C" void pondReset(void);
extern "C" ObjectEntry pondEntry;
extern "C" char pondDisplayName[];
extern "C" char pondFieldTypes[];
extern "C" const char* pondFieldNames[];

extern "C" void pondRegister(void)
{
	pondEntry.flags = 0;
	pondEntry.unk18 = 0;

	pondEntry.name   = pondDisplayName;
	pondEntry.load   = pondLoad;
	pondEntry.unload = pondUnload;
	pondEntry.create = pondCreate;
	pondEntry.reset  = pondReset;

	pondEntry.flags = 0x1000;
	pondEntry.unk18 = 0;
	pondEntry.unk20 = 0xa;
	pondEntry.unk1C = 0x989;
	pondEntry.unk1E = 2;
	pondEntry.unk21 = 0;

	pondEntry.fieldTypes = pondFieldTypes;
	pondEntry.fieldNames = pondFieldNames;

	if (pondFieldTypes != NULL) {
		pondEntry.flags |= 8;
	} else {
		pondEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const pondCtorEntry)(void) = pondRegister;
