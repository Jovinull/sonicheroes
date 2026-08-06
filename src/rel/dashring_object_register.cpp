#include "types.h"

// The record that registers DASHRING OBJECT with the editor.
//
// The claim is .text 0xE378 to 0xE420 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "fs" is the field type string: one character per parameter the
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
extern "C" void dashringObjectLoad(void);
extern "C" void dashringObjectUnload(void);
extern "C" void dashringObjectCreate(void);
extern "C" ObjectEntry dashringObjectEntry;
extern "C" char dashringObjectDisplayName[];
extern "C" char dashringObjectFieldTypes[];
extern "C" const char* dashringObjectFieldNames[];

extern "C" void dashringObjectRegister(void)
{
	dashringObjectEntry.flags = 0;
	dashringObjectEntry.unk18 = 0;

	dashringObjectEntry.name   = dashringObjectDisplayName;
	dashringObjectEntry.load   = dashringObjectLoad;
	dashringObjectEntry.unload = dashringObjectUnload;
	dashringObjectEntry.create = dashringObjectCreate;
	dashringObjectEntry.reset  = NULL;

	dashringObjectEntry.flags = 0x20000;
	dashringObjectEntry.unk18 = 0;
	dashringObjectEntry.unk20 = 0x1e;
	dashringObjectEntry.unk1C = 0xc;
	dashringObjectEntry.unk1E = 2;
	dashringObjectEntry.unk21 = 0;

	dashringObjectEntry.fieldTypes = dashringObjectFieldTypes;
	dashringObjectEntry.fieldNames = dashringObjectFieldNames;

	if (dashringObjectFieldTypes != NULL) {
		dashringObjectEntry.flags |= 8;
	} else {
		dashringObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const dashringObjectCtorEntry)(void) = dashringObjectRegister;
