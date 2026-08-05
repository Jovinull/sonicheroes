#include "types.h"

// The record that registers S02D Water with the editor.
//
// The claim is .text 0xA35B0 to 0xA365C and the .ctors word at 0x120 that names
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
extern "C" void s02WaterLoad(void);
extern "C" void s02WaterUnload(void);
extern "C" void s02WaterCreate(void);
extern "C" ObjectEntry s02WaterEntry;
extern "C" char s02WaterDisplayName[];
extern "C" char s02WaterFieldTypes[];
extern "C" const char* s02WaterFieldNames[];

extern "C" void s02WaterRegister(void)
{
	s02WaterEntry.flags = 0;
	s02WaterEntry.unk18 = 0;

	s02WaterEntry.name   = s02WaterDisplayName;
	s02WaterEntry.load   = s02WaterLoad;
	s02WaterEntry.unload = s02WaterUnload;
	s02WaterEntry.create = s02WaterCreate;
	s02WaterEntry.unk10  = NULL;

	s02WaterEntry.flags = 0x21000;
	s02WaterEntry.unk18 = 0;
	s02WaterEntry.unk20 = 20;
	s02WaterEntry.unk1C = 643;
	s02WaterEntry.unk1E = 2;
	s02WaterEntry.unk21 = 0;

	s02WaterEntry.fieldTypes = s02WaterFieldTypes;
	s02WaterEntry.fieldNames = s02WaterFieldNames;

	if (s02WaterFieldTypes != NULL) {
		s02WaterEntry.flags |= 8;
	} else {
		s02WaterEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s02WaterCtorEntry)(void) = s02WaterRegister;
