#include "types.h"

// The record that registers MOJI with the editor.
//
// The claim is .text 0x9246C to 0x9251C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage05D carries this run.

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
extern "C" void mojiLoad(void);
extern "C" void mojiUnload(void);
extern "C" void mojiCreate(void);
extern "C" void mojiReset(void);
extern "C" ObjectEntry mojiEntry;
extern "C" char mojiDisplayName[];
extern "C" char mojiFieldTypes[];
extern "C" const char* mojiFieldNames[];

extern "C" void mojiRegister(void)
{
	mojiEntry.flags = 0;
	mojiEntry.unk18 = 0;

	mojiEntry.name   = mojiDisplayName;
	mojiEntry.load   = mojiLoad;
	mojiEntry.unload = mojiUnload;
	mojiEntry.create = mojiCreate;
	mojiEntry.reset  = mojiReset;

	mojiEntry.flags = 0x1000;
	mojiEntry.unk18 = 0;
	mojiEntry.unk20 = 0xf;
	mojiEntry.unk1C = 0x582;
	mojiEntry.unk1E = 2;
	mojiEntry.unk21 = 0;

	mojiEntry.fieldTypes = mojiFieldTypes;
	mojiEntry.fieldNames = mojiFieldNames;

	if (mojiFieldTypes != NULL) {
		mojiEntry.flags |= 8;
	} else {
		mojiEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const mojiCtorEntry)(void) = mojiRegister;
