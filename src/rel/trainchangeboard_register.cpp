#include "types.h"

// The record that registers TRAINCHANGEBOARD with the editor.
//
// The claim is .text 0x90818 to 0x908C8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "xx" is the field type string: one character per parameter the
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
extern "C" void trainchangeboardLoad(void);
extern "C" void trainchangeboardUnload(void);
extern "C" void trainchangeboardCreate(void);
extern "C" void trainchangeboardReset(void);
extern "C" ObjectEntry trainchangeboardEntry;
extern "C" char trainchangeboardDisplayName[];
extern "C" char trainchangeboardFieldTypes[];
extern "C" const char* trainchangeboardFieldNames[];

extern "C" void trainchangeboardRegister(void)
{
	trainchangeboardEntry.flags = 0;
	trainchangeboardEntry.unk18 = 0;

	trainchangeboardEntry.name   = trainchangeboardDisplayName;
	trainchangeboardEntry.load   = trainchangeboardLoad;
	trainchangeboardEntry.unload = trainchangeboardUnload;
	trainchangeboardEntry.create = trainchangeboardCreate;
	trainchangeboardEntry.reset  = trainchangeboardReset;

	trainchangeboardEntry.flags = 0x20000;
	trainchangeboardEntry.unk18 = 0;
	trainchangeboardEntry.unk20 = 0xf;
	trainchangeboardEntry.unk1C = 0x702;
	trainchangeboardEntry.unk1E = 2;
	trainchangeboardEntry.unk21 = 0;

	trainchangeboardEntry.fieldTypes = trainchangeboardFieldTypes;
	trainchangeboardEntry.fieldNames = trainchangeboardFieldNames;

	if (trainchangeboardFieldTypes != NULL) {
		trainchangeboardEntry.flags |= 8;
	} else {
		trainchangeboardEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const trainchangeboardCtorEntry)(void)
    = trainchangeboardRegister;
