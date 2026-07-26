#include "types.h"

// The record that registers TObjSample2 with the editor.
//
// The claim is .text 0x804 to 0x88C and the .ctors word that names it. Only the
// record is taken: the factory it points at is still assembly.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.
//
// This class exposes nothing to the editor: no load or unload hook, no field
// types and no labels, and its flags start at zero. The one thing it shares
// with the others is the shape of the record. The test at the end reads the
// field type pointer back out of the record rather than from a local: with a
// local the compiler folds the branch away, and reading the field keeps it
// while still reusing the zero it just stored.

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
} ObjectEntry;               // 0x2C

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void sample2Create(void);
extern "C" ObjectEntry sample2Entry;
extern "C" char sample2DisplayName[];

extern "C" void sample2Register(void)
{
	sample2Entry.flags = 0;
	sample2Entry.unk18 = 0;

	sample2Entry.name   = sample2DisplayName;
	sample2Entry.load   = NULL;
	sample2Entry.unload = NULL;
	sample2Entry.create = sample2Create;
	sample2Entry.reset  = NULL;

	sample2Entry.flags = 0;
	sample2Entry.unk18 = 0;
	sample2Entry.unk20 = 0x1E;
	sample2Entry.unk1C = 0xFFFE;
	sample2Entry.unk1E = 6;
	sample2Entry.unk21 = 0;

	sample2Entry.fieldTypes = NULL;
	sample2Entry.fieldNames = NULL;

	if (sample2Entry.fieldTypes != NULL) {
		sample2Entry.flags |= 8;
	} else {
		sample2Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const sample2CtorEntry)(void) = sample2Register;
