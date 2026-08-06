#include "types.h"

// The record that registers S14D WALL NEON with the editor.
//
// The claim is .text 0xCE574 to 0xCE60C and the .ctors word that names it.
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
extern "C" void s14dWallNeonLoad(void);
extern "C" void s14dWallNeonUnload(void);
extern "C" void s14dWallNeonCreate(void);
extern "C" ObjectEntry s14dWallNeonEntry;
extern "C" char s14dWallNeonDisplayName[];

extern "C" void s14dWallNeonRegister(void)
{
	s14dWallNeonEntry.flags = 0;
	s14dWallNeonEntry.unk18 = 0;

	s14dWallNeonEntry.name   = s14dWallNeonDisplayName;
	s14dWallNeonEntry.load   = s14dWallNeonLoad;
	s14dWallNeonEntry.unload = s14dWallNeonUnload;
	s14dWallNeonEntry.create = s14dWallNeonCreate;
	s14dWallNeonEntry.reset  = NULL;

	s14dWallNeonEntry.flags = 0x1400;
	s14dWallNeonEntry.unk18 = 0;
	s14dWallNeonEntry.unk20 = 0xa;
	s14dWallNeonEntry.unk1C = 0x148a;
	s14dWallNeonEntry.unk1E = 2;
	s14dWallNeonEntry.unk21 = 0;

	s14dWallNeonEntry.fieldTypes = NULL;
	s14dWallNeonEntry.fieldNames = NULL;

	if (s14dWallNeonEntry.fieldTypes != NULL) {
		s14dWallNeonEntry.flags |= 8;
	} else {
		s14dWallNeonEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14dWallNeonCtorEntry)(void) = s14dWallNeonRegister;
