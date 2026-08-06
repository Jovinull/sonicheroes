#include "types.h"

// The record that registers WOOD. CONT. OBJECT with the editor.
//
// The claim is .text 0x140F4 to 0x1419C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into. The label array is
// the one the three container classes share, so it keeps the shared name.
//
// "s" is the field type string: one character per parameter the
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
extern "C" void woodContObjectLoad(void);
extern "C" void woodContObjectUnload(void);
extern "C" void woodContObjectCreate(void);
extern "C" ObjectEntry woodContObjectEntry;
extern "C" char woodContObjectDisplayName[];
extern "C" char woodContObjectFieldTypes[];
extern "C" const char* containerFieldNames[];

extern "C" void woodContObjectRegister(void)
{
	woodContObjectEntry.flags = 0;
	woodContObjectEntry.unk18 = 0;

	woodContObjectEntry.name   = woodContObjectDisplayName;
	woodContObjectEntry.load   = woodContObjectLoad;
	woodContObjectEntry.unload = woodContObjectUnload;
	woodContObjectEntry.create = woodContObjectCreate;
	woodContObjectEntry.reset  = NULL;

	woodContObjectEntry.flags = 0x20000;
	woodContObjectEntry.unk18 = 0;
	woodContObjectEntry.unk20 = 0x1e;
	woodContObjectEntry.unk1C = 0x20;
	woodContObjectEntry.unk1E = 2;
	woodContObjectEntry.unk21 = 0;

	woodContObjectEntry.fieldTypes = woodContObjectFieldTypes;
	woodContObjectEntry.fieldNames = containerFieldNames;

	if (woodContObjectFieldTypes != NULL) {
		woodContObjectEntry.flags |= 8;
	} else {
		woodContObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const woodContObjectCtorEntry)(void) = woodContObjectRegister;
