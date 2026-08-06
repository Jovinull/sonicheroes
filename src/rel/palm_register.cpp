#include "types.h"

// The record that registers PALM with the editor.
//
// The claim is .text 0x7CC2C to 0x7CCDC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "iF" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage09D carries this run.

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
extern "C" void palmLoad(void);
extern "C" void palmUnload(void);
extern "C" void palmCreate(void);
extern "C" void palmReset(void);
extern "C" ObjectEntry palmEntry;
extern "C" char palmDisplayName[];
extern "C" char palmFieldTypes[];
extern "C" const char* palmFieldNames[];

extern "C" void palmRegister(void)
{
	palmEntry.flags = 0;
	palmEntry.unk18 = 0;

	palmEntry.name   = palmDisplayName;
	palmEntry.load   = palmLoad;
	palmEntry.unload = palmUnload;
	palmEntry.create = palmCreate;
	palmEntry.reset  = palmReset;

	palmEntry.flags = 0x1000;
	palmEntry.unk18 = 0;
	palmEntry.unk20 = 0xf;
	palmEntry.unk1C = 0x98a;
	palmEntry.unk1E = 2;
	palmEntry.unk21 = 0;

	palmEntry.fieldTypes = palmFieldTypes;
	palmEntry.fieldNames = palmFieldNames;

	if (palmFieldTypes != NULL) {
		palmEntry.flags |= 8;
	} else {
		palmEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const palmCtorEntry)(void) = palmRegister;
