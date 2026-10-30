#include "types.h"

// The record that registers METAL SONIC 2ND with the editor.
//
// The claim is .text 0x6F014 to 0x6F0C8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cccc" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Before filling the record it clears metalSonic2ndFlags, the boss's state
// bits.
//
// Only stage28D carries this run.

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
extern "C" void metalSonic2ndLoad(void);
extern "C" void metalSonic2ndUnload(void);
extern "C" void metalSonic2ndCreate(void);
extern "C" ObjectEntry metalSonic2ndEntry;
extern "C" u32 metalSonic2ndFlags;
extern "C" char metalSonic2ndDisplayName[];
extern "C" char metalSonic2ndFieldTypes[];
extern "C" const char* metalSonic2ndFieldNames[];

extern "C" void metalSonic2ndRegister(void)
{
	metalSonic2ndFlags = 0;

	metalSonic2ndEntry.flags = 0;
	metalSonic2ndEntry.unk18 = 0;

	metalSonic2ndEntry.name   = metalSonic2ndDisplayName;
	metalSonic2ndEntry.load   = metalSonic2ndLoad;
	metalSonic2ndEntry.unload = metalSonic2ndUnload;
	metalSonic2ndEntry.create = metalSonic2ndCreate;
	metalSonic2ndEntry.reset  = NULL;

	metalSonic2ndEntry.flags = 0x20000;
	metalSonic2ndEntry.unk18 = 0;
	metalSonic2ndEntry.unk20 = 0x1e;
	metalSonic2ndEntry.unk1C = 0x15d3;
	metalSonic2ndEntry.unk1E = 4;
	metalSonic2ndEntry.unk21 = 0;

	metalSonic2ndEntry.fieldTypes = metalSonic2ndFieldTypes;
	metalSonic2ndEntry.fieldNames = metalSonic2ndFieldNames;

	if (metalSonic2ndFieldTypes != NULL) {
		metalSonic2ndEntry.flags |= 8;
	} else {
		metalSonic2ndEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const metalSonic2ndCtorEntry)(void) = metalSonic2ndRegister;
