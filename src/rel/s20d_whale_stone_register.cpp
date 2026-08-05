#include "types.h"

// The record that registers S20D WhaleStone with the editor.
//
// The claim is .text 0xBC130 to 0xBC1DC and the .ctors word at 0x140 that names
// it. Only the record is taken: the three hooks it points at stay assembly and
// are reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// The .ctors slot is derived: every function that owns a .ctors word was
// collected from the module's relocations and sorted by run address, and the
// slot is that position times four. The rule reproduces every slot already
// claimed in this module.
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
extern "C" void s20dWhalestoneLoad(void);
extern "C" void s20dWhalestoneUnload(void);
extern "C" void s20dWhalestoneCreate(void);
extern "C" ObjectEntry s20dWhalestoneEntry;
extern "C" char s20dWhalestoneDisplayName[];
extern "C" char s20dWhalestoneFieldTypes[];
extern "C" const char* s20dWhalestoneFieldNames[];

extern "C" void s20dWhalestoneRegister(void)
{
	s20dWhalestoneEntry.flags = 0;
	s20dWhalestoneEntry.unk18 = 0;

	s20dWhalestoneEntry.name   = s20dWhalestoneDisplayName;
	s20dWhalestoneEntry.load   = s20dWhalestoneLoad;
	s20dWhalestoneEntry.unload = s20dWhalestoneUnload;
	s20dWhalestoneEntry.create = s20dWhalestoneCreate;
	s20dWhalestoneEntry.unk10  = NULL;

	s20dWhalestoneEntry.flags = 0x1021000;
	s20dWhalestoneEntry.unk18 = 0;
	s20dWhalestoneEntry.unk20 = 20;
	s20dWhalestoneEntry.unk1C = 8321;
	s20dWhalestoneEntry.unk1E = 2;
	s20dWhalestoneEntry.unk21 = 0;

	s20dWhalestoneEntry.fieldTypes = s20dWhalestoneFieldTypes;
	s20dWhalestoneEntry.fieldNames = s20dWhalestoneFieldNames;

	if (s20dWhalestoneFieldTypes != NULL) {
		s20dWhalestoneEntry.flags |= 8;
	} else {
		s20dWhalestoneEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s20dWhalestoneCtorEntry)(void) = s20dWhalestoneRegister;
