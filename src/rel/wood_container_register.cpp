#include "types.h"

// The record that registers WOOD. CONT. OBJECT with the editor.
//
// The claim is .text 0x140F0 to 0x14198 and the .ctors word that names it. Only the
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
extern "C" void woodContainerLoad(void);
extern "C" void woodContainerUnload(void);
extern "C" void woodContainerCreate(void);
extern "C" ObjectEntry woodContainerEntry;
extern "C" char woodContainerDisplayName[];
extern "C" char woodContainerFieldTypes[];
extern "C" const char* containerFieldNames[];

extern "C" void woodContainerRegister(void)
{
	woodContainerEntry.flags = 0;
	woodContainerEntry.unk18 = 0;

	woodContainerEntry.name   = woodContainerDisplayName;
	woodContainerEntry.load   = woodContainerLoad;
	woodContainerEntry.unload = woodContainerUnload;
	woodContainerEntry.create = woodContainerCreate;
	woodContainerEntry.unk10  = NULL;

	woodContainerEntry.flags = 0x20000;
	woodContainerEntry.unk18 = 0;
	woodContainerEntry.unk20 = 0x1E;
	woodContainerEntry.unk1C = 0x20;
	woodContainerEntry.unk1E = 2;
	woodContainerEntry.unk21 = 0;

	woodContainerEntry.fieldTypes = woodContainerFieldTypes;
	woodContainerEntry.fieldNames = containerFieldNames;

	if (woodContainerFieldTypes != NULL) {
		woodContainerEntry.flags |= 8;
	} else {
		woodContainerEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const woodContainerCtorEntry)(void) = woodContainerRegister;
