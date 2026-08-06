#include "types.h"

// The record that registers S13 MISSILEPOD with the editor.
//
// The claim is .text 0x867F4 to 0x86890 and the .ctors word that names it.
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
extern "C" void s13MissilepodLoad(void);
extern "C" void s13MissilepodUnload(void);
extern "C" void s13MissilepodCreate(void);
extern "C" ObjectEntry s13MissilepodEntry;
extern "C" char s13MissilepodDisplayName[];

extern "C" void s13MissilepodRegister(void)
{
	s13MissilepodEntry.flags = 0;
	s13MissilepodEntry.unk18 = 0;

	s13MissilepodEntry.name   = s13MissilepodDisplayName;
	s13MissilepodEntry.load   = s13MissilepodLoad;
	s13MissilepodEntry.unload = s13MissilepodUnload;
	s13MissilepodEntry.create = s13MissilepodCreate;
	s13MissilepodEntry.reset  = NULL;

	s13MissilepodEntry.flags = 0x21000;
	s13MissilepodEntry.unk18 = 0;
	s13MissilepodEntry.unk20 = 0xa;
	s13MissilepodEntry.unk1C = 0x1381;
	s13MissilepodEntry.unk1E = 2;
	s13MissilepodEntry.unk21 = 0;

	s13MissilepodEntry.fieldTypes = NULL;
	s13MissilepodEntry.fieldNames = NULL;

	if (s13MissilepodEntry.fieldTypes != NULL) {
		s13MissilepodEntry.flags |= 8;
	} else {
		s13MissilepodEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13MissilepodCtorEntry)(void) = s13MissilepodRegister;
