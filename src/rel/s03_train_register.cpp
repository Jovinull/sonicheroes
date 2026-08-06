#include "types.h"

// The record that registers S03 Train with the editor.
//
// The claim is .text 0x867D8 to 0x86884 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "fff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage03D carries this run.

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

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void s03TrainLoad(void);
extern "C" void s03TrainUnload(void);
extern "C" void s03TrainCreate(void);
extern "C" ObjectEntry s03TrainEntry;
extern "C" char s03TrainDisplayName[];
extern "C" char s03TrainFieldTypes[];
extern "C" const char* s03TrainFieldNames[];

extern "C" void s03TrainRegister(void)
{
	s03TrainEntry.flags = 0;
	s03TrainEntry.unk18 = 0;

	s03TrainEntry.name   = s03TrainDisplayName;
	s03TrainEntry.load   = s03TrainLoad;
	s03TrainEntry.unload = s03TrainUnload;
	s03TrainEntry.create = s03TrainCreate;
	s03TrainEntry.reset  = NULL;

	s03TrainEntry.flags = 0x21400;
	s03TrainEntry.unk18 = 0;
	s03TrainEntry.unk20 = 0xa;
	s03TrainEntry.unk1C = 0x382;
	s03TrainEntry.unk1E = 2;
	s03TrainEntry.unk21 = 0;

	s03TrainEntry.fieldTypes = s03TrainFieldTypes;
	s03TrainEntry.fieldNames = s03TrainFieldNames;

	if (s03TrainFieldTypes != NULL) {
		s03TrainEntry.flags |= 8;
	} else {
		s03TrainEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03TrainCtorEntry)(void) = s03TrainRegister;
