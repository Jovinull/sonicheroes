#include "types.h"

// The record that registers MASK OBJECT with the editor.
//
// The claim is .text 0xCA168 to 0xCA210 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "iFFc" is the field type string: one character per parameter the
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
extern "C" void maskObjectLoad(void);
extern "C" void maskObjectUnload(void);
extern "C" void maskObjectCreate(void);
extern "C" ObjectEntry maskObjectEntry;
extern "C" char maskObjectDisplayName[];
extern "C" char maskObjectFieldTypes[];
extern "C" const char* maskObjectFieldNames[];

extern "C" void maskObjectRegister(void)
{
	maskObjectEntry.flags = 0;
	maskObjectEntry.unk18 = 0;

	maskObjectEntry.name   = maskObjectDisplayName;
	maskObjectEntry.load   = maskObjectLoad;
	maskObjectEntry.unload = maskObjectUnload;
	maskObjectEntry.create = maskObjectCreate;
	maskObjectEntry.reset  = NULL;

	maskObjectEntry.flags = 0x20000;
	maskObjectEntry.unk18 = 0;
	maskObjectEntry.unk20 = 0x1e;
	maskObjectEntry.unk1C = 0x118d;
	maskObjectEntry.unk1E = 2;
	maskObjectEntry.unk21 = 0;

	maskObjectEntry.fieldTypes = maskObjectFieldTypes;
	maskObjectEntry.fieldNames = maskObjectFieldNames;

	if (maskObjectFieldTypes != NULL) {
		maskObjectEntry.flags |= 8;
	} else {
		maskObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const maskObjectCtorEntry)(void) = maskObjectRegister;
