#include "types.h"

// The record that registers S02 COLLI FOR QUAKE with the editor.
//
// The claim is .text 0x92D80 to 0x92E14 and the .ctors word at 0x100 that names
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
extern "C" void s02ColliForQuakeCreate(void);
extern "C" ObjectEntry s02ColliForQuakeEntry;
extern "C" char s02ColliForQuakeDisplayName[];
extern "C" char s02ColliForQuakeFieldTypes[];
extern "C" const char* s02ColliForQuakeFieldNames[];

extern "C" void s02ColliForQuakeRegister(void)
{
	s02ColliForQuakeEntry.flags = 0;
	s02ColliForQuakeEntry.unk18 = 0;

	s02ColliForQuakeEntry.name   = s02ColliForQuakeDisplayName;
	s02ColliForQuakeEntry.load   = NULL;
	s02ColliForQuakeEntry.unload = NULL;
	s02ColliForQuakeEntry.create = s02ColliForQuakeCreate;
	s02ColliForQuakeEntry.reset  = NULL;

	s02ColliForQuakeEntry.flags = 0x0;
	s02ColliForQuakeEntry.unk18 = 0;
	s02ColliForQuakeEntry.unk20 = 50;
	s02ColliForQuakeEntry.unk1C = 522;
	s02ColliForQuakeEntry.unk1E = 2;
	s02ColliForQuakeEntry.unk21 = 0;

	s02ColliForQuakeEntry.fieldTypes = s02ColliForQuakeFieldTypes;
	s02ColliForQuakeEntry.fieldNames = s02ColliForQuakeFieldNames;

	if (s02ColliForQuakeEntry.fieldTypes != NULL) {
		s02ColliForQuakeEntry.flags |= 8;
	} else {
		s02ColliForQuakeEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s02ColliForQuakeCtorEntry)(void)
    = s02ColliForQuakeRegister;
