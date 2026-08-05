#include "types.h"

// The record that registers S01 TRUCK RAIL with the editor.
//
// The claim is .text 0x8FBCC to 0x8FC74 and the .ctors word at 0xF8 that names
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
extern "C" void s01TruckRailLoad(void);
extern "C" void s01TruckRailUnload(void);
extern "C" void s01TruckRailCreate(void);
extern "C" ObjectEntry s01TruckRailEntry;
extern "C" char s01TruckRailDisplayName[];
extern "C" char s01TruckRailFieldTypes[];
extern "C" const char* s01TruckRailFieldNames[];

extern "C" void s01TruckRailRegister(void)
{
	s01TruckRailEntry.flags = 0;
	s01TruckRailEntry.unk18 = 0;

	s01TruckRailEntry.name   = s01TruckRailDisplayName;
	s01TruckRailEntry.load   = s01TruckRailLoad;
	s01TruckRailEntry.unload = s01TruckRailUnload;
	s01TruckRailEntry.create = s01TruckRailCreate;
	s01TruckRailEntry.unk10  = NULL;

	s01TruckRailEntry.flags = 0x20000;
	s01TruckRailEntry.unk18 = 0;
	s01TruckRailEntry.unk20 = 50;
	s01TruckRailEntry.unk1C = 258;
	s01TruckRailEntry.unk1E = 2;
	s01TruckRailEntry.unk21 = 0;

	s01TruckRailEntry.fieldTypes = s01TruckRailFieldTypes;
	s01TruckRailEntry.fieldNames = s01TruckRailFieldNames;

	if (s01TruckRailFieldTypes != NULL) {
		s01TruckRailEntry.flags |= 8;
	} else {
		s01TruckRailEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s01TruckRailCtorEntry)(void) = s01TruckRailRegister;
