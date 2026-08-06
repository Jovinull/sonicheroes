#include "types.h"

// The record that registers PAWN OBJECT with the editor.
//
// The claim is .text 0x33CC4 to 0x33D6C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ccccssffffi" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in two of the fourteen stage modules: 13D and 26D.

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
extern "C" void pawnLoad(void);
extern "C" void pawnUnload(void);
extern "C" void pawnCreate(void);
extern "C" ObjectEntry pawnEntry;
extern "C" char pawnDisplayName[];
extern "C" char pawnFieldTypes[];
extern "C" const char* pawnFieldNames[];

extern "C" void pawnRegister(void)
{
	pawnEntry.flags = 0;
	pawnEntry.unk18 = 0;

	pawnEntry.name   = pawnDisplayName;
	pawnEntry.load   = pawnLoad;
	pawnEntry.unload = pawnUnload;
	pawnEntry.create = pawnCreate;
	pawnEntry.reset  = NULL;

	pawnEntry.flags = 0x20000;
	pawnEntry.unk18 = 0;
	pawnEntry.unk20 = 0x1e;
	pawnEntry.unk1C = 0x1510;
	pawnEntry.unk1E = 4;
	pawnEntry.unk21 = 0;

	pawnEntry.fieldTypes = pawnFieldTypes;
	pawnEntry.fieldNames = pawnFieldNames;

	if (pawnFieldTypes != NULL) {
		pawnEntry.flags |= 8;
	} else {
		pawnEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const pawnCtorEntry)(void) = pawnRegister;
