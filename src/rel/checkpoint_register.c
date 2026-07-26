#include "types.h"

// The record that registers CHECKPOINT OBJECT with the editor.
//
// The claim is .text 0x10ACC to 0x10B74 and the .ctors word that names it. Only the
// record is taken: the three hooks it points at stay assembly and are reached
// by the names each module's symbols.txt gives them.
//
// The run is the same in twelve of the fourteen stage modules. stage13D is
// built from a different revision here, and stage40D everywhere.
//
// "s" is the field type string: one character per parameter the editor
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
extern "C" void checkpointLoad(void);
extern "C" void checkpointUnload(void);
extern "C" void checkpointCreate(void);
extern "C" ObjectEntry checkpointEntry;
extern "C" char checkpointDisplayName[];
extern "C" char checkpointFieldTypes[];
extern "C" const char* checkpointFieldNames[];

extern "C" void checkpointRegister(void)
{
	checkpointEntry.flags = 0;
	checkpointEntry.unk18 = 0;

	checkpointEntry.name   = checkpointDisplayName;
	checkpointEntry.load   = checkpointLoad;
	checkpointEntry.unload = checkpointUnload;
	checkpointEntry.create = checkpointCreate;
	checkpointEntry.unk10  = NULL;

	checkpointEntry.flags = 0x20000;
	checkpointEntry.unk18 = 0;
	checkpointEntry.unk20 = 0x1E;
	checkpointEntry.unk1C = 0xE;
	checkpointEntry.unk1E = 2;
	checkpointEntry.unk21 = 0;

	checkpointEntry.fieldTypes = checkpointFieldTypes;
	checkpointEntry.fieldNames = checkpointFieldNames;

	if (checkpointFieldTypes != NULL) {
		checkpointEntry.flags |= 8;
	} else {
		checkpointEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const checkpointCtorEntry)(void) = checkpointRegister;
