#include "types.h"

// The record that registers S03D Pole with the editor.
//
// The claim is .text 0x8562C to 0x856D8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage03D carries this run.

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
extern "C" void s03dPoleLoad(void);
extern "C" void s03dPoleUnload(void);
extern "C" void s03dPoleCreate(void);
extern "C" ObjectEntry s03dPoleEntry;
extern "C" char s03dPoleDisplayName[];
extern "C" char s03dPoleFieldTypes[];
extern "C" const char* s03dPoleFieldNames[];

extern "C" void s03dPoleRegister(void)
{
	s03dPoleEntry.flags = 0;
	s03dPoleEntry.unk18 = 0;

	s03dPoleEntry.name   = s03dPoleDisplayName;
	s03dPoleEntry.load   = s03dPoleLoad;
	s03dPoleEntry.unload = s03dPoleUnload;
	s03dPoleEntry.create = s03dPoleCreate;
	s03dPoleEntry.reset  = NULL;

	s03dPoleEntry.flags = 0x21000;
	s03dPoleEntry.unk18 = 0;
	s03dPoleEntry.unk20 = 0xa;
	s03dPoleEntry.unk1C = 0x384;
	s03dPoleEntry.unk1E = 2;
	s03dPoleEntry.unk21 = 0;

	s03dPoleEntry.fieldTypes = s03dPoleFieldTypes;
	s03dPoleEntry.fieldNames = s03dPoleFieldNames;

	if (s03dPoleFieldTypes != NULL) {
		s03dPoleEntry.flags |= 8;
	} else {
		s03dPoleEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03dPoleCtorEntry)(void) = s03dPoleRegister;
