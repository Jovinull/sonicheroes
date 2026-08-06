#include "types.h"

// The record that registers TRAINAPPEAR with the editor.
//
// The claim is .text 0x8E78C to 0x8E83C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "Fii" is the field type string: one character per parameter the
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
extern "C" void trainappearLoad(void);
extern "C" void trainappearUnload(void);
extern "C" void trainappearCreate(void);
extern "C" void trainappearReset(void);
extern "C" ObjectEntry trainappearEntry;
extern "C" char trainappearDisplayName[];
extern "C" char trainappearFieldTypes[];
extern "C" const char* trainappearFieldNames[];

extern "C" void trainappearRegister(void)
{
	trainappearEntry.flags = 0;
	trainappearEntry.unk18 = 0;

	trainappearEntry.name   = trainappearDisplayName;
	trainappearEntry.load   = trainappearLoad;
	trainappearEntry.unload = trainappearUnload;
	trainappearEntry.create = trainappearCreate;
	trainappearEntry.reset  = trainappearReset;

	trainappearEntry.flags = 0x1000;
	trainappearEntry.unk18 = 0;
	trainappearEntry.unk20 = 0xf;
	trainappearEntry.unk1C = 0x795;
	trainappearEntry.unk1E = 2;
	trainappearEntry.unk21 = 0;

	trainappearEntry.fieldTypes = trainappearFieldTypes;
	trainappearEntry.fieldNames = trainappearFieldNames;

	if (trainappearFieldTypes != NULL) {
		trainappearEntry.flags |= 8;
	} else {
		trainappearEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const trainappearCtorEntry)(void) = trainappearRegister;
