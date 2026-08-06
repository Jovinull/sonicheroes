#include "types.h"

// The record that registers BIGCANNON with the editor.
//
// The claim is .text 0x73C6C to 0x73D1C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage07D carries this run.

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
extern "C" void bigcannonLoad(void);
extern "C" void bigcannonUnload(void);
extern "C" void bigcannonCreate(void);
extern "C" void bigcannonReset(void);
extern "C" ObjectEntry bigcannonEntry;
extern "C" char bigcannonDisplayName[];
extern "C" char bigcannonFieldTypes[];
extern "C" const char* bigcannonFieldNames[];

extern "C" void bigcannonRegister(void)
{
	bigcannonEntry.flags = 0;
	bigcannonEntry.unk18 = 0;

	bigcannonEntry.name   = bigcannonDisplayName;
	bigcannonEntry.load   = bigcannonLoad;
	bigcannonEntry.unload = bigcannonUnload;
	bigcannonEntry.create = bigcannonCreate;
	bigcannonEntry.reset  = bigcannonReset;

	bigcannonEntry.flags = 0x20000;
	bigcannonEntry.unk18 = 0;
	bigcannonEntry.unk20 = 0xf;
	bigcannonEntry.unk1C = 0x73e;
	bigcannonEntry.unk1E = 2;
	bigcannonEntry.unk21 = 0;

	bigcannonEntry.fieldTypes = bigcannonFieldTypes;
	bigcannonEntry.fieldNames = bigcannonFieldNames;

	if (bigcannonFieldTypes != NULL) {
		bigcannonEntry.flags |= 8;
	} else {
		bigcannonEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bigcannonCtorEntry)(void) = bigcannonRegister;
