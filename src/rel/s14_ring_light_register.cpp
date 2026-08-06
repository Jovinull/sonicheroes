#include "types.h"

// The record that registers S14 RingLight with the editor.
//
// The claim is .text 0xC823C to 0xC82D4 and the .ctors word that names it.
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
extern "C" void s14RingLightLoad(void);
extern "C" void s14RingLightUnload(void);
extern "C" void s14RingLightCreate(void);
extern "C" ObjectEntry s14RingLightEntry;
extern "C" char s14RingLightDisplayName[];

extern "C" void s14RingLightRegister(void)
{
	s14RingLightEntry.flags = 0;
	s14RingLightEntry.unk18 = 0;

	s14RingLightEntry.name   = s14RingLightDisplayName;
	s14RingLightEntry.load   = s14RingLightLoad;
	s14RingLightEntry.unload = s14RingLightUnload;
	s14RingLightEntry.create = s14RingLightCreate;
	s14RingLightEntry.reset  = NULL;

	s14RingLightEntry.flags = 0x1400;
	s14RingLightEntry.unk18 = 0;
	s14RingLightEntry.unk20 = 0xa;
	s14RingLightEntry.unk1C = 0x1489;
	s14RingLightEntry.unk1E = 2;
	s14RingLightEntry.unk21 = 0;

	s14RingLightEntry.fieldTypes = NULL;
	s14RingLightEntry.fieldNames = NULL;

	if (s14RingLightEntry.fieldTypes != NULL) {
		s14RingLightEntry.flags |= 8;
	} else {
		s14RingLightEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14RingLightCtorEntry)(void) = s14RingLightRegister;
