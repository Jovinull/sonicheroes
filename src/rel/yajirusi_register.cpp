#include "types.h"

// The record that registers YAJIRUSI with the editor.
//
// The claim is .text 0x9FA10 to 0x9FAC0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage05D carries this run.

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
extern "C" void yajirusiLoad(void);
extern "C" void yajirusiUnload(void);
extern "C" void yajirusiCreate(void);
extern "C" void yajirusiReset(void);
extern "C" ObjectEntry yajirusiEntry;
extern "C" char yajirusiDisplayName[];
extern "C" char yajirusiFieldTypes[];
extern "C" const char* yajirusiFieldNames[];

extern "C" void yajirusiRegister(void)
{
	yajirusiEntry.flags = 0;
	yajirusiEntry.unk18 = 0;

	yajirusiEntry.name   = yajirusiDisplayName;
	yajirusiEntry.load   = yajirusiLoad;
	yajirusiEntry.unload = yajirusiUnload;
	yajirusiEntry.create = yajirusiCreate;
	yajirusiEntry.reset  = yajirusiReset;

	yajirusiEntry.flags = 0x1000;
	yajirusiEntry.unk18 = 0;
	yajirusiEntry.unk20 = 0xf;
	yajirusiEntry.unk1C = 0x581;
	yajirusiEntry.unk1E = 2;
	yajirusiEntry.unk21 = 0;

	yajirusiEntry.fieldTypes = yajirusiFieldTypes;
	yajirusiEntry.fieldNames = yajirusiFieldNames;

	if (yajirusiFieldTypes != NULL) {
		yajirusiEntry.flags |= 8;
	} else {
		yajirusiEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const yajirusiCtorEntry)(void) = yajirusiRegister;
