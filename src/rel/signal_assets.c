#include "types.h"

// SIGNAL OBJECT's factory and the record that registers the class.
//
// The claim is .text 0x46B24 to 0x46C14 and the .ctors word that names the
// registration. Both are the shape every TObj* in the module repeats: allocate
// 0xFC bytes and hand them to the constructor, then fill a 0x2C record in .bss
// with the display name, the three hooks and the editor's field layout.
//
// The run is the same in nine of the fourteen stage modules. stage13D, 26D, 27D
// and 28D are built from a different revision this far in, and stage40D
// everywhere, so those five are left out.
//
// "c" is the field type string: one character per parameter the editor
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
extern "C" void* signalCtor(void* object, void* owner);
extern "C" void signalLoad(void);
extern "C" void signalUnload(void);
extern "C" ObjectEntry signalEntry;
extern "C" char signalDisplayName[];
extern "C" char signalFieldTypes[];
extern "C" const char* signalFieldNames[];

extern "C" void signalCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		signalCtor(memory, lbl_8042C110);
	}
}

extern "C" void signalRegister(void)
{
	signalEntry.flags = 0;
	signalEntry.unk18 = 0;

	signalEntry.name   = signalDisplayName;
	signalEntry.load   = signalLoad;
	signalEntry.unload = signalUnload;
	signalEntry.create = signalCreate;
	signalEntry.unk10  = NULL;

	signalEntry.flags = 0x20000;
	signalEntry.unk18 = 0;
	signalEntry.unk20 = 0x1E;
	signalEntry.unk1C = 0x25;
	signalEntry.unk1E = 2;
	signalEntry.unk21 = 0;

	signalEntry.fieldTypes = signalFieldTypes;
	signalEntry.fieldNames = signalFieldNames;

	if (signalFieldTypes != NULL) {
		signalEntry.flags |= 8;
	} else {
		signalEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const signalCtorEntry)(void) = signalRegister;
