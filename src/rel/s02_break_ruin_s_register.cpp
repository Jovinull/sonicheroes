#include "types.h"

// The record that registers S02 BreakRuin S with the editor.
//
// The claim is .text 0x9C238 to 0x9C2DC and the .ctors word at 0x110 that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here, and each hook is named from the entry offset it
// is stored into.
//
// It carries editor fields, so the type and label slots are filled. The flags word is 0x0; its width is what sets this run's length apart
// from others of the same shape.
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
	void (*reset)(void);     // 0x10
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
extern "C" void s02BreakruinSLoad(void);
extern "C" void s02BreakruinSUnload(void);
extern "C" void s02BreakruinSCreate(void);
extern "C" ObjectEntry s02BreakruinSEntry;
extern "C" char s02BreakruinSDisplayName[];
extern "C" char s02BreakruinSFieldTypes[];
extern "C" const char* s02BreakruinSFieldNames[];

extern "C" void s02BreakruinSRegister(void)
{
	s02BreakruinSEntry.flags = 0;
	s02BreakruinSEntry.unk18 = 0;

	s02BreakruinSEntry.name   = s02BreakruinSDisplayName;
	s02BreakruinSEntry.load   = s02BreakruinSLoad;
	s02BreakruinSEntry.unload = s02BreakruinSUnload;
	s02BreakruinSEntry.create = s02BreakruinSCreate;
	s02BreakruinSEntry.reset  = NULL;

	s02BreakruinSEntry.flags = 0x0;
	s02BreakruinSEntry.unk18 = 0;
	s02BreakruinSEntry.unk20 = 50;
	s02BreakruinSEntry.unk1C = 512;
	s02BreakruinSEntry.unk1E = 2;
	s02BreakruinSEntry.unk21 = 0;

	s02BreakruinSEntry.fieldTypes = s02BreakruinSFieldTypes;
	s02BreakruinSEntry.fieldNames = s02BreakruinSFieldNames;

	if (s02BreakruinSEntry.fieldTypes != NULL) {
		s02BreakruinSEntry.flags |= 8;
	} else {
		s02BreakruinSEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s02BreakruinSCtorEntry)(void) = s02BreakruinSRegister;
