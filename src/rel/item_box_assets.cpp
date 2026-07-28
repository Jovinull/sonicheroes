#include "types.h"

// ITEMBOX OBJECT's factory and the record that registers the class.
//
// The claim is .text 0x3B2CC to 0x3B3BC and the .ctors word that names the
// registration. Both are the shape every TObj* in the module repeats: allocate
// 0xF0 bytes and hand them to the constructor, then fill a 0x2C record in .bss
// with the display name, the three hooks and the editor's field layout.
//
// The run is the same in nine of the fourteen stage modules. stage13D, 26D, 27D
// and 28D are built from a different revision this far in, and stage40D
// everywhere, so those five are left out.
//
// "cc" is the field type string: one character per parameter the editor
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
extern "C" void* itemBoxCtor(void* object, void* owner);
extern "C" void itemBoxLoad(void);
extern "C" void itemBoxUnload(void);
extern "C" ObjectEntry itemBoxEntry;
extern "C" char itemBoxDisplayName[];
extern "C" char itemBoxFieldTypes[];
extern "C" const char* itemBoxFieldNames[];

extern "C" void itemBoxCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0xF0);

	if (memory != NULL) {
		itemBoxCtor(memory, lbl_8042C110);
	}
}

extern "C" void itemBoxRegister(void)
{
	itemBoxEntry.flags = 0;
	itemBoxEntry.unk18 = 0;

	itemBoxEntry.name   = itemBoxDisplayName;
	itemBoxEntry.load   = itemBoxLoad;
	itemBoxEntry.unload = itemBoxUnload;
	itemBoxEntry.create = itemBoxCreate;
	itemBoxEntry.unk10  = NULL;

	itemBoxEntry.flags = 0x20000;
	itemBoxEntry.unk18 = 0;
	itemBoxEntry.unk20 = 0x1E;
	itemBoxEntry.unk1C = 0x18;
	itemBoxEntry.unk1E = 2;
	itemBoxEntry.unk21 = 0;

	itemBoxEntry.fieldTypes = itemBoxFieldTypes;
	itemBoxEntry.fieldNames = itemBoxFieldNames;

	if (itemBoxFieldTypes != NULL) {
		itemBoxEntry.flags |= 8;
	} else {
		itemBoxEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const itemBoxCtorEntry)(void) = itemBoxRegister;
