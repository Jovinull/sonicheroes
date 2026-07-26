#include "types.h"

// TARGET OBJECT's factory and the record that registers the class.
//
// The claim is .text 0x240DC to 0x241CC and the .ctors word that names the
// registration. Both are the shape every TObj* in the module repeats: allocate
// 0xF0 bytes and hand them to the constructor, then fill a 0x2C record in .bss
// with the display name, the three hooks and the editor's field layout.
//
// The run is the same in twelve of the fourteen stage modules. stage13D is
// built from a different revision here, and stage40D everywhere, so both are
// left out.
//
// "ccC" is the field type string: one character per parameter the editor
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
extern "C" void* targetCtor(void* object, void* owner);
extern "C" void targetLoad(void);
extern "C" void targetUnload(void);
extern "C" ObjectEntry targetEntry;
extern "C" char targetDisplayName[];
extern "C" char targetFieldTypes[];
extern "C" const char* targetFieldNames[];

extern "C" void targetCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0xF0);

	if (memory != NULL) {
		targetCtor(memory, lbl_8042C110);
	}
}

extern "C" void targetRegister(void)
{
	targetEntry.flags = 0;
	targetEntry.unk18 = 0;

	targetEntry.name   = targetDisplayName;
	targetEntry.load   = targetLoad;
	targetEntry.unload = targetUnload;
	targetEntry.create = targetCreate;
	targetEntry.unk10  = NULL;

	targetEntry.flags = 0x8000000;
	targetEntry.unk18 = 0;
	targetEntry.unk20 = 0x1E;
	targetEntry.unk1C = 0x7;
	targetEntry.unk1E = 2;
	targetEntry.unk21 = 0;

	targetEntry.fieldTypes = targetFieldTypes;
	targetEntry.fieldNames = targetFieldNames;

	if (targetFieldTypes != NULL) {
		targetEntry.flags |= 8;
	} else {
		targetEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const targetCtorEntry)(void) = targetRegister;
