#include "types.h"

// The record that registers IVYJUMP with the editor.
//
// The claim is .text 0x79590 to 0x79640 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "FFFFFFccs" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage09D carries this run.

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
extern "C" void ivyjumpLoad(void);
extern "C" void ivyjumpUnload(void);
extern "C" void ivyjumpCreate(void);
extern "C" void ivyjumpReset(void);
extern "C" ObjectEntry ivyjumpEntry;
extern "C" char ivyjumpDisplayName[];
extern "C" char ivyjumpFieldTypes[];
extern "C" const char* ivyjumpFieldNames[];

extern "C" void ivyjumpRegister(void)
{
	ivyjumpEntry.flags = 0;
	ivyjumpEntry.unk18 = 0;

	ivyjumpEntry.name   = ivyjumpDisplayName;
	ivyjumpEntry.load   = ivyjumpLoad;
	ivyjumpEntry.unload = ivyjumpUnload;
	ivyjumpEntry.create = ivyjumpCreate;
	ivyjumpEntry.reset  = ivyjumpReset;

	ivyjumpEntry.flags = 0x20000;
	ivyjumpEntry.unk18 = 0;
	ivyjumpEntry.unk20 = 0xa;
	ivyjumpEntry.unk1C = 0x90b;
	ivyjumpEntry.unk1E = 2;
	ivyjumpEntry.unk21 = 0;

	ivyjumpEntry.fieldTypes = ivyjumpFieldTypes;
	ivyjumpEntry.fieldNames = ivyjumpFieldNames;

	if (ivyjumpFieldTypes != NULL) {
		ivyjumpEntry.flags |= 8;
	} else {
		ivyjumpEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const ivyjumpCtorEntry)(void) = ivyjumpRegister;
