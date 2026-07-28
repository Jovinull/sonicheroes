#include "types.h"

// The record that registers UNBR. CONT. OBJECT with the editor.
//
// The claim is .text 0x14C9C to 0x14D44 and the .ctors word that names it. Only the
// record is taken: the three hooks it points at stay assembly and are reached
// by the names each module's symbols.txt gives them.
//
// The run is the same in twelve of the fourteen stage modules. stage13D is
// built from a different revision here, and stage40D everywhere.
//
// "s" is the field type string: one character per parameter the editor
// shows. The three container classes are laid out the same and share one
// label array between them.

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

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void unbreakableContainerLoad(void);
extern "C" void unbreakableContainerUnload(void);
extern "C" void unbreakableContainerCreate(void);
extern "C" ObjectEntry unbreakableContainerEntry;
extern "C" char unbreakableContainerDisplayName[];
extern "C" char unbreakableContainerFieldTypes[];
extern "C" const char* containerFieldNames[];

extern "C" void unbreakableContainerRegister(void)
{
	unbreakableContainerEntry.flags = 0;
	unbreakableContainerEntry.unk18 = 0;

	unbreakableContainerEntry.name   = unbreakableContainerDisplayName;
	unbreakableContainerEntry.load   = unbreakableContainerLoad;
	unbreakableContainerEntry.unload = unbreakableContainerUnload;
	unbreakableContainerEntry.create = unbreakableContainerCreate;
	unbreakableContainerEntry.unk10  = NULL;

	unbreakableContainerEntry.flags = 0x20000;
	unbreakableContainerEntry.unk18 = 0;
	unbreakableContainerEntry.unk20 = 0x1E;
	unbreakableContainerEntry.unk1C = 0x22;
	unbreakableContainerEntry.unk1E = 2;
	unbreakableContainerEntry.unk21 = 0;

	unbreakableContainerEntry.fieldTypes = unbreakableContainerFieldTypes;
	unbreakableContainerEntry.fieldNames = containerFieldNames;

	if (unbreakableContainerFieldTypes != NULL) {
		unbreakableContainerEntry.flags |= 8;
	} else {
		unbreakableContainerEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const unbreakableContainerCtorEntry)(void)
    = unbreakableContainerRegister;
