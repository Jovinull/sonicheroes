#include "types.h"

// The record that registers TENKYU with the editor.
//
// The claim is .text 0xC9CD4 to 0xC9D74 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
//
// Only stage05D carries this run.

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
extern "C" void tenkyuLoad(void);
extern "C" void tenkyuUnload(void);
extern "C" void tenkyuCreate(void);
extern "C" void tenkyuReset(void);
extern "C" ObjectEntry tenkyuEntry;
extern "C" char tenkyuDisplayName[];

extern "C" void tenkyuRegister(void)
{
	tenkyuEntry.flags = 0;
	tenkyuEntry.unk18 = 0;

	tenkyuEntry.name   = tenkyuDisplayName;
	tenkyuEntry.load   = tenkyuLoad;
	tenkyuEntry.unload = tenkyuUnload;
	tenkyuEntry.create = tenkyuCreate;
	tenkyuEntry.reset  = tenkyuReset;

	tenkyuEntry.flags = 0x1400;
	tenkyuEntry.unk18 = 0;
	tenkyuEntry.unk20 = 0xf;
	tenkyuEntry.unk1C = 0x588;
	tenkyuEntry.unk1E = 2;
	tenkyuEntry.unk21 = 0;

	tenkyuEntry.fieldTypes = NULL;
	tenkyuEntry.fieldNames = NULL;

	if (tenkyuEntry.fieldTypes != NULL) {
		tenkyuEntry.flags |= 8;
	} else {
		tenkyuEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const tenkyuCtorEntry)(void) = tenkyuRegister;
