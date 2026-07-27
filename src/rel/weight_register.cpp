#include "types.h"

// The record that registers WEIGHT OBJECT with the editor.
//
// The claim is .text 0x28C34 to 0x28CDC and the .ctors word that names it. Only the
// record is taken: the three hooks it points at stay assembly and are reached
// by the names each module's symbols.txt gives them.
//
// The run is the same in twelve of the fourteen stage modules. stage13D is
// built from a different revision here, and stage40D everywhere.
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
extern "C" void weightLoad(void);
extern "C" void weightUnload(void);
extern "C" void weightCreate(void);
extern "C" ObjectEntry weightEntry;
extern "C" char weightDisplayName[];
extern "C" char weightFieldTypes[];
extern "C" const char* weightFieldNames[];

extern "C" void weightRegister(void)
{
	weightEntry.flags = 0;
	weightEntry.unk18 = 0;

	weightEntry.name   = weightDisplayName;
	weightEntry.load   = weightLoad;
	weightEntry.unload = weightUnload;
	weightEntry.create = weightCreate;
	weightEntry.unk10  = NULL;

	weightEntry.flags = 0x20000;
	weightEntry.unk18 = 0;
	weightEntry.unk20 = 0x1E;
	weightEntry.unk1C = 0x13;
	weightEntry.unk1E = 2;
	weightEntry.unk21 = 0;

	weightEntry.fieldTypes = weightFieldTypes;
	weightEntry.fieldNames = weightFieldNames;

	if (weightFieldTypes != NULL) {
		weightEntry.flags |= 8;
	} else {
		weightEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const weightCtorEntry)(void) = weightRegister;
