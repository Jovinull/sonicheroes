#include "types.h"

// PAWN OBJECT's factory and the record that registers the class.
//
// The claim is .text 0x33C98 to 0x33D88 and the .ctors word that names the
// registration. Both are the shape every TObj* in the module repeats: allocate
// 0x390 bytes and hand them to the constructor, then fill a 0x2C record in .bss
// with the display name, the three hooks and the editor's field layout.
//
// The run is the same in nine of the fourteen stage modules. stage13D, 26D, 27D
// and 28D are built from a different revision this far in, and stage40D
// everywhere, so those five are left out.
//
// This one takes its owner from lbl_8042C10C rather than the lbl_8042C110 the
// other factories use.
//
// "ccccssffffi" is the field type string: one character per parameter the editor
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

extern "C" void* lbl_8042C10C;
extern "C" void* lbl_8042C148;

extern "C" void* fn_80018A34(void* heap, u32 size);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* pawnCtor(void* object, void* owner);
extern "C" void pawnLoad(void);
extern "C" void pawnUnload(void);
extern "C" ObjectEntry pawnEntry;
extern "C" char pawnDisplayName[];
extern "C" char pawnFieldTypes[];
extern "C" const char* pawnFieldNames[];

extern "C" void pawnCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0x390);

	if (memory != NULL) {
		pawnCtor(memory, lbl_8042C10C);
	}
}

extern "C" void pawnRegister(void)
{
	pawnEntry.flags = 0;
	pawnEntry.unk18 = 0;

	pawnEntry.name   = pawnDisplayName;
	pawnEntry.load   = pawnLoad;
	pawnEntry.unload = pawnUnload;
	pawnEntry.create = pawnCreate;
	pawnEntry.unk10  = NULL;

	pawnEntry.flags = 0x20000;
	pawnEntry.unk18 = 0;
	pawnEntry.unk20 = 0x1E;
	pawnEntry.unk1C = 0x1510;
	pawnEntry.unk1E = 4;
	pawnEntry.unk21 = 0;

	pawnEntry.fieldTypes = pawnFieldTypes;
	pawnEntry.fieldNames = pawnFieldNames;

	if (pawnFieldTypes != NULL) {
		pawnEntry.flags |= 8;
	} else {
		pawnEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const pawnCtorEntry)(void) = pawnRegister;
