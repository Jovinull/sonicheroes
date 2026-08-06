#include "types.h"

// The record that registers BIGRINGS OBJECT with the editor.
//
// The claim is .text 0x1F0DC to 0x1F184 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "sSff" is the field type string: one character per parameter the
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
extern "C" void bigringsObjectLoad(void);
extern "C" void bigringsObjectUnload(void);
extern "C" void bigringsObjectCreate(void);
extern "C" ObjectEntry bigringsObjectEntry;
extern "C" char bigringsObjectDisplayName[];
extern "C" char bigringsObjectFieldTypes[];
extern "C" const char* bigringsObjectFieldNames[];

extern "C" void bigringsObjectRegister(void)
{
	bigringsObjectEntry.flags = 0;
	bigringsObjectEntry.unk18 = 0;

	bigringsObjectEntry.name   = bigringsObjectDisplayName;
	bigringsObjectEntry.load   = bigringsObjectLoad;
	bigringsObjectEntry.unload = bigringsObjectUnload;
	bigringsObjectEntry.create = bigringsObjectCreate;
	bigringsObjectEntry.reset  = NULL;

	bigringsObjectEntry.flags = 0x20000;
	bigringsObjectEntry.unk18 = 0;
	bigringsObjectEntry.unk20 = 0x1e;
	bigringsObjectEntry.unk1C = 0xd;
	bigringsObjectEntry.unk1E = 2;
	bigringsObjectEntry.unk21 = 0;

	bigringsObjectEntry.fieldTypes = bigringsObjectFieldTypes;
	bigringsObjectEntry.fieldNames = bigringsObjectFieldNames;

	if (bigringsObjectFieldTypes != NULL) {
		bigringsObjectEntry.flags |= 8;
	} else {
		bigringsObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bigringsObjectCtorEntry)(void) = bigringsObjectRegister;
