#include "types.h"

// The record that registers S02D MovingLand with the editor.
//
// The claim is .text 0x9F2CC to 0x9F378 and the .ctors word at 0x118 that names
// it. Only the record is taken: the three hooks it points at stay assembly and
// are reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// The .ctors slot is derived rather than guessed. Every function that owns a
// .ctors word was collected from the module's relocations and sorted by run
// address; the slot is that position times four. The rule reproduces all fifty
// slots already claimed in this module and contradicts none.
//
// Only stage01D carries this run, like the other stage-02 object records around
// it.

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
extern "C" void s02MovingLandLoad(void);
extern "C" void s02MovingLandUnload(void);
extern "C" void s02MovingLandCreate(void);
extern "C" ObjectEntry s02MovingLandEntry;
extern "C" char s02MovingLandDisplayName[];
extern "C" char s02MovingLandFieldTypes[];
extern "C" const char* s02MovingLandFieldNames[];

extern "C" void s02MovingLandRegister(void)
{
	s02MovingLandEntry.flags = 0;
	s02MovingLandEntry.unk18 = 0;

	s02MovingLandEntry.name   = s02MovingLandDisplayName;
	s02MovingLandEntry.load   = s02MovingLandLoad;
	s02MovingLandEntry.unload = s02MovingLandUnload;
	s02MovingLandEntry.create = s02MovingLandCreate;
	s02MovingLandEntry.unk10  = NULL;

	s02MovingLandEntry.flags = 0x21400;
	s02MovingLandEntry.unk18 = 0;
	s02MovingLandEntry.unk20 = 50;
	s02MovingLandEntry.unk1C = 640;
	s02MovingLandEntry.unk1E = 2;
	s02MovingLandEntry.unk21 = 0;

	s02MovingLandEntry.fieldTypes = s02MovingLandFieldTypes;
	s02MovingLandEntry.fieldNames = s02MovingLandFieldNames;

	if (s02MovingLandFieldTypes != NULL) {
		s02MovingLandEntry.flags |= 8;
	} else {
		s02MovingLandEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s02MovingLandCtorEntry)(void) = s02MovingLandRegister;
