#include "types.h"

// The record that registers TRAINCAPSULE with the editor.
//
// The claim is .text 0x8F7A8 to 0x8F858 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cc" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage07D carries this run.

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
extern "C" void traincapsuleLoad(void);
extern "C" void traincapsuleUnload(void);
extern "C" void traincapsuleCreate(void);
extern "C" void traincapsuleReset(void);
extern "C" ObjectEntry traincapsuleEntry;
extern "C" char traincapsuleDisplayName[];
extern "C" char traincapsuleFieldTypes[];
extern "C" const char* traincapsuleFieldNames[];

extern "C" void traincapsuleRegister(void)
{
	traincapsuleEntry.flags = 0;
	traincapsuleEntry.unk18 = 0;

	traincapsuleEntry.name   = traincapsuleDisplayName;
	traincapsuleEntry.load   = traincapsuleLoad;
	traincapsuleEntry.unload = traincapsuleUnload;
	traincapsuleEntry.create = traincapsuleCreate;
	traincapsuleEntry.reset  = traincapsuleReset;

	traincapsuleEntry.flags = 0x20000;
	traincapsuleEntry.unk18 = 0;
	traincapsuleEntry.unk20 = 0xf;
	traincapsuleEntry.unk1C = 0x705;
	traincapsuleEntry.unk1E = 2;
	traincapsuleEntry.unk21 = 0;

	traincapsuleEntry.fieldTypes = traincapsuleFieldTypes;
	traincapsuleEntry.fieldNames = traincapsuleFieldNames;

	if (traincapsuleFieldTypes != NULL) {
		traincapsuleEntry.flags |= 8;
	} else {
		traincapsuleEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const traincapsuleCtorEntry)(void) = traincapsuleRegister;
