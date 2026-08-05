#include "types.h"

// The record that registers S02D Green with the editor.
//
// The claim is .text 0xAECF0 to 0xAED9C and the .ctors word at 0x124 that names
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
extern "C" void s02GreenLoad(void);
extern "C" void s02GreenUnload(void);
extern "C" void s02GreenCreate(void);
extern "C" ObjectEntry s02GreenEntry;
extern "C" char s02GreenDisplayName[];
extern "C" char s02GreenFieldTypes[];
extern "C" const char* s02GreenFieldNames[];

extern "C" void s02GreenRegister(void)
{
	s02GreenEntry.flags = 0;
	s02GreenEntry.unk18 = 0;

	s02GreenEntry.name   = s02GreenDisplayName;
	s02GreenEntry.load   = s02GreenLoad;
	s02GreenEntry.unload = s02GreenUnload;
	s02GreenEntry.create = s02GreenCreate;
	s02GreenEntry.unk10  = NULL;

	s02GreenEntry.flags = 0x21000;
	s02GreenEntry.unk18 = 0;
	s02GreenEntry.unk20 = 20;
	s02GreenEntry.unk1C = 644;
	s02GreenEntry.unk1E = 2;
	s02GreenEntry.unk21 = 0;

	s02GreenEntry.fieldTypes = s02GreenFieldTypes;
	s02GreenEntry.fieldNames = s02GreenFieldNames;

	if (s02GreenFieldTypes != NULL) {
		s02GreenEntry.flags |= 8;
	} else {
		s02GreenEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s02GreenCtorEntry)(void) = s02GreenRegister;
