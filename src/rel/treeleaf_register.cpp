#include "types.h"

// The record that registers TREELEAF with the editor.
//
// The claim is .text 0x999E0 to 0x99A90 and the .ctors word that names it.
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
extern "C" void treeleafLoad(void);
extern "C" void treeleafUnload(void);
extern "C" void treeleafCreate(void);
extern "C" void treeleafReset(void);
extern "C" ObjectEntry treeleafEntry;
extern "C" char treeleafDisplayName[];
extern "C" char treeleafFieldTypes[];
extern "C" const char* treeleafFieldNames[];

extern "C" void treeleafRegister(void)
{
	treeleafEntry.flags = 0;
	treeleafEntry.unk18 = 0;

	treeleafEntry.name   = treeleafDisplayName;
	treeleafEntry.load   = treeleafLoad;
	treeleafEntry.unload = treeleafUnload;
	treeleafEntry.create = treeleafCreate;
	treeleafEntry.reset  = treeleafReset;

	treeleafEntry.flags = 0x1000;
	treeleafEntry.unk18 = 0;
	treeleafEntry.unk20 = 0xa;
	treeleafEntry.unk1C = 0x992;
	treeleafEntry.unk1E = 2;
	treeleafEntry.unk21 = 0;

	treeleafEntry.fieldTypes = treeleafFieldTypes;
	treeleafEntry.fieldNames = treeleafFieldNames;

	if (treeleafFieldTypes != NULL) {
		treeleafEntry.flags |= 8;
	} else {
		treeleafEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const treeleafCtorEntry)(void) = treeleafRegister;
