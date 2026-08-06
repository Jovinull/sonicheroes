#include "types.h"

// The record that registers TRAINROLLTUNNEL with the editor.
//
// The claim is .text 0xCB384 to 0xCB438 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
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
extern "C" void trainrolltunnelLoad(void);
extern "C" void trainrolltunnelUnload(void);
extern "C" void trainrolltunnelCreate(void);
extern "C" void trainrolltunnelReset(void);
extern "C" ObjectEntry trainrolltunnelEntry;
extern "C" char trainrolltunnelDisplayName[];
extern "C" char trainrolltunnelFieldTypes[];
extern "C" const char* trainrolltunnelFieldNames[];

extern "C" void trainrolltunnelRegister(void)
{
	trainrolltunnelEntry.flags = 0;
	trainrolltunnelEntry.unk18 = 0;

	trainrolltunnelEntry.name   = trainrolltunnelDisplayName;
	trainrolltunnelEntry.load   = trainrolltunnelLoad;
	trainrolltunnelEntry.unload = trainrolltunnelUnload;
	trainrolltunnelEntry.create = trainrolltunnelCreate;
	trainrolltunnelEntry.reset  = trainrolltunnelReset;

	trainrolltunnelEntry.flags = 0x20400;
	trainrolltunnelEntry.unk18 = 0;
	trainrolltunnelEntry.unk20 = 0x14;
	trainrolltunnelEntry.unk1C = 0x72c;
	trainrolltunnelEntry.unk1E = 2;
	trainrolltunnelEntry.unk21 = 0;

	trainrolltunnelEntry.fieldTypes = trainrolltunnelFieldTypes;
	trainrolltunnelEntry.fieldNames = trainrolltunnelFieldNames;

	if (trainrolltunnelFieldTypes != NULL) {
		trainrolltunnelEntry.flags |= 8;
	} else {
		trainrolltunnelEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const trainrolltunnelCtorEntry)(void) = trainrolltunnelRegister;
