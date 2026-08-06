#include "types.h"

// The record that registers BUSHZENMAI with the editor.
//
// The claim is .text 0x94BB4 to 0x94C64 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
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
extern "C" void bushzenmaiLoad(void);
extern "C" void bushzenmaiUnload(void);
extern "C" void bushzenmaiCreate(void);
extern "C" void bushzenmaiReset(void);
extern "C" ObjectEntry bushzenmaiEntry;
extern "C" char bushzenmaiDisplayName[];
extern "C" char bushzenmaiFieldTypes[];
extern "C" const char* bushzenmaiFieldNames[];

extern "C" void bushzenmaiRegister(void)
{
	bushzenmaiEntry.flags = 0;
	bushzenmaiEntry.unk18 = 0;

	bushzenmaiEntry.name   = bushzenmaiDisplayName;
	bushzenmaiEntry.load   = bushzenmaiLoad;
	bushzenmaiEntry.unload = bushzenmaiUnload;
	bushzenmaiEntry.create = bushzenmaiCreate;
	bushzenmaiEntry.reset  = bushzenmaiReset;

	bushzenmaiEntry.flags = 0x1000;
	bushzenmaiEntry.unk18 = 0;
	bushzenmaiEntry.unk20 = 0xa;
	bushzenmaiEntry.unk1C = 0x995;
	bushzenmaiEntry.unk1E = 2;
	bushzenmaiEntry.unk21 = 0;

	bushzenmaiEntry.fieldTypes = bushzenmaiFieldTypes;
	bushzenmaiEntry.fieldNames = bushzenmaiFieldNames;

	if (bushzenmaiFieldTypes != NULL) {
		bushzenmaiEntry.flags |= 8;
	} else {
		bushzenmaiEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bushzenmaiCtorEntry)(void) = bushzenmaiRegister;
