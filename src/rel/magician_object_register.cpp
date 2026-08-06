#include "types.h"

// The record that registers MAGICIAN OBJECT with the editor.
//
// The claim is .text 0xAF904 to 0xAF9AC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccccfffif" is the field type string: one character per parameter the
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
extern "C" void magicianObjectLoad(void);
extern "C" void magicianObjectUnload(void);
extern "C" void magicianObjectCreate(void);
extern "C" ObjectEntry magicianObjectEntry;
extern "C" char magicianObjectDisplayName[];
extern "C" char magicianObjectFieldTypes[];
extern "C" const char* magicianObjectFieldNames[];

extern "C" void magicianObjectRegister(void)
{
	magicianObjectEntry.flags = 0;
	magicianObjectEntry.unk18 = 0;

	magicianObjectEntry.name   = magicianObjectDisplayName;
	magicianObjectEntry.load   = magicianObjectLoad;
	magicianObjectEntry.unload = magicianObjectUnload;
	magicianObjectEntry.create = magicianObjectCreate;
	magicianObjectEntry.reset  = NULL;

	magicianObjectEntry.flags = 0x20000;
	magicianObjectEntry.unk18 = 0;
	magicianObjectEntry.unk20 = 0x1e;
	magicianObjectEntry.unk1C = 0x15c0;
	magicianObjectEntry.unk1E = 4;
	magicianObjectEntry.unk21 = 0;

	magicianObjectEntry.fieldTypes = magicianObjectFieldTypes;
	magicianObjectEntry.fieldNames = magicianObjectFieldNames;

	if (magicianObjectFieldTypes != NULL) {
		magicianObjectEntry.flags |= 8;
	} else {
		magicianObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const magicianObjectCtorEntry)(void) = magicianObjectRegister;
