#include "types.h"

// The record that registers S03D Light with the editor.
//
// The claim is .text 0x7E99C to 0x7EA44 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cfff" is the field type string: one character per parameter the
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
extern "C" void s03dLightLoad(void);
extern "C" void s03dLightUnload(void);
extern "C" void s03dLightCreate(void);
extern "C" ObjectEntry s03dLightEntry;
extern "C" char s03dLightDisplayName[];
extern "C" char s03dLightFieldTypes[];
extern "C" const char* s03dLightFieldNames[];

extern "C" void s03dLightRegister(void)
{
	s03dLightEntry.flags = 0;
	s03dLightEntry.unk18 = 0;

	s03dLightEntry.name   = s03dLightDisplayName;
	s03dLightEntry.load   = s03dLightLoad;
	s03dLightEntry.unload = s03dLightUnload;
	s03dLightEntry.create = s03dLightCreate;
	s03dLightEntry.reset  = NULL;

	s03dLightEntry.flags = 0x20000;
	s03dLightEntry.unk18 = 0;
	s03dLightEntry.unk20 = 0xa;
	s03dLightEntry.unk1C = 0x385;
	s03dLightEntry.unk1E = 4098;
	s03dLightEntry.unk21 = 0;

	s03dLightEntry.fieldTypes = s03dLightFieldTypes;
	s03dLightEntry.fieldNames = s03dLightFieldNames;

	if (s03dLightFieldTypes != NULL) {
		s03dLightEntry.flags |= 8;
	} else {
		s03dLightEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03dLightCtorEntry)(void) = s03dLightRegister;
