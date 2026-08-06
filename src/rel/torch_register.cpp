#include "types.h"

// The record that registers TORCH with the editor.
//
// The claim is .text 0xC9530 to 0xC95E0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage07D carries this run.

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
extern "C" void torchLoad(void);
extern "C" void torchUnload(void);
extern "C" void torchCreate(void);
extern "C" void torchReset(void);
extern "C" ObjectEntry torchEntry;
extern "C" char torchDisplayName[];
extern "C" char torchFieldTypes[];
extern "C" const char* torchFieldNames[];

extern "C" void torchRegister(void)
{
	torchEntry.flags = 0;
	torchEntry.unk18 = 0;

	torchEntry.name   = torchDisplayName;
	torchEntry.load   = torchLoad;
	torchEntry.unload = torchUnload;
	torchEntry.create = torchCreate;
	torchEntry.reset  = torchReset;

	torchEntry.flags = 0x20000;
	torchEntry.unk18 = 0;
	torchEntry.unk20 = 0x14;
	torchEntry.unk1C = 0x802;
	torchEntry.unk1E = 2;
	torchEntry.unk21 = 0;

	torchEntry.fieldTypes = torchFieldTypes;
	torchEntry.fieldNames = torchFieldNames;

	if (torchFieldTypes != NULL) {
		torchEntry.flags |= 8;
	} else {
		torchEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const torchCtorEntry)(void) = torchRegister;
