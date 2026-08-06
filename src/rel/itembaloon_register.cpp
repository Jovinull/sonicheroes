#include "types.h"

// The records that register ITEMBALOON OBJECT and SCROLLLITEM OBJECT with the
// editor.
//
// The claim is .text 0x3D244 to 0x3D390 and the .ctors word that names it. Only
// the records are taken: the hooks they point at stay assembly and are reached
// by the names each module's symbols.txt gives them.
//
// The run is the same in thirteen of the fourteen stage modules. stage40D
// registers the same objects from a different build and does not share it.
//
// One function fills two records, the same shape rel/ring_register.cpp has. The
// two classes share their load and unload hooks and differ only in the factory,
// the editor fields and the class index. Neither installs a reset hook, so the
// slot at 0x10 takes the zero the flags were cleared with.
//
// "cf" and "cFFFFFssss" are the field type strings: one character per parameter
// the editor shows, and the array beside each holds their labels.

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
extern "C" void itembaloonObjectLoad(void);
extern "C" void itembaloonObjectUnload(void);
extern "C" void itembaloonObjectCreate(void);
extern "C" void scrolllitemObjectCreate(void);

extern "C" ObjectEntry itembaloonObjectEntry;
extern "C" char itembaloonObjectDisplayName[];
extern "C" char itembaloonObjectFieldTypes[];
extern "C" const char* itembaloonObjectFieldNames[];

extern "C" ObjectEntry scrolllitemObjectEntry;
extern "C" char scrolllitemObjectDisplayName[];
extern "C" char scrolllitemObjectFieldTypes[];
extern "C" const char* scrolllitemObjectFieldNames[];

extern "C" void itembaloonObjectRegister(void)
{
	itembaloonObjectEntry.flags = 0;
	itembaloonObjectEntry.unk18 = 0;

	itembaloonObjectEntry.name   = itembaloonObjectDisplayName;
	itembaloonObjectEntry.load   = itembaloonObjectLoad;
	itembaloonObjectEntry.unload = itembaloonObjectUnload;
	itembaloonObjectEntry.create = itembaloonObjectCreate;
	itembaloonObjectEntry.reset  = NULL;

	itembaloonObjectEntry.flags = 0x20000;
	itembaloonObjectEntry.unk18 = 0;
	itembaloonObjectEntry.unk20 = 0x1E;
	itembaloonObjectEntry.unk1C = 0x19;
	itembaloonObjectEntry.unk1E = 2;
	itembaloonObjectEntry.unk21 = 0;

	itembaloonObjectEntry.fieldTypes = itembaloonObjectFieldTypes;
	itembaloonObjectEntry.fieldNames = itembaloonObjectFieldNames;

	if (itembaloonObjectFieldTypes != NULL) {
		itembaloonObjectEntry.flags |= 8;
	} else {
		itembaloonObjectEntry.flags &= ~8;
	}

	scrolllitemObjectEntry.flags = 0;
	scrolllitemObjectEntry.unk18 = 0;

	scrolllitemObjectEntry.name   = scrolllitemObjectDisplayName;
	scrolllitemObjectEntry.load   = itembaloonObjectLoad;
	scrolllitemObjectEntry.unload = itembaloonObjectUnload;
	scrolllitemObjectEntry.create = scrolllitemObjectCreate;
	scrolllitemObjectEntry.reset  = NULL;

	scrolllitemObjectEntry.flags = 0x20000;
	scrolllitemObjectEntry.unk18 = 0;
	scrolllitemObjectEntry.unk20 = 0x1E;
	scrolllitemObjectEntry.unk1C = 0x206;
	scrolllitemObjectEntry.unk1E = 2;
	scrolllitemObjectEntry.unk21 = 0;

	scrolllitemObjectEntry.fieldTypes = scrolllitemObjectFieldTypes;
	scrolllitemObjectEntry.fieldNames = scrolllitemObjectFieldNames;

	if (scrolllitemObjectFieldTypes != NULL) {
		scrolllitemObjectEntry.flags |= 8;
	} else {
		scrolllitemObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const itembaloonObjectCtorEntry)(void)
    = itembaloonObjectRegister;
