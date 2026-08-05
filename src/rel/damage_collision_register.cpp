#include "types.h"

// The record that registers DAMAGE COLLISION with the editor.
//
// The claim is .text 0x70D50 to 0x70DE8 and the .ctors word at 0xBC that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// It installs no load or unload hook, only a create one, so those two
// slots take NULL.
//
// The .ctors slot is derived: every function owning a .ctors word, sorted by run
// address, at position times four.
//
// Only stage01D carries this run.

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

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void damageCollisionCreate(void);
extern "C" ObjectEntry damageCollisionEntry;
extern "C" char damageCollisionDisplayName[];
extern "C" char damageCollisionFieldTypes[];
extern "C" const char* damageCollisionFieldNames[];

extern "C" void damageCollisionRegister(void)
{
	damageCollisionEntry.flags = 0;
	damageCollisionEntry.unk18 = 0;

	damageCollisionEntry.name   = damageCollisionDisplayName;
	damageCollisionEntry.load   = NULL;
	damageCollisionEntry.unload = NULL;
	damageCollisionEntry.create = damageCollisionCreate;
	damageCollisionEntry.unk10  = NULL;

	damageCollisionEntry.flags = 0x20000;
	damageCollisionEntry.unk18 = 0;
	damageCollisionEntry.unk20 = 30;
	damageCollisionEntry.unk1C = 100;
	damageCollisionEntry.unk1E = 2;
	damageCollisionEntry.unk21 = 0;

	damageCollisionEntry.fieldTypes = damageCollisionFieldTypes;
	damageCollisionEntry.fieldNames = damageCollisionFieldNames;

	if (damageCollisionEntry.fieldTypes != NULL) {
		damageCollisionEntry.flags |= 8;
	} else {
		damageCollisionEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const damageCollisionCtorEntry)(void) = damageCollisionRegister;
