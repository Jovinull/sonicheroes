#include "types.h"

// The record that registers S02 Break Gareki with the editor.
//
// The claim is .text 0x97CCC to 0x97D74 and the .ctors word at 0x108 that names
// it. Only the record is taken: the three hooks it points at stay assembly and
// are reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here.
//
// The flags word is 0x20000, small enough for one instruction, which is the
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
extern "C" void s02BreakGarekiLoad(void);
extern "C" void s02BreakGarekiUnload(void);
extern "C" void s02BreakGarekiCreate(void);
extern "C" ObjectEntry s02BreakGarekiEntry;
extern "C" char s02BreakGarekiDisplayName[];
extern "C" char s02BreakGarekiFieldTypes[];
extern "C" const char* s02BreakGarekiFieldNames[];

extern "C" void s02BreakGarekiRegister(void)
{
	s02BreakGarekiEntry.flags = 0;
	s02BreakGarekiEntry.unk18 = 0;

	s02BreakGarekiEntry.name   = s02BreakGarekiDisplayName;
	s02BreakGarekiEntry.load   = s02BreakGarekiLoad;
	s02BreakGarekiEntry.unload = s02BreakGarekiUnload;
	s02BreakGarekiEntry.create = s02BreakGarekiCreate;
	s02BreakGarekiEntry.unk10  = NULL;

	s02BreakGarekiEntry.flags = 0x20000;
	s02BreakGarekiEntry.unk18 = 0;
	s02BreakGarekiEntry.unk20 = 50;
	s02BreakGarekiEntry.unk1C = 515;
	s02BreakGarekiEntry.unk1E = 2;
	s02BreakGarekiEntry.unk21 = 0;

	s02BreakGarekiEntry.fieldTypes = s02BreakGarekiFieldTypes;
	s02BreakGarekiEntry.fieldNames = s02BreakGarekiFieldNames;

	if (s02BreakGarekiFieldTypes != NULL) {
		s02BreakGarekiEntry.flags |= 8;
	} else {
		s02BreakGarekiEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s02BreakGarekiCtorEntry)(void) = s02BreakGarekiRegister;
