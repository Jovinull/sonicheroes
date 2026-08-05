#include "types.h"

// The record that registers S66 STAR with the editor.
//
// The claim is .text 0xCB010 to 0xCB0BC and the .ctors word at 0x164 that names
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
extern "C" void s66StarLoad(void);
extern "C" void s66StarUnload(void);
extern "C" void s66StarCreate(void);
extern "C" ObjectEntry s66StarEntry;
extern "C" char s66StarDisplayName[];
extern "C" char s66StarFieldTypes[];
extern "C" const char* s66StarFieldNames[];

extern "C" void s66StarRegister(void)
{
	s66StarEntry.flags = 0;
	s66StarEntry.unk18 = 0;

	s66StarEntry.name   = s66StarDisplayName;
	s66StarEntry.load   = s66StarLoad;
	s66StarEntry.unload = s66StarUnload;
	s66StarEntry.create = s66StarCreate;
	s66StarEntry.unk10  = NULL;

	s66StarEntry.flags = 0x1021000;
	s66StarEntry.unk18 = 0;
	s66StarEntry.unk20 = 20;
	s66StarEntry.unk1C = 8323;
	s66StarEntry.unk1E = 2;
	s66StarEntry.unk21 = 0;

	s66StarEntry.fieldTypes = s66StarFieldTypes;
	s66StarEntry.fieldNames = s66StarFieldNames;

	if (s66StarFieldTypes != NULL) {
		s66StarEntry.flags |= 8;
	} else {
		s66StarEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s66StarCtorEntry)(void) = s66StarRegister;
