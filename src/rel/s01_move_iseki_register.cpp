#include "types.h"

// The record that registers S01 MOVE ISEKI with the editor (the ruins that
// move), in stage01D: the run at .text 0x882B8 to 0x88368 and the .ctors word
// at 0xE4 that names it, the body of rel/s02_colli_for_quake_register.cpp with
// the module's Load and Unload hooks, flags 0x20000 and the first of the
// family's set ids (a table of halfwords) as its id.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void (*reset)(void);     // 0x10
	u32 flags;               // 0x14
	u32 unk18;               // 0x18
	u16 unk1C;               // 0x1C
	s16 unk1E;               // 0x1E
	u8 unk20;                // 0x20
	u8 unk21;                // 0x21
	u8 pad22[2];             // 0x22
	const char* fieldTypes;  // 0x24
	const char** fieldNames; // 0x28
	u8 unk2C[0x4];           // 0x2C
} ObjectEntry;               // 0x30

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void s01MoveIsekiLoad(void);
extern "C" void s01MoveIsekiUnload(void);
extern "C" void s01MoveIsekiCreate(void);
extern "C" ObjectEntry s01MoveIsekiEntry;
extern "C" char s01MoveIsekiDisplayName[];
extern "C" char s01MoveIsekiFieldTypes[];
extern "C" const char* s01MoveIsekiFieldNames[];
extern "C" u16 s01MoveIsekiSetIds[];

extern "C" void s01MoveIsekiRegister(void)
{
	s01MoveIsekiEntry.flags = 0;
	s01MoveIsekiEntry.unk18 = 0;

	s01MoveIsekiEntry.name   = s01MoveIsekiDisplayName;
	s01MoveIsekiEntry.load   = s01MoveIsekiLoad;
	s01MoveIsekiEntry.unload = s01MoveIsekiUnload;
	s01MoveIsekiEntry.create = s01MoveIsekiCreate;
	s01MoveIsekiEntry.reset  = NULL;

	s01MoveIsekiEntry.flags = 0x20000;
	s01MoveIsekiEntry.unk18 = 0;
	s01MoveIsekiEntry.unk20 = 50;
	s01MoveIsekiEntry.unk1C = s01MoveIsekiSetIds[0];
	s01MoveIsekiEntry.unk1E = 2;
	s01MoveIsekiEntry.unk21 = 0;

	s01MoveIsekiEntry.fieldTypes = s01MoveIsekiFieldTypes;
	s01MoveIsekiEntry.fieldNames = s01MoveIsekiFieldNames;

	if (s01MoveIsekiEntry.fieldTypes != NULL) {
		s01MoveIsekiEntry.flags |= 8;
	} else {
		s01MoveIsekiEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s01MoveIsekiCtorEntry)(void) = s01MoveIsekiRegister;
