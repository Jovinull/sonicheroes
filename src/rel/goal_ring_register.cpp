#include "types.h"

// The record that registers GOALRING OBJECT with the editor.
//
// The claim is .text 0x4D584 to 0x4D62C and the .ctors word that names it. Only the
// record is taken: the three hooks it points at stay assembly and are reached
// by the names each module's symbols.txt gives them.
//
// The run is the same in thirteen of the fourteen stage modules. stage40D
// registers the same object from a different build and does not share it.
//
// This class exposes no editable parameters, so its type string is empty.

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
extern "C" void goalRingLoad(void);
extern "C" void goalRingUnload(void);
extern "C" void goalRingCreate(void);
extern "C" ObjectEntry goalRingEntry;
extern "C" char goalRingDisplayName[];
extern "C" char goalRingFieldTypes[];
extern "C" const char* goalRingFieldNames[];

extern "C" void goalRingRegister(void)
{
	goalRingEntry.flags = 0;
	goalRingEntry.unk18 = 0;

	goalRingEntry.name   = goalRingDisplayName;
	goalRingEntry.load   = goalRingLoad;
	goalRingEntry.unload = goalRingUnload;
	goalRingEntry.create = goalRingCreate;
	goalRingEntry.unk10  = NULL;

	goalRingEntry.flags = 0x20000;
	goalRingEntry.unk18 = 0;
	goalRingEntry.unk20 = 0x1E;
	goalRingEntry.unk1C = 0x1B;
	goalRingEntry.unk1E = 2;
	goalRingEntry.unk21 = 0;

	goalRingEntry.fieldTypes = goalRingFieldTypes;
	goalRingEntry.fieldNames = goalRingFieldNames;

	if (goalRingFieldTypes != NULL) {
		goalRingEntry.flags |= 8;
	} else {
		goalRingEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const goalRingCtorEntry)(void) = goalRingRegister;
