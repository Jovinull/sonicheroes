#include "types.h"

// The record that registers S03 SignBoard with the editor.
//
// The claim is .text 0xACE44 to 0xACEE0 and the .ctors word that names it.
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
extern "C" void s03SignBoardLoad(void);
extern "C" void s03SignBoardUnload(void);
extern "C" void s03SignBoardCreate(void);
extern "C" ObjectEntry s03SignBoardEntry;
extern "C" char s03SignBoardDisplayName[];

extern "C" void s03SignBoardRegister(void)
{
	s03SignBoardEntry.flags = 0;
	s03SignBoardEntry.unk18 = 0;

	s03SignBoardEntry.name   = s03SignBoardDisplayName;
	s03SignBoardEntry.load   = s03SignBoardLoad;
	s03SignBoardEntry.unload = s03SignBoardUnload;
	s03SignBoardEntry.create = s03SignBoardCreate;
	s03SignBoardEntry.reset  = NULL;

	s03SignBoardEntry.flags = 0x21000;
	s03SignBoardEntry.unk18 = 0;
	s03SignBoardEntry.unk20 = 0x14;
	s03SignBoardEntry.unk1C = 0x386;
	s03SignBoardEntry.unk1E = 2;
	s03SignBoardEntry.unk21 = 0;

	s03SignBoardEntry.fieldTypes = NULL;
	s03SignBoardEntry.fieldNames = NULL;

	if (s03SignBoardEntry.fieldTypes != NULL) {
		s03SignBoardEntry.flags |= 8;
	} else {
		s03SignBoardEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03SignBoardCtorEntry)(void) = s03SignBoardRegister;
