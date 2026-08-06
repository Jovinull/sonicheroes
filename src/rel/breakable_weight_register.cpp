#include "types.h"

// The record that registers BREAKABLEWEIGHTOBJECT with the editor.
//
// The claim is .text 0x2C958 to 0x2CA00 and the .ctors word that names it. Only the
// record is taken: the three hooks it points at stay assembly and are reached
// by the names each module's symbols.txt gives them.
//
// The run is the same in thirteen of the fourteen stage modules. stage40D
// registers the same object from a different build and does not share it.
//
// "cCsffssf" is the field type string: one character per parameter the editor
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
extern "C" void breakableWeightLoad(void);
extern "C" void breakableWeightUnload(void);
extern "C" void breakableWeightCreate(void);
extern "C" ObjectEntry breakableWeightEntry;
extern "C" char breakableWeightDisplayName[];
extern "C" char breakableWeightFieldTypes[];
extern "C" const char* breakableWeightFieldNames[];

extern "C" void breakableWeightRegister(void)
{
	breakableWeightEntry.flags = 0;
	breakableWeightEntry.unk18 = 0;

	breakableWeightEntry.name   = breakableWeightDisplayName;
	breakableWeightEntry.load   = breakableWeightLoad;
	breakableWeightEntry.unload = breakableWeightUnload;
	breakableWeightEntry.create = breakableWeightCreate;
	breakableWeightEntry.unk10  = NULL;

	breakableWeightEntry.flags = 0x20000;
	breakableWeightEntry.unk18 = 0;
	breakableWeightEntry.unk20 = 0x1E;
	breakableWeightEntry.unk1C = 0x14;
	breakableWeightEntry.unk1E = 2;
	breakableWeightEntry.unk21 = 0;

	breakableWeightEntry.fieldTypes = breakableWeightFieldTypes;
	breakableWeightEntry.fieldNames = breakableWeightFieldNames;

	if (breakableWeightFieldTypes != NULL) {
		breakableWeightEntry.flags |= 8;
	} else {
		breakableWeightEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const breakableWeightCtorEntry)(void) = breakableWeightRegister;
