#include "types.h"

// The record that registers AUTODOOR with the editor.
//
// The claim is .text 0x8C4BC to 0x8C56C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage07D carries this run.

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
extern "C" void autodoorLoad(void);
extern "C" void autodoorUnload(void);
extern "C" void autodoorCreate(void);
extern "C" void autodoorReset(void);
extern "C" ObjectEntry autodoorEntry;
extern "C" char autodoorDisplayName[];
extern "C" char autodoorFieldTypes[];
extern "C" const char* autodoorFieldNames[];

extern "C" void autodoorRegister(void)
{
	autodoorEntry.flags = 0;
	autodoorEntry.unk18 = 0;

	autodoorEntry.name   = autodoorDisplayName;
	autodoorEntry.load   = autodoorLoad;
	autodoorEntry.unload = autodoorUnload;
	autodoorEntry.create = autodoorCreate;
	autodoorEntry.reset  = autodoorReset;

	autodoorEntry.flags = 0x1000;
	autodoorEntry.unk18 = 0;
	autodoorEntry.unk20 = 0xf;
	autodoorEntry.unk1C = 0x797;
	autodoorEntry.unk1E = 2;
	autodoorEntry.unk21 = 0;

	autodoorEntry.fieldTypes = autodoorFieldTypes;
	autodoorEntry.fieldNames = autodoorFieldNames;

	if (autodoorFieldTypes != NULL) {
		autodoorEntry.flags |= 8;
	} else {
		autodoorEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const autodoorCtorEntry)(void) = autodoorRegister;
