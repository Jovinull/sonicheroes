#include "types.h"

// The record that registers S13 DESIGN PIPE with the editor.
//
// The claim is .text 0x88508 to 0x885A0 and the .ctors word that names it.
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
extern "C" void s13DesignPipeLoad(void);
extern "C" void s13DesignPipeUnload(void);
extern "C" void s13DesignPipeCreate(void);
extern "C" ObjectEntry s13DesignPipeEntry;
extern "C" char s13DesignPipeDisplayName[];

extern "C" void s13DesignPipeRegister(void)
{
	s13DesignPipeEntry.flags = 0;
	s13DesignPipeEntry.unk18 = 0;

	s13DesignPipeEntry.name   = s13DesignPipeDisplayName;
	s13DesignPipeEntry.load   = s13DesignPipeLoad;
	s13DesignPipeEntry.unload = s13DesignPipeUnload;
	s13DesignPipeEntry.create = s13DesignPipeCreate;
	s13DesignPipeEntry.reset  = NULL;

	s13DesignPipeEntry.flags = 0x20000;
	s13DesignPipeEntry.unk18 = 0;
	s13DesignPipeEntry.unk20 = 0x17;
	s13DesignPipeEntry.unk1C = 0x1383;
	s13DesignPipeEntry.unk1E = 2;
	s13DesignPipeEntry.unk21 = 0;

	s13DesignPipeEntry.fieldTypes = NULL;
	s13DesignPipeEntry.fieldNames = NULL;

	if (s13DesignPipeEntry.fieldTypes != NULL) {
		s13DesignPipeEntry.flags |= 8;
	} else {
		s13DesignPipeEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13DesignPipeCtorEntry)(void) = s13DesignPipeRegister;
