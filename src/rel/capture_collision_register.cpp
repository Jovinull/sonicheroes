#include "types.h"

// The record that registers CAPTURE COLLISION with the editor.
//
// The claim is .text 0xA8AEC to 0xA8B94 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in six of the fourteen stage modules: 05D, 07D, 09D, 11D, 13D and 26D.

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
extern "C" void captureCollisionLoad(void);
extern "C" void captureCollisionUnload(void);
extern "C" void captureCollisionCreate(void);
extern "C" ObjectEntry captureCollisionEntry;
extern "C" char captureCollisionDisplayName[];
extern "C" char captureCollisionFieldTypes[];
extern "C" const char* captureCollisionFieldNames[];

extern "C" void captureCollisionRegister(void)
{
	captureCollisionEntry.flags = 0;
	captureCollisionEntry.unk18 = 0;

	captureCollisionEntry.name   = captureCollisionDisplayName;
	captureCollisionEntry.load   = captureCollisionLoad;
	captureCollisionEntry.unload = captureCollisionUnload;
	captureCollisionEntry.create = captureCollisionCreate;
	captureCollisionEntry.reset  = NULL;

	captureCollisionEntry.flags = 0x20000;
	captureCollisionEntry.unk18 = 0;
	captureCollisionEntry.unk20 = 0x1e;
	captureCollisionEntry.unk1C = 0x65;
	captureCollisionEntry.unk1E = 4;
	captureCollisionEntry.unk21 = 0;

	captureCollisionEntry.fieldTypes = captureCollisionFieldTypes;
	captureCollisionEntry.fieldNames = captureCollisionFieldNames;

	if (captureCollisionFieldTypes != NULL) {
		captureCollisionEntry.flags |= 8;
	} else {
		captureCollisionEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const captureCollisionCtorEntry)(void)
    = captureCollisionRegister;
