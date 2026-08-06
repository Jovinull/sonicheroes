#include "types.h"

// The record that registers TRAINCHANGESWITCH with the editor.
//
// The claim is .text 0x92B1C to 0x92BBC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void trainchangeswitchLoad(void);
extern "C" void trainchangeswitchUnload(void);
extern "C" void trainchangeswitchCreate(void);
extern "C" void trainchangeswitchReset(void);
extern "C" ObjectEntry trainchangeswitchEntry;
extern "C" char trainchangeswitchDisplayName[];

extern "C" void trainchangeswitchRegister(void)
{
	trainchangeswitchEntry.flags = 0;
	trainchangeswitchEntry.unk18 = 0;

	trainchangeswitchEntry.name   = trainchangeswitchDisplayName;
	trainchangeswitchEntry.load   = trainchangeswitchLoad;
	trainchangeswitchEntry.unload = trainchangeswitchUnload;
	trainchangeswitchEntry.create = trainchangeswitchCreate;
	trainchangeswitchEntry.reset  = trainchangeswitchReset;

	trainchangeswitchEntry.flags = 0x20000;
	trainchangeswitchEntry.unk18 = 0;
	trainchangeswitchEntry.unk20 = 0xf;
	trainchangeswitchEntry.unk1C = 0x701;
	trainchangeswitchEntry.unk1E = 2;
	trainchangeswitchEntry.unk21 = 0;

	trainchangeswitchEntry.fieldTypes = NULL;
	trainchangeswitchEntry.fieldNames = NULL;

	if (trainchangeswitchEntry.fieldTypes != NULL) {
		trainchangeswitchEntry.flags |= 8;
	} else {
		trainchangeswitchEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const trainchangeswitchCtorEntry)(void)
    = trainchangeswitchRegister;
