#include "types.h"

// The record that registers TREE OBJECT with the editor.
//
// The claim is .text 0xC4DEC to 0xC4E94 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "Fc" is the field type string: one character per parameter the
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
extern "C" void treeObjectLoad(void);
extern "C" void treeObjectUnload(void);
extern "C" void treeObjectCreate(void);
extern "C" ObjectEntry treeObjectEntry;
extern "C" char treeObjectDisplayName[];
extern "C" char treeObjectFieldTypes[];
extern "C" const char* treeObjectFieldNames[];

extern "C" void treeObjectRegister(void)
{
	treeObjectEntry.flags = 0;
	treeObjectEntry.unk18 = 0;

	treeObjectEntry.name   = treeObjectDisplayName;
	treeObjectEntry.load   = treeObjectLoad;
	treeObjectEntry.unload = treeObjectUnload;
	treeObjectEntry.create = treeObjectCreate;
	treeObjectEntry.reset  = NULL;

	treeObjectEntry.flags = 0x20000;
	treeObjectEntry.unk18 = 0;
	treeObjectEntry.unk20 = 0x1e;
	treeObjectEntry.unk1C = 0x118a;
	treeObjectEntry.unk1E = 2;
	treeObjectEntry.unk21 = 0;

	treeObjectEntry.fieldTypes = treeObjectFieldTypes;
	treeObjectEntry.fieldNames = treeObjectFieldNames;

	if (treeObjectFieldTypes != NULL) {
		treeObjectEntry.flags |= 8;
	} else {
		treeObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const treeObjectCtorEntry)(void) = treeObjectRegister;
