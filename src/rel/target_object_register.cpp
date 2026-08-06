#include "types.h"

// The record that registers TARGET OBJECT with the editor.
//
// The claim is .text 0x24118 to 0x241C0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccC" is the field type string: one character per parameter the
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
extern "C" void targetObjectLoad(void);
extern "C" void targetObjectUnload(void);
extern "C" void targetObjectCreate(void);
extern "C" ObjectEntry targetObjectEntry;
extern "C" char targetObjectDisplayName[];
extern "C" char targetObjectFieldTypes[];
extern "C" const char* targetObjectFieldNames[];

extern "C" void targetObjectRegister(void)
{
	targetObjectEntry.flags = 0;
	targetObjectEntry.unk18 = 0;

	targetObjectEntry.name   = targetObjectDisplayName;
	targetObjectEntry.load   = targetObjectLoad;
	targetObjectEntry.unload = targetObjectUnload;
	targetObjectEntry.create = targetObjectCreate;
	targetObjectEntry.reset  = NULL;

	targetObjectEntry.flags = 0x8000000;
	targetObjectEntry.unk18 = 0;
	targetObjectEntry.unk20 = 0x1e;
	targetObjectEntry.unk1C = 0x7;
	targetObjectEntry.unk1E = 2;
	targetObjectEntry.unk21 = 0;

	targetObjectEntry.fieldTypes = targetObjectFieldTypes;
	targetObjectEntry.fieldNames = targetObjectFieldNames;

	if (targetObjectFieldTypes != NULL) {
		targetObjectEntry.flags |= 8;
	} else {
		targetObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const targetObjectCtorEntry)(void) = targetObjectRegister;
