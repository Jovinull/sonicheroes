#include "types.h"

// The record that registers S13D SCREW with the editor.
//
// The claim is .text 0x87C1C to 0x87CB8 and the .ctors word that names it.
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
extern "C" void s13dScrewLoad(void);
extern "C" void s13dScrewUnload(void);
extern "C" void s13dScrewCreate(void);
extern "C" ObjectEntry s13dScrewEntry;
extern "C" char s13dScrewDisplayName[];

extern "C" void s13dScrewRegister(void)
{
	s13dScrewEntry.flags = 0;
	s13dScrewEntry.unk18 = 0;

	s13dScrewEntry.name   = s13dScrewDisplayName;
	s13dScrewEntry.load   = s13dScrewLoad;
	s13dScrewEntry.unload = s13dScrewUnload;
	s13dScrewEntry.create = s13dScrewCreate;
	s13dScrewEntry.reset  = NULL;

	s13dScrewEntry.flags = 0x21000;
	s13dScrewEntry.unk18 = 0;
	s13dScrewEntry.unk20 = 0xd;
	s13dScrewEntry.unk1C = 0x1382;
	s13dScrewEntry.unk1E = 2;
	s13dScrewEntry.unk21 = 0;

	s13dScrewEntry.fieldTypes = NULL;
	s13dScrewEntry.fieldNames = NULL;

	if (s13dScrewEntry.fieldTypes != NULL) {
		s13dScrewEntry.flags |= 8;
	} else {
		s13dScrewEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13dScrewCtorEntry)(void) = s13dScrewRegister;
