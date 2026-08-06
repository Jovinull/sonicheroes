#include "types.h"

// The record that registers S14 KOWARE with the editor.
//
// The claim is .text 0x9EAFC to 0x9EBA4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "f" is the field type string: one character per parameter the
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
extern "C" void s14KowareLoad(void);
extern "C" void s14KowareUnload(void);
extern "C" void s14KowareCreate(void);
extern "C" ObjectEntry s14KowareEntry;
extern "C" char s14KowareDisplayName[];
extern "C" char s14KowareFieldTypes[];
extern "C" const char* s14KowareFieldNames[];

extern "C" void s14KowareRegister(void)
{
	s14KowareEntry.flags = 0;
	s14KowareEntry.unk18 = 0;

	s14KowareEntry.name   = s14KowareDisplayName;
	s14KowareEntry.load   = s14KowareLoad;
	s14KowareEntry.unload = s14KowareUnload;
	s14KowareEntry.create = s14KowareCreate;
	s14KowareEntry.reset  = NULL;

	s14KowareEntry.flags = 0x20000;
	s14KowareEntry.unk18 = 0;
	s14KowareEntry.unk20 = 0x32;
	s14KowareEntry.unk1C = 0x1406;
	s14KowareEntry.unk1E = 2;
	s14KowareEntry.unk21 = 0;

	s14KowareEntry.fieldTypes = s14KowareFieldTypes;
	s14KowareEntry.fieldNames = s14KowareFieldNames;

	if (s14KowareFieldTypes != NULL) {
		s14KowareEntry.flags |= 8;
	} else {
		s14KowareEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14KowareCtorEntry)(void) = s14KowareRegister;
