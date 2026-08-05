#include "types.h"

// The record that registers S02 BreakRuin L with the editor.
//
// The claim is .text 0x99808 to 0x9989C and the .ctors word at 0x10C that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here, and each hook is named from the entry offset it
// is stored into.
//
// It shows no editor fields, so the type and label slots take NULL. The flags word is 0x0; its width is what sets this run's length apart
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
extern "C" void s02BreakruinLLoad(void);
extern "C" void s02BreakruinLUnload(void);
extern "C" void s02BreakruinLCreate(void);
extern "C" ObjectEntry s02BreakruinLEntry;
extern "C" char s02BreakruinLDisplayName[];

extern "C" void s02BreakruinLRegister(void)
{
	s02BreakruinLEntry.flags = 0;
	s02BreakruinLEntry.unk18 = 0;

	s02BreakruinLEntry.name   = s02BreakruinLDisplayName;
	s02BreakruinLEntry.load   = s02BreakruinLLoad;
	s02BreakruinLEntry.unload = s02BreakruinLUnload;
	s02BreakruinLEntry.create = s02BreakruinLCreate;
	s02BreakruinLEntry.reset  = NULL;

	s02BreakruinLEntry.flags = 0x0;
	s02BreakruinLEntry.unk18 = 0;
	s02BreakruinLEntry.unk20 = 50;
	s02BreakruinLEntry.unk1C = 513;
	s02BreakruinLEntry.unk1E = 2;
	s02BreakruinLEntry.unk21 = 0;

	s02BreakruinLEntry.fieldTypes = NULL;
	s02BreakruinLEntry.fieldNames = NULL;

	if (s02BreakruinLEntry.fieldTypes != NULL) {
		s02BreakruinLEntry.flags |= 8;
	} else {
		s02BreakruinLEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s02BreakruinLCtorEntry)(void) = s02BreakruinLRegister;
