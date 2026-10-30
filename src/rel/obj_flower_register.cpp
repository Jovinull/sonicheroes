#include "types.h"

// The record that registers FLOWER (TObjFlower, rel/flower_create.cpp) with the editor.
//
// The claim is .text 0x74830 to 0x748E0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The type string and the label array describe the parameters it exposes.
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
extern "C" void flowerLoad(void);
extern "C" void flowerUnload(void);
extern "C" void flowerCreate(void);
extern "C" void flowerReset(void);
extern "C" ObjectEntry flowerEntry;
extern "C" char flowerDisplayName[];
extern "C" char flowerFieldTypes[];
extern "C" const char* flowerFieldNames[];

extern "C" void flowerRegister(void)
{
	flowerEntry.flags = 0;
	flowerEntry.unk18 = 0;

	flowerEntry.name   = flowerDisplayName;
	flowerEntry.load   = flowerLoad;
	flowerEntry.unload = flowerUnload;
	flowerEntry.create = flowerCreate;
	flowerEntry.reset  = flowerReset;

	flowerEntry.flags = 0x1000;
	flowerEntry.unk18 = 0;
	flowerEntry.unk20 = 0xa;
	flowerEntry.unk1C = 0x981;
	flowerEntry.unk1E = 2;
	flowerEntry.unk21 = 0;

	flowerEntry.fieldTypes = flowerFieldTypes;
	flowerEntry.fieldNames = flowerFieldNames;

	if (flowerFieldTypes != NULL) {
		flowerEntry.flags |= 8;
	} else {
		flowerEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const flowerCtorEntry)(void) = flowerRegister;
