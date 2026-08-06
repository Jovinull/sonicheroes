#include "types.h"

// The record that registers SCAFFOLD OBJECT with the editor.
//
// The claim is .text 0x7EAC0 to 0x7EB68 and the .ctors word that names it.
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
extern "C" void scaffoldObjectLoad(void);
extern "C" void scaffoldObjectUnload(void);
extern "C" void scaffoldObjectCreate(void);
extern "C" ObjectEntry scaffoldObjectEntry;
extern "C" char scaffoldObjectDisplayName[];
extern "C" char scaffoldObjectFieldTypes[];
extern "C" const char* scaffoldObjectFieldNames[];

extern "C" void scaffoldObjectRegister(void)
{
	scaffoldObjectEntry.flags = 0;
	scaffoldObjectEntry.unk18 = 0;

	scaffoldObjectEntry.name   = scaffoldObjectDisplayName;
	scaffoldObjectEntry.load   = scaffoldObjectLoad;
	scaffoldObjectEntry.unload = scaffoldObjectUnload;
	scaffoldObjectEntry.create = scaffoldObjectCreate;
	scaffoldObjectEntry.reset  = NULL;

	scaffoldObjectEntry.flags = 0x20000;
	scaffoldObjectEntry.unk18 = 0;
	scaffoldObjectEntry.unk20 = 0x1e;
	scaffoldObjectEntry.unk1C = 0x1103;
	scaffoldObjectEntry.unk1E = 2;
	scaffoldObjectEntry.unk21 = 0;

	scaffoldObjectEntry.fieldTypes = scaffoldObjectFieldTypes;
	scaffoldObjectEntry.fieldNames = scaffoldObjectFieldNames;

	if (scaffoldObjectFieldTypes != NULL) {
		scaffoldObjectEntry.flags |= 8;
	} else {
		scaffoldObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const scaffoldObjectCtorEntry)(void) = scaffoldObjectRegister;
