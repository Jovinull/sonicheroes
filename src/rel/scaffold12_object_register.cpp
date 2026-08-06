#include "types.h"

// The record that registers SCAFFOLD12 OBJECT with the editor.
//
// The claim is .text 0x8F7F8 to 0x8F8A0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccssssssC" is the field type string: one character per parameter the
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
extern "C" void scaffold12ObjectLoad(void);
extern "C" void scaffold12ObjectUnload(void);
extern "C" void scaffold12ObjectCreate(void);
extern "C" ObjectEntry scaffold12ObjectEntry;
extern "C" char scaffold12ObjectDisplayName[];
extern "C" char scaffold12ObjectFieldTypes[];
extern "C" const char* scaffold12ObjectFieldNames[];

extern "C" void scaffold12ObjectRegister(void)
{
	scaffold12ObjectEntry.flags = 0;
	scaffold12ObjectEntry.unk18 = 0;

	scaffold12ObjectEntry.name   = scaffold12ObjectDisplayName;
	scaffold12ObjectEntry.load   = scaffold12ObjectLoad;
	scaffold12ObjectEntry.unload = scaffold12ObjectUnload;
	scaffold12ObjectEntry.create = scaffold12ObjectCreate;
	scaffold12ObjectEntry.reset  = NULL;

	scaffold12ObjectEntry.flags = 0x20000;
	scaffold12ObjectEntry.unk18 = 0;
	scaffold12ObjectEntry.unk20 = 0x1e;
	scaffold12ObjectEntry.unk1C = 0x1106;
	scaffold12ObjectEntry.unk1E = 2;
	scaffold12ObjectEntry.unk21 = 0;

	scaffold12ObjectEntry.fieldTypes = scaffold12ObjectFieldTypes;
	scaffold12ObjectEntry.fieldNames = scaffold12ObjectFieldNames;

	if (scaffold12ObjectFieldTypes != NULL) {
		scaffold12ObjectEntry.flags |= 8;
	} else {
		scaffold12ObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const scaffold12ObjectCtorEntry)(void)
    = scaffold12ObjectRegister;
