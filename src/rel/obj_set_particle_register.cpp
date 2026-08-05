#include "types.h"

// The record that registers OBJ SetParticle  with the editor.
//
// The claim is .text 0xAF398 to 0xAF434 and the .ctors word at 0x128 that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// It carries editor fields, so the type and label slots are filled. The flags word is 0x21000.
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

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void objSetparticleCreate(void);
extern "C" ObjectEntry objSetparticleEntry;
extern "C" char objSetparticleDisplayName[];
extern "C" char objSetparticleFieldTypes[];
extern "C" const char* objSetparticleFieldNames[];

extern "C" void objSetparticleRegister(void)
{
	objSetparticleEntry.flags = 0;
	objSetparticleEntry.unk18 = 0;

	objSetparticleEntry.name   = objSetparticleDisplayName;
	objSetparticleEntry.load   = NULL;
	objSetparticleEntry.unload = NULL;
	objSetparticleEntry.create = objSetparticleCreate;
	objSetparticleEntry.reset  = NULL;

	objSetparticleEntry.flags = 0x21000;
	objSetparticleEntry.unk18 = 0;
	objSetparticleEntry.unk20 = 20;
	objSetparticleEntry.unk1C = 511;
	objSetparticleEntry.unk1E = 2;
	objSetparticleEntry.unk21 = 0;

	objSetparticleEntry.fieldTypes = objSetparticleFieldTypes;
	objSetparticleEntry.fieldNames = objSetparticleFieldNames;

	if (objSetparticleEntry.fieldTypes != NULL) {
		objSetparticleEntry.flags |= 8;
	} else {
		objSetparticleEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const objSetparticleCtorEntry)(void) = objSetparticleRegister;
