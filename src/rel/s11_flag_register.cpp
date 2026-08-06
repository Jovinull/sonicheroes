#include "types.h"

// The record that registers S11 FLAG with the editor.
//
// The claim is .text 0xC8FD0 to 0xC907C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cccF" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage11D carries this run.

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
extern "C" void s11FlagLoad(void);
extern "C" void s11FlagUnload(void);
extern "C" void s11FlagCreate(void);
extern "C" ObjectEntry s11FlagEntry;
extern "C" char s11FlagDisplayName[];
extern "C" char s11FlagFieldTypes[];
extern "C" const char* s11FlagFieldNames[];

extern "C" void s11FlagRegister(void)
{
	s11FlagEntry.flags = 0;
	s11FlagEntry.unk18 = 0;

	s11FlagEntry.name   = s11FlagDisplayName;
	s11FlagEntry.load   = s11FlagLoad;
	s11FlagEntry.unload = s11FlagUnload;
	s11FlagEntry.create = s11FlagCreate;
	s11FlagEntry.reset  = NULL;

	s11FlagEntry.flags = 0x21000;
	s11FlagEntry.unk18 = 0;
	s11FlagEntry.unk20 = 0x14;
	s11FlagEntry.unk1C = 0x1188;
	s11FlagEntry.unk1E = 2;
	s11FlagEntry.unk21 = 0;

	s11FlagEntry.fieldTypes = s11FlagFieldTypes;
	s11FlagEntry.fieldNames = s11FlagFieldNames;

	if (s11FlagFieldTypes != NULL) {
		s11FlagEntry.flags |= 8;
	} else {
		s11FlagEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s11FlagCtorEntry)(void) = s11FlagRegister;
