#include "types.h"

// The record that registers S02 BreakDoor with the editor.
//
// The claim is .text 0x95E7C to 0x95F24 and the .ctors word at 0x104 that names
// it. Only the record is taken: the three hooks it points at stay assembly and
// are reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// The flags word is 0x100, small enough for one instruction, which is the
// whole difference from rel/s66_star_register.cpp's two-instruction load.
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
extern "C" void s02BreakdoorLoad(void);
extern "C" void s02BreakdoorUnload(void);
extern "C" void s02BreakdoorCreate(void);
extern "C" ObjectEntry s02BreakdoorEntry;
extern "C" char s02BreakdoorDisplayName[];
extern "C" char s02BreakdoorFieldTypes[];
extern "C" const char* s02BreakdoorFieldNames[];

extern "C" void s02BreakdoorRegister(void)
{
	s02BreakdoorEntry.flags = 0;
	s02BreakdoorEntry.unk18 = 0;

	s02BreakdoorEntry.name   = s02BreakdoorDisplayName;
	s02BreakdoorEntry.load   = s02BreakdoorLoad;
	s02BreakdoorEntry.unload = s02BreakdoorUnload;
	s02BreakdoorEntry.create = s02BreakdoorCreate;
	s02BreakdoorEntry.unk10  = NULL;

	s02BreakdoorEntry.flags = 0x100;
	s02BreakdoorEntry.unk18 = 0;
	s02BreakdoorEntry.unk20 = 20;
	s02BreakdoorEntry.unk1C = 514;
	s02BreakdoorEntry.unk1E = 2;
	s02BreakdoorEntry.unk21 = 0;

	s02BreakdoorEntry.fieldTypes = s02BreakdoorFieldTypes;
	s02BreakdoorEntry.fieldNames = s02BreakdoorFieldNames;

	if (s02BreakdoorFieldTypes != NULL) {
		s02BreakdoorEntry.flags |= 8;
	} else {
		s02BreakdoorEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s02BreakdoorCtorEntry)(void) = s02BreakdoorRegister;
