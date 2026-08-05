#include "types.h"

// The record that registers S20D CurbStone with the editor.
//
// The claim is .text 0xBB5BC to 0xBB668 and the .ctors word at 0x13C that names
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
extern "C" void s20dCurbstoneLoad(void);
extern "C" void s20dCurbstoneUnload(void);
extern "C" void s20dCurbstoneCreate(void);
extern "C" ObjectEntry s20dCurbstoneEntry;
extern "C" char s20dCurbstoneDisplayName[];
extern "C" char s20dCurbstoneFieldTypes[];
extern "C" const char* s20dCurbstoneFieldNames[];

extern "C" void s20dCurbstoneRegister(void)
{
	s20dCurbstoneEntry.flags = 0;
	s20dCurbstoneEntry.unk18 = 0;

	s20dCurbstoneEntry.name   = s20dCurbstoneDisplayName;
	s20dCurbstoneEntry.load   = s20dCurbstoneLoad;
	s20dCurbstoneEntry.unload = s20dCurbstoneUnload;
	s20dCurbstoneEntry.create = s20dCurbstoneCreate;
	s20dCurbstoneEntry.unk10  = NULL;

	s20dCurbstoneEntry.flags = 0x21000;
	s20dCurbstoneEntry.unk18 = 0;
	s20dCurbstoneEntry.unk20 = 20;
	s20dCurbstoneEntry.unk1C = 8320;
	s20dCurbstoneEntry.unk1E = 2;
	s20dCurbstoneEntry.unk21 = 0;

	s20dCurbstoneEntry.fieldTypes = s20dCurbstoneFieldTypes;
	s20dCurbstoneEntry.fieldNames = s20dCurbstoneFieldNames;

	if (s20dCurbstoneFieldTypes != NULL) {
		s20dCurbstoneEntry.flags |= 8;
	} else {
		s20dCurbstoneEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s20dCurbstoneCtorEntry)(void) = s20dCurbstoneRegister;
