#include "types.h"

// The record that registers JUMPPANEL OBJECT with the editor.
//
// The claim is .text 0xCFB4 to 0xD05C and the .ctors word that names it. Only the
// record is taken: the three hooks it points at stay assembly and are reached
// by the names each module's symbols.txt gives them.
//
// The run is the same in twelve of the fourteen stage modules. stage13D is
// built from a different revision here, and stage40D everywhere.
//
// "ffs" is the field type string: one character per parameter the editor
// shows, and the array beside it holds their labels.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void* unk10;             // 0x10
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
extern "C" void jumpPanelLoad(void);
extern "C" void jumpPanelUnload(void);
extern "C" void jumpPanelCreate(void);
extern "C" ObjectEntry jumpPanelEntry;
extern "C" char jumpPanelDisplayName[];
extern "C" char jumpPanelFieldTypes[];
extern "C" const char* jumpPanelFieldNames[];

extern "C" void jumpPanelRegister(void)
{
	jumpPanelEntry.flags = 0;
	jumpPanelEntry.unk18 = 0;

	jumpPanelEntry.name   = jumpPanelDisplayName;
	jumpPanelEntry.load   = jumpPanelLoad;
	jumpPanelEntry.unload = jumpPanelUnload;
	jumpPanelEntry.create = jumpPanelCreate;
	jumpPanelEntry.unk10  = NULL;

	jumpPanelEntry.flags = 0x20000;
	jumpPanelEntry.unk18 = 0;
	jumpPanelEntry.unk20 = 0x1E;
	jumpPanelEntry.unk1C = 0xF;
	jumpPanelEntry.unk1E = 2;
	jumpPanelEntry.unk21 = 0;

	jumpPanelEntry.fieldTypes = jumpPanelFieldTypes;
	jumpPanelEntry.fieldNames = jumpPanelFieldNames;

	if (jumpPanelFieldTypes != NULL) {
		jumpPanelEntry.flags |= 8;
	} else {
		jumpPanelEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const jumpPanelCtorEntry)(void) = jumpPanelRegister;
