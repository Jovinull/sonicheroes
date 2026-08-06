#include "types.h"

// The record that registers S14 LaserLight with the editor.
//
// The claim is .text 0xC6168 to 0xC6210 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cc" is the field type string: one character per parameter the
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
extern "C" void s14LaserLightLoad(void);
extern "C" void s14LaserLightUnload(void);
extern "C" void s14LaserLightCreate(void);
extern "C" ObjectEntry s14LaserLightEntry;
extern "C" char s14LaserLightDisplayName[];
extern "C" char s14LaserLightFieldTypes[];
extern "C" const char* s14LaserLightFieldNames[];

extern "C" void s14LaserLightRegister(void)
{
	s14LaserLightEntry.flags = 0;
	s14LaserLightEntry.unk18 = 0;

	s14LaserLightEntry.name   = s14LaserLightDisplayName;
	s14LaserLightEntry.load   = s14LaserLightLoad;
	s14LaserLightEntry.unload = s14LaserLightUnload;
	s14LaserLightEntry.create = s14LaserLightCreate;
	s14LaserLightEntry.reset  = NULL;

	s14LaserLightEntry.flags = 0x1000;
	s14LaserLightEntry.unk18 = 0;
	s14LaserLightEntry.unk20 = 0x1e;
	s14LaserLightEntry.unk1C = 0x1483;
	s14LaserLightEntry.unk1E = 2;
	s14LaserLightEntry.unk21 = 0;

	s14LaserLightEntry.fieldTypes = s14LaserLightFieldTypes;
	s14LaserLightEntry.fieldNames = s14LaserLightFieldNames;

	if (s14LaserLightFieldTypes != NULL) {
		s14LaserLightEntry.flags |= 8;
	} else {
		s14LaserLightEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14LaserLightCtorEntry)(void) = s14LaserLightRegister;
