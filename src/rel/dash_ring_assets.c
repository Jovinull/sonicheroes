#include "types.h"

// DASHRING OBJECT's factory and the record that registers the class.
//
// The claim is .text 0xE32C to 0xE41C and the .ctors word that names the
// registration. Both are the shape every TObj* in the module repeats: allocate
// 0x6C bytes and hand them to the constructor, then fill a 0x2C record in .bss
// with the display name, the three hooks and the editor's field layout.
//
// The run is the same in twelve of the fourteen stage modules. stage13D is
// built from a different revision here, and stage40D everywhere, so both are
// left out.
//
// "fs" is the field type string: one character per parameter the editor
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

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* fn_80018A34(void* heap, u32 size);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* dashRingCtor(void* object, void* owner);
extern "C" void dashRingLoad(void);
extern "C" void dashRingUnload(void);
extern "C" ObjectEntry dashRingEntry;
extern "C" char dashRingDisplayName[];
extern "C" char dashRingFieldTypes[];
extern "C" const char* dashRingFieldNames[];

extern "C" void dashRingCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0x6C);

	if (memory != NULL) {
		dashRingCtor(memory, lbl_8042C110);
	}
}

extern "C" void dashRingRegister(void)
{
	dashRingEntry.flags = 0;
	dashRingEntry.unk18 = 0;

	dashRingEntry.name   = dashRingDisplayName;
	dashRingEntry.load   = dashRingLoad;
	dashRingEntry.unload = dashRingUnload;
	dashRingEntry.create = dashRingCreate;
	dashRingEntry.unk10  = NULL;

	dashRingEntry.flags = 0x20000;
	dashRingEntry.unk18 = 0;
	dashRingEntry.unk20 = 0x1E;
	dashRingEntry.unk1C = 0xC;
	dashRingEntry.unk1E = 2;
	dashRingEntry.unk21 = 0;

	dashRingEntry.fieldTypes = dashRingFieldTypes;
	dashRingEntry.fieldNames = dashRingFieldNames;

	if (dashRingFieldTypes != NULL) {
		dashRingEntry.flags |= 8;
	} else {
		dashRingEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const dashRingCtorEntry)(void) = dashRingRegister;
