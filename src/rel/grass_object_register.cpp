#include "types.h"

// The record that registers GRASS OBJECT with the editor.
//
// The claim is .text 0xC74A0 to 0xC7548 and the .ctors word that names it.
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
extern "C" void grassObjectLoad(void);
extern "C" void grassObjectUnload(void);
extern "C" void grassObjectCreate(void);
extern "C" ObjectEntry grassObjectEntry;
extern "C" char grassObjectDisplayName[];
extern "C" char grassObjectFieldTypes[];
extern "C" const char* grassObjectFieldNames[];

extern "C" void grassObjectRegister(void)
{
	grassObjectEntry.flags = 0;
	grassObjectEntry.unk18 = 0;

	grassObjectEntry.name   = grassObjectDisplayName;
	grassObjectEntry.load   = grassObjectLoad;
	grassObjectEntry.unload = grassObjectUnload;
	grassObjectEntry.create = grassObjectCreate;
	grassObjectEntry.reset  = NULL;

	grassObjectEntry.flags = 0x20000;
	grassObjectEntry.unk18 = 0;
	grassObjectEntry.unk20 = 0x1e;
	grassObjectEntry.unk1C = 0x118b;
	grassObjectEntry.unk1E = 2;
	grassObjectEntry.unk21 = 0;

	grassObjectEntry.fieldTypes = grassObjectFieldTypes;
	grassObjectEntry.fieldNames = grassObjectFieldNames;

	if (grassObjectFieldTypes != NULL) {
		grassObjectEntry.flags |= 8;
	} else {
		grassObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const grassObjectCtorEntry)(void) = grassObjectRegister;
