#include "types.h"

// The record that registers S14D EGGMAN with the editor.
//
// The claim is .text 0xD3CF4 to 0xD3D90 and the .ctors word that names it.
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
extern "C" void s14dEggmanLoad(void);
extern "C" void s14dEggmanUnload(void);
extern "C" void s14dEggmanCreate(void);
extern "C" ObjectEntry s14dEggmanEntry;
extern "C" char s14dEggmanDisplayName[];

extern "C" void s14dEggmanRegister(void)
{
	s14dEggmanEntry.flags = 0;
	s14dEggmanEntry.unk18 = 0;

	s14dEggmanEntry.name   = s14dEggmanDisplayName;
	s14dEggmanEntry.load   = s14dEggmanLoad;
	s14dEggmanEntry.unload = s14dEggmanUnload;
	s14dEggmanEntry.create = s14dEggmanCreate;
	s14dEggmanEntry.reset  = NULL;

	s14dEggmanEntry.flags = 0x21000;
	s14dEggmanEntry.unk18 = 0;
	s14dEggmanEntry.unk20 = 0x64;
	s14dEggmanEntry.unk1C = 0x1496;
	s14dEggmanEntry.unk1E = 2;
	s14dEggmanEntry.unk21 = 0;

	s14dEggmanEntry.fieldTypes = NULL;
	s14dEggmanEntry.fieldNames = NULL;

	if (s14dEggmanEntry.fieldTypes != NULL) {
		s14dEggmanEntry.flags |= 8;
	} else {
		s14dEggmanEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14dEggmanCtorEntry)(void) = s14dEggmanRegister;
