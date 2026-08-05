#include "types.h"

// The record that registers S02D Pole with the editor.
//
// The claim is .text 0xB05CC to 0xB0678 and the .ctors word at 0x12C that names
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
extern "C" void s02PoleLoad(void);
extern "C" void s02PoleUnload(void);
extern "C" void s02PoleCreate(void);
extern "C" ObjectEntry s02PoleEntry;
extern "C" char s02PoleDisplayName[];
extern "C" char s02PoleFieldTypes[];
extern "C" const char* s02PoleFieldNames[];

extern "C" void s02PoleRegister(void)
{
	s02PoleEntry.flags = 0;
	s02PoleEntry.unk18 = 0;

	s02PoleEntry.name   = s02PoleDisplayName;
	s02PoleEntry.load   = s02PoleLoad;
	s02PoleEntry.unload = s02PoleUnload;
	s02PoleEntry.create = s02PoleCreate;
	s02PoleEntry.unk10  = NULL;

	s02PoleEntry.flags = 0x21000;
	s02PoleEntry.unk18 = 0;
	s02PoleEntry.unk20 = 20;
	s02PoleEntry.unk1C = 645;
	s02PoleEntry.unk1E = 2;
	s02PoleEntry.unk21 = 0;

	s02PoleEntry.fieldTypes = s02PoleFieldTypes;
	s02PoleEntry.fieldNames = s02PoleFieldNames;

	if (s02PoleFieldTypes != NULL) {
		s02PoleEntry.flags |= 8;
	} else {
		s02PoleEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s02PoleCtorEntry)(void) = s02PoleRegister;
