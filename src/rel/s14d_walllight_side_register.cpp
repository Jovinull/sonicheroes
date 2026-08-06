#include "types.h"

// The records that register S14D WALLLIGHT SIDE and S14D WALLLIGHT FRONT with the editor.
//
// The claim is .text 0xCD498 to 0xCD5C4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
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
extern "C" void s14dWalllightSideLoad(void);
extern "C" void s14dWalllightSideUnload(void);
extern "C" void s14dWalllightSideCreate(void);
extern "C" ObjectEntry s14dWalllightSideEntry;
extern "C" char s14dWalllightSideDisplayName[];

extern "C" void s14dWalllightFrontCreate(void);
extern "C" ObjectEntry s14dWalllightFrontEntry;
extern "C" char s14dWalllightFrontDisplayName[];

extern "C" void s14dWalllightSideRegister(void)
{
	s14dWalllightSideEntry.flags = 0;
	s14dWalllightSideEntry.unk18 = 0;

	s14dWalllightSideEntry.name   = s14dWalllightSideDisplayName;
	s14dWalllightSideEntry.load   = s14dWalllightSideLoad;
	s14dWalllightSideEntry.unload = s14dWalllightSideUnload;
	s14dWalllightSideEntry.create = s14dWalllightSideCreate;
	s14dWalllightSideEntry.reset  = NULL;

	s14dWalllightSideEntry.flags = 0x1000;
	s14dWalllightSideEntry.unk18 = 0;
	s14dWalllightSideEntry.unk20 = 0x7f;
	s14dWalllightSideEntry.unk1C = 0x148b;
	s14dWalllightSideEntry.unk1E = 2;
	s14dWalllightSideEntry.unk21 = 0x0;

	s14dWalllightSideEntry.fieldTypes = NULL;
	s14dWalllightSideEntry.fieldNames = NULL;

	if (s14dWalllightSideEntry.fieldTypes != NULL) {
		s14dWalllightSideEntry.flags |= 8;
	} else {
		s14dWalllightSideEntry.flags &= ~8;
	}

	s14dWalllightFrontEntry.flags = 0;
	s14dWalllightFrontEntry.unk18 = 0;

	s14dWalllightFrontEntry.name   = s14dWalllightFrontDisplayName;
	s14dWalllightFrontEntry.load   = s14dWalllightSideLoad;
	s14dWalllightFrontEntry.unload = s14dWalllightSideUnload;
	s14dWalllightFrontEntry.create = s14dWalllightFrontCreate;
	s14dWalllightFrontEntry.reset  = NULL;

	s14dWalllightFrontEntry.flags = 0x1000;
	s14dWalllightFrontEntry.unk18 = 0;
	s14dWalllightFrontEntry.unk20 = 0x7f;
	s14dWalllightFrontEntry.unk1C = 0x148c;
	s14dWalllightFrontEntry.unk1E = 2;
	s14dWalllightFrontEntry.unk21 = 0x0;

	s14dWalllightFrontEntry.fieldTypes = NULL;
	s14dWalllightFrontEntry.fieldNames = NULL;

	if (s14dWalllightFrontEntry.fieldTypes != NULL) {
		s14dWalllightFrontEntry.flags |= 8;
	} else {
		s14dWalllightFrontEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14dWalllightSideCtorEntry)(void)
    = s14dWalllightSideRegister;
