#include "types.h"

// The record that registers POWDER with the editor.
//
// The claim is .text 0x802FC to 0x803AC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FiiiFF" is the field type string: one character per parameter the
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
extern "C" void powderLoad(void);
extern "C" void powderUnload(void);
extern "C" void powderCreate(void);
extern "C" void powderReset(void);
extern "C" ObjectEntry powderEntry;
extern "C" char powderDisplayName[];
extern "C" char powderFieldTypes[];
extern "C" const char* powderFieldNames[];

extern "C" void powderRegister(void)
{
	powderEntry.flags = 0;
	powderEntry.unk18 = 0;

	powderEntry.name   = powderDisplayName;
	powderEntry.load   = powderLoad;
	powderEntry.unload = powderUnload;
	powderEntry.create = powderCreate;
	powderEntry.reset  = powderReset;

	powderEntry.flags = 0x1000;
	powderEntry.unk18 = 0;
	powderEntry.unk20 = 0xa;
	powderEntry.unk1C = 0x999;
	powderEntry.unk1E = 2;
	powderEntry.unk21 = 0;

	powderEntry.fieldTypes = powderFieldTypes;
	powderEntry.fieldNames = powderFieldNames;

	if (powderFieldTypes != NULL) {
		powderEntry.flags |= 8;
	} else {
		powderEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const powderCtorEntry)(void) = powderRegister;
