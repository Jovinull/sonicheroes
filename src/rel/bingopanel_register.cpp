#include "types.h"

// The record that registers BINGOPANEL with the editor.
//
// The claim is .text 0x81CE4 to 0x81D94 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
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
extern "C" void bingopanelLoad(void);
extern "C" void bingopanelUnload(void);
extern "C" void bingopanelCreate(void);
extern "C" void bingopanelReset(void);
extern "C" ObjectEntry bingopanelEntry;
extern "C" char bingopanelDisplayName[];
extern "C" char bingopanelFieldTypes[];
extern "C" const char* bingopanelFieldNames[];

extern "C" void bingopanelRegister(void)
{
	bingopanelEntry.flags = 0;
	bingopanelEntry.unk18 = 0;

	bingopanelEntry.name   = bingopanelDisplayName;
	bingopanelEntry.load   = bingopanelLoad;
	bingopanelEntry.unload = bingopanelUnload;
	bingopanelEntry.create = bingopanelCreate;
	bingopanelEntry.reset  = bingopanelReset;

	bingopanelEntry.flags = 0x20000;
	bingopanelEntry.unk18 = 0;
	bingopanelEntry.unk20 = 0xf;
	bingopanelEntry.unk1C = 0x50d;
	bingopanelEntry.unk1E = 2;
	bingopanelEntry.unk21 = 0;

	bingopanelEntry.fieldTypes = bingopanelFieldTypes;
	bingopanelEntry.fieldNames = bingopanelFieldNames;

	if (bingopanelFieldTypes != NULL) {
		bingopanelEntry.flags |= 8;
	} else {
		bingopanelEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const bingopanelCtorEntry)(void) = bingopanelRegister;
