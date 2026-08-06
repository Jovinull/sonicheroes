#include "types.h"

// The record that registers STOPRAIN with the editor.
//
// The claim is .text 0x8D390 to 0x8D430 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FFF" is the field type string: one character per parameter the
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
extern "C" void stoprainCreate(void);
extern "C" void stoprainReset(void);
extern "C" ObjectEntry stoprainEntry;
extern "C" char stoprainDisplayName[];
extern "C" char stoprainFieldTypes[];
extern "C" const char* stoprainFieldNames[];

extern "C" void stoprainRegister(void)
{
	stoprainEntry.flags = 0;
	stoprainEntry.unk18 = 0;

	stoprainEntry.name   = stoprainDisplayName;
	stoprainEntry.load   = NULL;
	stoprainEntry.unload = NULL;
	stoprainEntry.create = stoprainCreate;
	stoprainEntry.reset  = stoprainReset;

	stoprainEntry.flags = 0x20000;
	stoprainEntry.unk18 = 0;
	stoprainEntry.unk20 = 0xa;
	stoprainEntry.unk1C = 0x90d;
	stoprainEntry.unk1E = 2;
	stoprainEntry.unk21 = 0;

	stoprainEntry.fieldTypes = stoprainFieldTypes;
	stoprainEntry.fieldNames = stoprainFieldNames;

	if (stoprainFieldTypes != NULL) {
		stoprainEntry.flags |= 8;
	} else {
		stoprainEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const stoprainCtorEntry)(void) = stoprainRegister;
