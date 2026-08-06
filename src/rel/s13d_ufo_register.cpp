#include "types.h"

// The record that registers S13D UFO with the editor.
//
// The claim is .text 0x96518 to 0x965C0 and the .ctors word that names it.
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
extern "C" void s13dUfoLoad(void);
extern "C" void s13dUfoUnload(void);
extern "C" void s13dUfoCreate(void);
extern "C" ObjectEntry s13dUfoEntry;
extern "C" char s13dUfoDisplayName[];
extern "C" char s13dUfoFieldTypes[];
extern "C" const char* s13dUfoFieldNames[];

extern "C" void s13dUfoRegister(void)
{
	s13dUfoEntry.flags = 0;
	s13dUfoEntry.unk18 = 0;

	s13dUfoEntry.name   = s13dUfoDisplayName;
	s13dUfoEntry.load   = s13dUfoLoad;
	s13dUfoEntry.unload = s13dUfoUnload;
	s13dUfoEntry.create = s13dUfoCreate;
	s13dUfoEntry.reset  = NULL;

	s13dUfoEntry.flags = 0x1000;
	s13dUfoEntry.unk18 = 0;
	s13dUfoEntry.unk20 = 0xa;
	s13dUfoEntry.unk1C = 0x1384;
	s13dUfoEntry.unk1E = 2;
	s13dUfoEntry.unk21 = 0;

	s13dUfoEntry.fieldTypes = s13dUfoFieldTypes;
	s13dUfoEntry.fieldNames = s13dUfoFieldNames;

	if (s13dUfoFieldTypes != NULL) {
		s13dUfoEntry.flags |= 8;
	} else {
		s13dUfoEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13dUfoCtorEntry)(void) = s13dUfoRegister;
