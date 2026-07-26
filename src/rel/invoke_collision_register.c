#include "types.h"

// The record that registers INVOKE COLLI with the editor.
//
// The claim is .text 0x4FBFC to 0x4FC90 and the .ctors word that names it. Only the
// record is taken: the hooks it points at stay assembly and are reached by the
// names each module's symbols.txt gives them.
//
// The run is the same in nine of the fourteen stage modules. stage13D, 26D, 27D
// and 28D are a different revision this far in, and stage40D everywhere.
//
// Same shape as LIGHT COLLISION, factory only, and its flags start at zero
// rather than at a bit pattern.

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
extern "C" void invokeCollisionCreate(void);
extern "C" ObjectEntry invokeCollisionEntry;
extern "C" char invokeCollisionDisplayName[];
extern "C" char invokeCollisionFieldTypes[];
extern "C" const char* invokeCollisionFieldNames[];

extern "C" void invokeCollisionRegister(void)
{
	invokeCollisionEntry.flags = 0;
	invokeCollisionEntry.unk18 = 0;

	invokeCollisionEntry.name   = invokeCollisionDisplayName;
	invokeCollisionEntry.load   = NULL;
	invokeCollisionEntry.unload = NULL;
	invokeCollisionEntry.create = invokeCollisionCreate;
	invokeCollisionEntry.reset  = NULL;

	invokeCollisionEntry.flags = 0x0;
	invokeCollisionEntry.unk18 = 0;
	invokeCollisionEntry.unk20 = 0x32;
	invokeCollisionEntry.unk1C = 0x20B;
	invokeCollisionEntry.unk1E = 2;
	invokeCollisionEntry.unk21 = 0;

	invokeCollisionEntry.fieldTypes = invokeCollisionFieldTypes;
	invokeCollisionEntry.fieldNames = invokeCollisionFieldNames;

	if (invokeCollisionFieldTypes != NULL) {
		invokeCollisionEntry.flags |= 8;
	} else {
		invokeCollisionEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const invokeCollisionCtorEntry)(void) = invokeCollisionRegister;
