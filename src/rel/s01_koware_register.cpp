#include "types.h"

// The record that registers S01 Koware with the editor.
//
// The claim is .text 0x85F54 to 0x85FEC and the .ctors word at 0xE0 that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// It shows no editor fields, so the type and label slots take NULL and
// the trailing test folds bit 3 out rather than in.
//
// The .ctors slot is derived: every function owning a .ctors word, sorted by run
// address, at position times four.
//
// Only stage01D carries this run.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void* unk10;             // 0x10
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

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void s01KowareLoad(void);
extern "C" void s01KowareUnload(void);
extern "C" void s01KowareCreate(void);
extern "C" ObjectEntry s01KowareEntry;
extern "C" char s01KowareDisplayName[];

extern "C" void s01KowareRegister(void)
{
	s01KowareEntry.flags = 0;
	s01KowareEntry.unk18 = 0;

	s01KowareEntry.name   = s01KowareDisplayName;
	s01KowareEntry.load   = s01KowareLoad;
	s01KowareEntry.unload = s01KowareUnload;
	s01KowareEntry.create = s01KowareCreate;
	s01KowareEntry.unk10  = NULL;

	s01KowareEntry.flags = 0x20000;
	s01KowareEntry.unk18 = 0;
	s01KowareEntry.unk20 = 50;
	s01KowareEntry.unk1C = 260;
	s01KowareEntry.unk1E = 2;
	s01KowareEntry.unk21 = 0;

	s01KowareEntry.fieldTypes = NULL;
	s01KowareEntry.fieldNames = NULL;

	if (s01KowareEntry.fieldTypes != NULL) {
		s01KowareEntry.flags |= 8;
	} else {
		s01KowareEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s01KowareCtorEntry)(void) = s01KowareRegister;
