#include "types.h"

// The record that registers S14D Crush with the editor.
//
// The claim is .text 0xD5A08 to 0xD5AA4 and the .ctors word that names it.
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
extern "C" void s14dCrushLoad(void);
extern "C" void s14dCrushUnload(void);
extern "C" void s14dCrushCreate(void);
extern "C" ObjectEntry s14dCrushEntry;
extern "C" char s14dCrushDisplayName[];

extern "C" void s14dCrushRegister(void)
{
	s14dCrushEntry.flags = 0;
	s14dCrushEntry.unk18 = 0;

	s14dCrushEntry.name   = s14dCrushDisplayName;
	s14dCrushEntry.load   = s14dCrushLoad;
	s14dCrushEntry.unload = s14dCrushUnload;
	s14dCrushEntry.create = s14dCrushCreate;
	s14dCrushEntry.reset  = NULL;

	s14dCrushEntry.flags = 0x21000;
	s14dCrushEntry.unk18 = 0;
	s14dCrushEntry.unk20 = 0x64;
	s14dCrushEntry.unk1C = 0x1497;
	s14dCrushEntry.unk1E = 2;
	s14dCrushEntry.unk21 = 0;

	s14dCrushEntry.fieldTypes = NULL;
	s14dCrushEntry.fieldNames = NULL;

	if (s14dCrushEntry.fieldTypes != NULL) {
		s14dCrushEntry.flags |= 8;
	} else {
		s14dCrushEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14dCrushCtorEntry)(void) = s14dCrushRegister;
