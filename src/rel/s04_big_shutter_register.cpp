#include "types.h"

// The record that registers S04 BigShutter with the editor.
//
// The claim is .text 0xA6C18 to 0xA6CB4 and the .ctors word that names it.
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
extern "C" void s04BigShutterLoad(void);
extern "C" void s04BigShutterUnload(void);
extern "C" void s04BigShutterCreate(void);
extern "C" ObjectEntry s04BigShutterEntry;
extern "C" char s04BigShutterDisplayName[];

extern "C" void s04BigShutterRegister(void)
{
	s04BigShutterEntry.flags = 0;
	s04BigShutterEntry.unk18 = 0;

	s04BigShutterEntry.name   = s04BigShutterDisplayName;
	s04BigShutterEntry.load   = s04BigShutterLoad;
	s04BigShutterEntry.unload = s04BigShutterUnload;
	s04BigShutterEntry.create = s04BigShutterCreate;
	s04BigShutterEntry.reset  = NULL;

	s04BigShutterEntry.flags = 0x20400;
	s04BigShutterEntry.unk18 = 0;
	s04BigShutterEntry.unk20 = 0xa;
	s04BigShutterEntry.unk1C = 0x486;
	s04BigShutterEntry.unk1E = 2;
	s04BigShutterEntry.unk21 = 0;

	s04BigShutterEntry.fieldTypes = NULL;
	s04BigShutterEntry.fieldNames = NULL;

	if (s04BigShutterEntry.fieldTypes != NULL) {
		s04BigShutterEntry.flags |= 8;
	} else {
		s04BigShutterEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04BigShutterCtorEntry)(void) = s04BigShutterRegister;
