#include "types.h"

// The record that registers PROPELLER (TObjPropeller07, rel/propeller07_create.cpp) with the editor.
//
// The claim is .text 0x7E38C to 0x7E42C and the .ctors word that names it.
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
extern "C" void propeller07Load(void);
extern "C" void propeller07Unload(void);
extern "C" void propeller07Create(void);
extern "C" void propeller07Reset(void);
extern "C" ObjectEntry propeller07Entry;
extern "C" char propeller07DisplayName[];

extern "C" void propeller07Register(void)
{
	propeller07Entry.flags = 0;
	propeller07Entry.unk18 = 0;

	propeller07Entry.name   = propeller07DisplayName;
	propeller07Entry.load   = propeller07Load;
	propeller07Entry.unload = propeller07Unload;
	propeller07Entry.create = propeller07Create;
	propeller07Entry.reset  = propeller07Reset;

	propeller07Entry.flags = 0x1000;
	propeller07Entry.unk18 = 0;
	propeller07Entry.unk20 = 0xf;
	propeller07Entry.unk1C = 0x790;
	propeller07Entry.unk1E = 2;
	propeller07Entry.unk21 = 0;

	propeller07Entry.fieldTypes = NULL;
	propeller07Entry.fieldNames = NULL;

	if (propeller07Entry.fieldTypes != NULL) {
		propeller07Entry.flags |= 8;
	} else {
		propeller07Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const propeller07CtorEntry)(void) = propeller07Register;
