#include "types.h"

// TObjSwitch's factory and the record that registers the class.
//
// The claim is .text 0x4E50 to 0x4F48 and the .ctors word that names the
// registration. It stops at 0x4F48 rather than carrying on: what follows is the
// adjustor thunk into the parameter guard, and a tail call is not something the
// compiler emits from C.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out, as everywhere
// else.
//
// The record is the same shape every TObj* fills in, with two differences worth
// noting against the spring's: this class uses the fourth hook slot, which the
// others leave null, and its flags start at 0x8000000 rather than 0x20000.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void (*reset)(void*);    // 0x10
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
extern "C" void* switchCtor(void* object, void* owner);
extern "C" void switchLoad(void);
extern "C" void switchUnload(void);
extern "C" void switchReset(void* object);
extern "C" ObjectEntry switchEntry;
extern "C" char switchDisplayName[];
extern "C" char switchFieldTypes[];
extern "C" const char* switchLabels[];

extern "C" void switchCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		switchCtor(memory, lbl_8042C110);
	}
}

extern "C" void switchRegister(void)
{
	switchEntry.flags = 0;
	switchEntry.unk18 = 0;

	switchEntry.name   = switchDisplayName;
	switchEntry.load   = switchLoad;
	switchEntry.unload = switchUnload;
	switchEntry.create = switchCreate;
	switchEntry.reset  = switchReset;

	switchEntry.flags = 0x8000000;
	switchEntry.unk18 = 0;
	switchEntry.unk20 = 0x1E;
	switchEntry.unk1C = 5;
	switchEntry.unk1E = 2;
	switchEntry.unk21 = 0;

	switchEntry.fieldTypes = switchFieldTypes;
	switchEntry.fieldNames = switchLabels;

	if (switchFieldTypes != NULL) {
		switchEntry.flags |= 8;
	} else {
		switchEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const switchCtorEntry)(void) = switchRegister;
