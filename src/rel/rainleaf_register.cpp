#include "types.h"

// The record that registers RAINLEAF with the editor.
//
// The claim is .text 0x87148 to 0x871F8 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
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
extern "C" void rainleafLoad(void);
extern "C" void rainleafUnload(void);
extern "C" void rainleafCreate(void);
extern "C" void rainleafReset(void);
extern "C" ObjectEntry rainleafEntry;
extern "C" char rainleafDisplayName[];
extern "C" char rainleafFieldTypes[];
extern "C" const char* rainleafFieldNames[];

extern "C" void rainleafRegister(void)
{
	rainleafEntry.flags = 0;
	rainleafEntry.unk18 = 0;

	rainleafEntry.name   = rainleafDisplayName;
	rainleafEntry.load   = rainleafLoad;
	rainleafEntry.unload = rainleafUnload;
	rainleafEntry.create = rainleafCreate;
	rainleafEntry.reset  = rainleafReset;

	rainleafEntry.flags = 0x20000;
	rainleafEntry.unk18 = 0;
	rainleafEntry.unk20 = 0xa;
	rainleafEntry.unk1C = 0x902;
	rainleafEntry.unk1E = 2;
	rainleafEntry.unk21 = 0;

	rainleafEntry.fieldTypes = rainleafFieldTypes;
	rainleafEntry.fieldNames = rainleafFieldNames;

	if (rainleafFieldTypes != NULL) {
		rainleafEntry.flags |= 8;
	} else {
		rainleafEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const rainleafCtorEntry)(void) = rainleafRegister;
