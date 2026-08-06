#include "types.h"

// The record that registers PUSH/PULL SWITCH with the editor.
//
// The claim is .text 0x5191C to 0x519CC and the .ctors word that names it. Only the
// record is taken: the hooks it points at stay assembly and are reached by the
// names each module's symbols.txt gives them.
//
// The run is the same in thirteen of the fourteen stage modules. stage40D
// registers the same object from a different build and does not share it.
//
// This class uses the fourth hook slot, which most of the others leave null.

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
extern "C" void pushPullSwitchLoad(void);
extern "C" void pushPullSwitchUnload(void);
extern "C" void pushPullSwitchCreate(void);
extern "C" void pushPullSwitchReset(void);
extern "C" ObjectEntry pushPullSwitchEntry;
extern "C" char pushPullSwitchDisplayName[];
extern "C" char pushPullSwitchFieldTypes[];
extern "C" const char* pushPullSwitchFieldNames[];

extern "C" void pushPullSwitchRegister(void)
{
	pushPullSwitchEntry.flags = 0;
	pushPullSwitchEntry.unk18 = 0;

	pushPullSwitchEntry.name   = pushPullSwitchDisplayName;
	pushPullSwitchEntry.load   = pushPullSwitchLoad;
	pushPullSwitchEntry.unload = pushPullSwitchUnload;
	pushPullSwitchEntry.create = pushPullSwitchCreate;
	pushPullSwitchEntry.reset  = pushPullSwitchReset;

	pushPullSwitchEntry.flags = 0x8000000;
	pushPullSwitchEntry.unk18 = 0;
	pushPullSwitchEntry.unk20 = 0x1E;
	pushPullSwitchEntry.unk1C = 0x6;
	pushPullSwitchEntry.unk1E = 2;
	pushPullSwitchEntry.unk21 = 0;

	pushPullSwitchEntry.fieldTypes = pushPullSwitchFieldTypes;
	pushPullSwitchEntry.fieldNames = pushPullSwitchFieldNames;

	if (pushPullSwitchFieldTypes != NULL) {
		pushPullSwitchEntry.flags |= 8;
	} else {
		pushPullSwitchEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const pushPullSwitchCtorEntry)(void) = pushPullSwitchRegister;
