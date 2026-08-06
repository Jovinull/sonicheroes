#include "types.h"

// The record that registers S11WARP OBJECT with the editor.
//
// The claim is .text 0x807FC to 0x808AC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "fffcc" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage11D carries this run.

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
extern "C" void s11warpObjectLoad(void);
extern "C" void s11warpObjectUnload(void);
extern "C" void s11warpObjectCreate(void);
extern "C" void s11warpObjectReset(void);
extern "C" ObjectEntry s11warpObjectEntry;
extern "C" char s11warpObjectDisplayName[];
extern "C" char s11warpObjectFieldTypes[];
extern "C" const char* s11warpObjectFieldNames[];

extern "C" void s11warpObjectRegister(void)
{
	s11warpObjectEntry.flags = 0;
	s11warpObjectEntry.unk18 = 0;

	s11warpObjectEntry.name   = s11warpObjectDisplayName;
	s11warpObjectEntry.load   = s11warpObjectLoad;
	s11warpObjectEntry.unload = s11warpObjectUnload;
	s11warpObjectEntry.create = s11warpObjectCreate;
	s11warpObjectEntry.reset  = s11warpObjectReset;

	s11warpObjectEntry.flags = 0x20000;
	s11warpObjectEntry.unk18 = 0;
	s11warpObjectEntry.unk20 = 0x1e;
	s11warpObjectEntry.unk1C = 0x1100;
	s11warpObjectEntry.unk1E = 2;
	s11warpObjectEntry.unk21 = 0;

	s11warpObjectEntry.fieldTypes = s11warpObjectFieldTypes;
	s11warpObjectEntry.fieldNames = s11warpObjectFieldNames;

	if (s11warpObjectFieldTypes != NULL) {
		s11warpObjectEntry.flags |= 8;
	} else {
		s11warpObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s11warpObjectCtorEntry)(void) = s11warpObjectRegister;
