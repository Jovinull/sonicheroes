#include "types.h"

// The record that registers TObjDashpanel with the editor.
//
// The claim is .text 0x8578 to 0x8620 and the .ctors word that names it. It
// stops there rather than carrying on: what follows is the adjustor thunk into
// the parameter guard, and a tail call is not something the compiler emits from
// C.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out, as everywhere
// else.
//
// "fs" is the field type string: a float and a halfword, which is the power and
// the no control time the guard in rel/dashpanel_object.cpp bounds.

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
extern "C" void dashpanelLoad(void);
extern "C" void dashpanelUnload(void);
extern "C" void dashpanelCreate(void);
extern "C" ObjectEntry dashpanelEntry;
extern "C" char dashpanelDisplayName[];
extern "C" char dashpanelFieldTypes[];
extern "C" const char* dashpanelFieldNames[];

extern "C" void dashpanelRegister(void)
{
	dashpanelEntry.flags = 0;
	dashpanelEntry.unk18 = 0;

	dashpanelEntry.name   = dashpanelDisplayName;
	dashpanelEntry.load   = dashpanelLoad;
	dashpanelEntry.unload = dashpanelUnload;
	dashpanelEntry.create = dashpanelCreate;
	dashpanelEntry.unk10  = NULL;

	dashpanelEntry.flags = 0x20000;
	dashpanelEntry.unk18 = 0;
	dashpanelEntry.unk20 = 0x1E;
	dashpanelEntry.unk1C = 0xB;
	dashpanelEntry.unk1E = 2;
	dashpanelEntry.unk21 = 0;

	dashpanelEntry.fieldTypes = dashpanelFieldTypes;
	dashpanelEntry.fieldNames = dashpanelFieldNames;

	if (dashpanelFieldTypes != NULL) {
		dashpanelEntry.flags |= 8;
	} else {
		dashpanelEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const dashpanelCtorEntry)(void) = dashpanelRegister;
