#include "types.h"

// The record that registers LIGHT COLLISION with the editor.
//
// The claim is .text 0x4F2E4 to 0x4F37C and the .ctors word that names it. Only the
// record is taken: the hooks it points at stay assembly and are reached by the
// names each module's symbols.txt gives them.
//
// The run is the same in thirteen of the fourteen stage modules. stage40D
// registers the same object from a different build and does not share it.
//
// This class has only a factory: nothing to load or unload, and no reset
// hook. Its byte at 0x20 is 0x32 rather than the 0x1E the others use.

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
extern "C" void lightCollisionCreate(void);
extern "C" ObjectEntry lightCollisionEntry;
extern "C" char lightCollisionDisplayName[];
extern "C" char lightCollisionFieldTypes[];
extern "C" const char* lightCollisionFieldNames[];

extern "C" void lightCollisionRegister(void)
{
	lightCollisionEntry.flags = 0;
	lightCollisionEntry.unk18 = 0;

	lightCollisionEntry.name   = lightCollisionDisplayName;
	lightCollisionEntry.load   = NULL;
	lightCollisionEntry.unload = NULL;
	lightCollisionEntry.create = lightCollisionCreate;
	lightCollisionEntry.reset  = NULL;

	lightCollisionEntry.flags = 0x1000;
	lightCollisionEntry.unk18 = 0;
	lightCollisionEntry.unk20 = 0x32;
	lightCollisionEntry.unk1C = 0x59;
	lightCollisionEntry.unk1E = 2;
	lightCollisionEntry.unk21 = 0;

	lightCollisionEntry.fieldTypes = lightCollisionFieldTypes;
	lightCollisionEntry.fieldNames = lightCollisionFieldNames;

	if (lightCollisionFieldTypes != NULL) {
		lightCollisionEntry.flags |= 8;
	} else {
		lightCollisionEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const lightCollisionCtorEntry)(void) = lightCollisionRegister;
