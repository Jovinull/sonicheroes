#include "types.h"

// The record that registers RAILBOARD with the editor.
//
// The claim is .text 0x80DC4 to 0x80E74 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccsFF" is the field type string: one character per parameter the
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
extern "C" void railboardLoad(void);
extern "C" void railboardUnload(void);
extern "C" void railboardCreate(void);
extern "C" void railboardReset(void);
extern "C" ObjectEntry railboardEntry;
extern "C" char railboardDisplayName[];
extern "C" char railboardFieldTypes[];
extern "C" const char* railboardFieldNames[];

extern "C" void railboardRegister(void)
{
	railboardEntry.flags = 0;
	railboardEntry.unk18 = 0;

	railboardEntry.name   = railboardDisplayName;
	railboardEntry.load   = railboardLoad;
	railboardEntry.unload = railboardUnload;
	railboardEntry.create = railboardCreate;
	railboardEntry.reset  = railboardReset;

	railboardEntry.flags = 0x20000;
	railboardEntry.unk18 = 0;
	railboardEntry.unk20 = 0xf;
	railboardEntry.unk1C = 0x708;
	railboardEntry.unk1E = 2;
	railboardEntry.unk21 = 0;

	railboardEntry.fieldTypes = railboardFieldTypes;
	railboardEntry.fieldNames = railboardFieldNames;

	if (railboardFieldTypes != NULL) {
		railboardEntry.flags |= 8;
	} else {
		railboardEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const railboardCtorEntry)(void) = railboardRegister;
