#include "types.h"

// The record that registers REEL OBJECT with the editor.
//
// The claim is .text 0x12174 to 0x1221C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "fffs" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage13D carries this run.

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
extern "C" void reelObjectLoad(void);
extern "C" void reelObjectUnload(void);
extern "C" void reelObjectCreate(void);
extern "C" ObjectEntry reelObjectEntry;
extern "C" char reelObjectDisplayName[];
extern "C" char reelObjectFieldTypes[];
extern "C" const char* reelObjectFieldNames[];

extern "C" void reelObjectRegister(void)
{
	reelObjectEntry.flags = 0;
	reelObjectEntry.unk18 = 0;

	reelObjectEntry.name   = reelObjectDisplayName;
	reelObjectEntry.load   = reelObjectLoad;
	reelObjectEntry.unload = reelObjectUnload;
	reelObjectEntry.create = reelObjectCreate;
	reelObjectEntry.reset  = NULL;

	reelObjectEntry.flags = 0x20000;
	reelObjectEntry.unk18 = 0;
	reelObjectEntry.unk20 = 0x1e;
	reelObjectEntry.unk1C = 0x1d;
	reelObjectEntry.unk1E = 2;
	reelObjectEntry.unk21 = 0;

	reelObjectEntry.fieldTypes = reelObjectFieldTypes;
	reelObjectEntry.fieldNames = reelObjectFieldNames;

	if (reelObjectFieldTypes != NULL) {
		reelObjectEntry.flags |= 8;
	} else {
		reelObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const reelObjectCtorEntry)(void) = reelObjectRegister;
