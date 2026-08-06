#include "types.h"

// The record that registers CAGE OBJECT with the editor.
//
// The claim is .text 0x21C90 to 0x21D38 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "Ifff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage13D carries this run.

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
extern "C" void cageObjectLoad(void);
extern "C" void cageObjectUnload(void);
extern "C" void cageObjectCreate(void);
extern "C" ObjectEntry cageObjectEntry;
extern "C" char cageObjectDisplayName[];
extern "C" char cageObjectFieldTypes[];
extern "C" const char* cageObjectFieldNames[];

extern "C" void cageObjectRegister(void)
{
	cageObjectEntry.flags = 0;
	cageObjectEntry.unk18 = 0;

	cageObjectEntry.name   = cageObjectDisplayName;
	cageObjectEntry.load   = cageObjectLoad;
	cageObjectEntry.unload = cageObjectUnload;
	cageObjectEntry.create = cageObjectCreate;
	cageObjectEntry.reset  = NULL;

	cageObjectEntry.flags = 0x20000;
	cageObjectEntry.unk18 = 0;
	cageObjectEntry.unk20 = 0x1e;
	cageObjectEntry.unk1C = 0x24;
	cageObjectEntry.unk1E = 2;
	cageObjectEntry.unk21 = 0;

	cageObjectEntry.fieldTypes = cageObjectFieldTypes;
	cageObjectEntry.fieldNames = cageObjectFieldNames;

	if (cageObjectFieldTypes != NULL) {
		cageObjectEntry.flags |= 8;
	} else {
		cageObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const cageObjectCtorEntry)(void) = cageObjectRegister;
