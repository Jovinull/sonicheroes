#include "types.h"

// The record that registers S04 Wall with the editor.
//
// The claim is .text 0x9A318 to 0x9A3B4 and the .ctors word that names it.
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
extern "C" void s04WallLoad(void);
extern "C" void s04WallUnload(void);
extern "C" void s04WallCreate(void);
extern "C" ObjectEntry s04WallEntry;
extern "C" char s04WallDisplayName[];

extern "C" void s04WallRegister(void)
{
	s04WallEntry.flags = 0;
	s04WallEntry.unk18 = 0;

	s04WallEntry.name   = s04WallDisplayName;
	s04WallEntry.load   = s04WallLoad;
	s04WallEntry.unload = s04WallUnload;
	s04WallEntry.create = s04WallCreate;
	s04WallEntry.reset  = NULL;

	s04WallEntry.flags = 0x21000;
	s04WallEntry.unk18 = 0;
	s04WallEntry.unk20 = 0x14;
	s04WallEntry.unk1C = 0x481;
	s04WallEntry.unk1E = 2;
	s04WallEntry.unk21 = 0;

	s04WallEntry.fieldTypes = NULL;
	s04WallEntry.fieldNames = NULL;

	if (s04WallEntry.fieldTypes != NULL) {
		s04WallEntry.flags |= 8;
	} else {
		s04WallEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04WallCtorEntry)(void) = s04WallRegister;
