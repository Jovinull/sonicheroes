#include "types.h"

// The record that registers UNBR. BOBCONT. OBJECT with the editor.
//
// The claim is .text 0xD2CB0 to 0xD2D58 and the .ctors word at 0x168 that names
// it. Only the record is taken: the three hooks it points at stay assembly and
// are reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// The flags word is 0x20000, small enough for one instruction, which is the
// whole difference from rel/s66_star_register.cpp's two-instruction load.
//
// The .ctors slot is derived: every function owning a .ctors word, sorted by run
// address, at position times four.
//
// The run is the same in thirteen of the fourteen stage modules. stage40D
// registers the same object from a different build and does not share it.

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

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void unbrBobcontObjectLoad(void);
extern "C" void unbrBobcontObjectUnload(void);
extern "C" void unbrBobcontObjectCreate(void);
extern "C" ObjectEntry unbrBobcontObjectEntry;
extern "C" char unbrBobcontObjectDisplayName[];
extern "C" char unbrBobcontObjectFieldTypes[];
extern "C" const char* unbrBobcontObjectFieldNames[];

extern "C" void unbrBobcontObjectRegister(void)
{
	unbrBobcontObjectEntry.flags = 0;
	unbrBobcontObjectEntry.unk18 = 0;

	unbrBobcontObjectEntry.name   = unbrBobcontObjectDisplayName;
	unbrBobcontObjectEntry.load   = unbrBobcontObjectLoad;
	unbrBobcontObjectEntry.unload = unbrBobcontObjectUnload;
	unbrBobcontObjectEntry.create = unbrBobcontObjectCreate;
	unbrBobcontObjectEntry.unk10  = NULL;

	unbrBobcontObjectEntry.flags = 0x20000;
	unbrBobcontObjectEntry.unk18 = 0;
	unbrBobcontObjectEntry.unk20 = 30;
	unbrBobcontObjectEntry.unk1C = 13056;
	unbrBobcontObjectEntry.unk1E = 2;
	unbrBobcontObjectEntry.unk21 = 0;

	unbrBobcontObjectEntry.fieldTypes = unbrBobcontObjectFieldTypes;
	unbrBobcontObjectEntry.fieldNames = unbrBobcontObjectFieldNames;

	if (unbrBobcontObjectFieldTypes != NULL) {
		unbrBobcontObjectEntry.flags |= 8;
	} else {
		unbrBobcontObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const unbrBobcontObjectCtorEntry)(void)
    = unbrBobcontObjectRegister;
