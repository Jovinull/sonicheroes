#include "types.h"

// REEL OBJECT's factory and the record that registers the class.
//
// The claim is .text 0x12128 to 0x12218 and the .ctors word that names the
// registration. Both are the shape every TObj* in the module repeats: allocate
// 0xF8 bytes and hand them to the constructor, then fill a 0x2C record in .bss
// with the display name, the three hooks and the editor's field layout.
//
// The run is the same in twelve of the fourteen stage modules. stage13D is
// built from a different revision here, and stage40D everywhere, so both are
// left out.
//
// "fffs" is the field type string: one character per parameter the editor
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
extern "C" void* reelCtor(void* object, void* owner);
extern "C" void reelLoad(void);
extern "C" void reelUnload(void);
extern "C" ObjectEntry reelEntry;
extern "C" char reelDisplayName[];
extern "C" char reelFieldTypes[];
extern "C" const char* reelFieldNames[];

extern "C" void reelCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0xF8);

	if (memory != NULL) {
		reelCtor(memory, lbl_8042C110);
	}
}

extern "C" void reelRegister(void)
{
	reelEntry.flags = 0;
	reelEntry.unk18 = 0;

	reelEntry.name   = reelDisplayName;
	reelEntry.load   = reelLoad;
	reelEntry.unload = reelUnload;
	reelEntry.create = reelCreate;
	reelEntry.unk10  = NULL;

	reelEntry.flags = 0x20000;
	reelEntry.unk18 = 0;
	reelEntry.unk20 = 0x1E;
	reelEntry.unk1C = 0x1D;
	reelEntry.unk1E = 2;
	reelEntry.unk21 = 0;

	reelEntry.fieldTypes = reelFieldTypes;
	reelEntry.fieldNames = reelFieldNames;

	if (reelFieldTypes != NULL) {
		reelEntry.flags |= 8;
	} else {
		reelEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const reelCtorEntry)(void) = reelRegister;
