#include "types.h"

// The record that registers GRASS2 OBJECT with the editor.
//
// The claim is .text 0xC5EFC to 0xC5FA4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccF" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage11D carries this run.

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
extern "C" void grass2ObjectLoad(void);
extern "C" void grass2ObjectUnload(void);
extern "C" void grass2ObjectCreate(void);
extern "C" ObjectEntry grass2ObjectEntry;
extern "C" char grass2ObjectDisplayName[];
extern "C" char grass2ObjectFieldTypes[];
extern "C" const char* grass2ObjectFieldNames[];

extern "C" void grass2ObjectRegister(void)
{
	grass2ObjectEntry.flags = 0;
	grass2ObjectEntry.unk18 = 0;

	grass2ObjectEntry.name   = grass2ObjectDisplayName;
	grass2ObjectEntry.load   = grass2ObjectLoad;
	grass2ObjectEntry.unload = grass2ObjectUnload;
	grass2ObjectEntry.create = grass2ObjectCreate;
	grass2ObjectEntry.reset  = NULL;

	grass2ObjectEntry.flags = 0x20000;
	grass2ObjectEntry.unk18 = 0;
	grass2ObjectEntry.unk20 = 0x1e;
	grass2ObjectEntry.unk1C = 0x118c;
	grass2ObjectEntry.unk1E = 2;
	grass2ObjectEntry.unk21 = 0;

	grass2ObjectEntry.fieldTypes = grass2ObjectFieldTypes;
	grass2ObjectEntry.fieldNames = grass2ObjectFieldNames;

	if (grass2ObjectFieldTypes != NULL) {
		grass2ObjectEntry.flags |= 8;
	} else {
		grass2ObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const grass2ObjectCtorEntry)(void) = grass2ObjectRegister;
