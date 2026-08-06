#include "types.h"

// The record that registers S14 BombSwitch with the editor.
//
// The claim is .text 0x9DBE4 to 0x9DC8C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "c" is the field type string: one character per parameter the
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
extern "C" void s14BombSwitchLoad(void);
extern "C" void s14BombSwitchUnload(void);
extern "C" void s14BombSwitchCreate(void);
extern "C" ObjectEntry s14BombSwitchEntry;
extern "C" char s14BombSwitchDisplayName[];
extern "C" char s14BombSwitchFieldTypes[];
extern "C" const char* s14BombSwitchFieldNames[];

extern "C" void s14BombSwitchRegister(void)
{
	s14BombSwitchEntry.flags = 0;
	s14BombSwitchEntry.unk18 = 0;

	s14BombSwitchEntry.name   = s14BombSwitchDisplayName;
	s14BombSwitchEntry.load   = s14BombSwitchLoad;
	s14BombSwitchEntry.unload = s14BombSwitchUnload;
	s14BombSwitchEntry.create = s14BombSwitchCreate;
	s14BombSwitchEntry.reset  = NULL;

	s14BombSwitchEntry.flags = 0x20000;
	s14BombSwitchEntry.unk18 = 0;
	s14BombSwitchEntry.unk20 = 0x14;
	s14BombSwitchEntry.unk1C = 0x1405;
	s14BombSwitchEntry.unk1E = 2;
	s14BombSwitchEntry.unk21 = 0;

	s14BombSwitchEntry.fieldTypes = s14BombSwitchFieldTypes;
	s14BombSwitchEntry.fieldNames = s14BombSwitchFieldNames;

	if (s14BombSwitchFieldTypes != NULL) {
		s14BombSwitchEntry.flags |= 8;
	} else {
		s14BombSwitchEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14BombSwitchCtorEntry)(void) = s14BombSwitchRegister;
