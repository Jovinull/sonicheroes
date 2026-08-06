#include "types.h"

// The record that registers S04 EggCapElev with the editor.
//
// The claim is .text 0x9105C to 0x910F4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void s04EggCapElevLoad(void);
extern "C" void s04EggCapElevUnload(void);
extern "C" void s04EggCapElevCreate(void);
extern "C" ObjectEntry s04EggCapElevEntry;
extern "C" char s04EggCapElevDisplayName[];

extern "C" void s04EggCapElevRegister(void)
{
	s04EggCapElevEntry.flags = 0;
	s04EggCapElevEntry.unk18 = 0;

	s04EggCapElevEntry.name   = s04EggCapElevDisplayName;
	s04EggCapElevEntry.load   = s04EggCapElevLoad;
	s04EggCapElevEntry.unload = s04EggCapElevUnload;
	s04EggCapElevEntry.create = s04EggCapElevCreate;
	s04EggCapElevEntry.reset  = NULL;

	s04EggCapElevEntry.flags = 0x20000;
	s04EggCapElevEntry.unk18 = 0;
	s04EggCapElevEntry.unk20 = 0x14;
	s04EggCapElevEntry.unk1C = 0x413;
	s04EggCapElevEntry.unk1E = 2;
	s04EggCapElevEntry.unk21 = 0;

	s04EggCapElevEntry.fieldTypes = NULL;
	s04EggCapElevEntry.fieldNames = NULL;

	if (s04EggCapElevEntry.fieldTypes != NULL) {
		s04EggCapElevEntry.flags |= 8;
	} else {
		s04EggCapElevEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04EggCapElevCtorEntry)(void) = s04EggCapElevRegister;
