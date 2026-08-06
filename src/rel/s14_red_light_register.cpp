#include "types.h"

// The record that registers S14 RedLight with the editor.
//
// The claim is .text 0xC7898 to 0xC7930 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void s14RedLightLoad(void);
extern "C" void s14RedLightUnload(void);
extern "C" void s14RedLightCreate(void);
extern "C" ObjectEntry s14RedLightEntry;
extern "C" char s14RedLightDisplayName[];

extern "C" void s14RedLightRegister(void)
{
	s14RedLightEntry.flags = 0;
	s14RedLightEntry.unk18 = 0;

	s14RedLightEntry.name   = s14RedLightDisplayName;
	s14RedLightEntry.load   = s14RedLightLoad;
	s14RedLightEntry.unload = s14RedLightUnload;
	s14RedLightEntry.create = s14RedLightCreate;
	s14RedLightEntry.reset  = NULL;

	s14RedLightEntry.flags = 0x1000;
	s14RedLightEntry.unk18 = 0;
	s14RedLightEntry.unk20 = 0x14;
	s14RedLightEntry.unk1C = 0x1485;
	s14RedLightEntry.unk1E = 2;
	s14RedLightEntry.unk21 = 0;

	s14RedLightEntry.fieldTypes = NULL;
	s14RedLightEntry.fieldNames = NULL;

	if (s14RedLightEntry.fieldTypes != NULL) {
		s14RedLightEntry.flags |= 8;
	} else {
		s14RedLightEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14RedLightCtorEntry)(void) = s14RedLightRegister;
