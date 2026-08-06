#include "types.h"

// The record that registers TRAINCHANGERAIL with the editor.
//
// The claim is .text 0x918D0 to 0x91970 and the .ctors word that names it.
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
extern "C" void trainchangerailLoad(void);
extern "C" void trainchangerailUnload(void);
extern "C" void trainchangerailCreate(void);
extern "C" void trainchangerailReset(void);
extern "C" ObjectEntry trainchangerailEntry;
extern "C" char trainchangerailDisplayName[];

extern "C" void trainchangerailRegister(void)
{
	trainchangerailEntry.flags = 0;
	trainchangerailEntry.unk18 = 0;

	trainchangerailEntry.name   = trainchangerailDisplayName;
	trainchangerailEntry.load   = trainchangerailLoad;
	trainchangerailEntry.unload = trainchangerailUnload;
	trainchangerailEntry.create = trainchangerailCreate;
	trainchangerailEntry.reset  = trainchangerailReset;

	trainchangerailEntry.flags = 0x80;
	trainchangerailEntry.unk18 = 0;
	trainchangerailEntry.unk20 = 0x1e;
	trainchangerailEntry.unk1C = 0x700;
	trainchangerailEntry.unk1E = 2;
	trainchangerailEntry.unk21 = 0;

	trainchangerailEntry.fieldTypes = NULL;
	trainchangerailEntry.fieldNames = NULL;

	if (trainchangerailEntry.fieldTypes != NULL) {
		trainchangerailEntry.flags |= 8;
	} else {
		trainchangerailEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const trainchangerailCtorEntry)(void) = trainchangerailRegister;
