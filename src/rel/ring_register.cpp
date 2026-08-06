#include "types.h"

// The records that register RING OBJECT and SCROLL RING OBJECT with the editor.
//
// The claim is .text 0xBD38 to 0xBE94 and the .ctors word that names it. Only
// the records are taken: the hooks they point at stay assembly and are reached
// by the names each module's symbols.txt gives them.
//
// The run is the same in thirteen of the fourteen stage modules. stage40D
// registers the same objects from a different build and does not share it.
//
// One function fills two records. The two classes share their load, unload and
// reset hooks and differ only in the factory, the editor fields and the flags,
// which is why the compiler emits the second fill straight after the first
// instead of a second constructor: the branch out of the first record's flag
// test jumps to the second record's first store rather than to a return.
//
// "ssff" and "ssffxsssssf" are the field type strings: one character per
// parameter the editor shows, and the array beside each holds their labels.

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
extern "C" void ringObjectLoad(void);
extern "C" void ringObjectUnload(void);
extern "C" void ringObjectCreate(void);
extern "C" void ringObjectReset(void);
extern "C" void scrollRingCreate(void);

extern "C" ObjectEntry ringObjectEntry;
extern "C" char ringObjectDisplayName[];
extern "C" char ringObjectFieldTypes[];
extern "C" const char* ringObjectFieldNames[];

extern "C" ObjectEntry scrollRingObjectEntry;
extern "C" char scrollRingObjectDisplayName[];
extern "C" char scrollRingObjectFieldTypes[];
extern "C" const char* scrollRingObjectFieldNames[];

extern "C" void ringObjectRegister(void)
{
	ringObjectEntry.flags = 0;
	ringObjectEntry.unk18 = 0;

	ringObjectEntry.name   = ringObjectDisplayName;
	ringObjectEntry.load   = ringObjectLoad;
	ringObjectEntry.unload = ringObjectUnload;
	ringObjectEntry.create = ringObjectCreate;
	ringObjectEntry.reset  = ringObjectReset;

	ringObjectEntry.flags = 0x8020000;
	ringObjectEntry.unk18 = 0;
	ringObjectEntry.unk20 = 0x1E;
	ringObjectEntry.unk1C = 3;
	ringObjectEntry.unk1E = 2;
	ringObjectEntry.unk21 = 0;

	ringObjectEntry.fieldTypes = ringObjectFieldTypes;
	ringObjectEntry.fieldNames = ringObjectFieldNames;

	if (ringObjectFieldTypes != NULL) {
		ringObjectEntry.flags |= 8;
	} else {
		ringObjectEntry.flags &= ~8;
	}

	scrollRingObjectEntry.flags = 0;
	scrollRingObjectEntry.unk18 = 0;

	scrollRingObjectEntry.name   = scrollRingObjectDisplayName;
	scrollRingObjectEntry.load   = ringObjectLoad;
	scrollRingObjectEntry.unload = ringObjectUnload;
	scrollRingObjectEntry.create = scrollRingCreate;
	scrollRingObjectEntry.reset  = ringObjectReset;

	scrollRingObjectEntry.flags = 0x20000;
	scrollRingObjectEntry.unk18 = 0;
	scrollRingObjectEntry.unk20 = 0x1E;
	scrollRingObjectEntry.unk1C = 0x207;
	scrollRingObjectEntry.unk1E = 2;
	scrollRingObjectEntry.unk21 = 0;

	scrollRingObjectEntry.fieldTypes = scrollRingObjectFieldTypes;
	scrollRingObjectEntry.fieldNames = scrollRingObjectFieldNames;

	if (scrollRingObjectFieldTypes != NULL) {
		scrollRingObjectEntry.flags |= 8;
	} else {
		scrollRingObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const ringObjectCtorEntry)(void) = ringObjectRegister;
