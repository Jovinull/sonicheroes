#include "types.h"

// The record that registers TObjSample with the editor.
//
// The claim is .text 0x494 to 0x548 and the .ctors word that names it. Only the
// record is taken: the factory it points at is still assembly, for the reason
// written up in rel/sample2_object.c.
//
// The run is the same in all thirteen stage modules that share the engine core.
// stage40D is a different revision of the source and is left out.
//
// The count at 0x1C is 0xFFFF here, which the compiler builds with a shift and
// a subtract rather than a load immediate. Writing it as -1 into a signed field
// costs one of those two instructions, so the field is unsigned.
//
// "fc" is the field type string, a float and a byte. The three hooks are the
// empty ones from rel/sample1_object.c: this class loads nothing.

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
extern "C" void sample1Stub1(void);
extern "C" void sample1Stub2(void);
extern "C" void sample1Stub3(void);
extern "C" void sample1Create(void);
extern "C" ObjectEntry sample1Entry;
extern "C" char sample1DisplayName[];
extern "C" char sample1FieldTypes[];
extern "C" const char* sample1FieldNames[];

extern "C" void sample1Register(void)
{
	sample1Entry.flags = 0;
	sample1Entry.unk18 = 0;

	sample1Entry.name   = sample1DisplayName;
	sample1Entry.load   = sample1Stub3;
	sample1Entry.unload = sample1Stub2;
	sample1Entry.create = sample1Create;
	sample1Entry.reset  = sample1Stub1;

	sample1Entry.flags = 0x20000;
	sample1Entry.unk18 = 0;
	sample1Entry.unk20 = 0x1E;
	sample1Entry.unk1C = 0xFFFF;
	sample1Entry.unk1E = 2;
	sample1Entry.unk21 = 0;

	sample1Entry.fieldTypes = sample1FieldTypes;
	sample1Entry.fieldNames = sample1FieldNames;

	if (sample1FieldTypes != NULL) {
		sample1Entry.flags |= 8;
	} else {
		sample1Entry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const sample1CtorEntry)(void) = sample1Register;
