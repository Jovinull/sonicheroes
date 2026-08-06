#include "types.h"

// The record that registers S14D UFO with the editor.
//
// The claim is .text 0xCBFFC to 0xCC0A4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "x" is the field type string: one character per parameter the
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
extern "C" void s14dUfoLoad(void);
extern "C" void s14dUfoUnload(void);
extern "C" void s14dUfoCreate(void);
extern "C" ObjectEntry s14dUfoEntry;
extern "C" char s14dUfoDisplayName[];
extern "C" char s14dUfoFieldTypes[];
extern "C" const char* s14dUfoFieldNames[];

extern "C" void s14dUfoRegister(void)
{
	s14dUfoEntry.flags = 0;
	s14dUfoEntry.unk18 = 0;

	s14dUfoEntry.name   = s14dUfoDisplayName;
	s14dUfoEntry.load   = s14dUfoLoad;
	s14dUfoEntry.unload = s14dUfoUnload;
	s14dUfoEntry.create = s14dUfoCreate;
	s14dUfoEntry.reset  = NULL;

	s14dUfoEntry.flags = 0x1000;
	s14dUfoEntry.unk18 = 0;
	s14dUfoEntry.unk20 = 0xa;
	s14dUfoEntry.unk1C = 0x1488;
	s14dUfoEntry.unk1E = 2;
	s14dUfoEntry.unk21 = 0;

	s14dUfoEntry.fieldTypes = s14dUfoFieldTypes;
	s14dUfoEntry.fieldNames = s14dUfoFieldNames;

	if (s14dUfoFieldTypes != NULL) {
		s14dUfoEntry.flags |= 8;
	} else {
		s14dUfoEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14dUfoCtorEntry)(void) = s14dUfoRegister;
