#include "types.h"

// The record that registers STG28 OBJ with the editor.
//
// The claim is .text 0x7BFE0 to 0x7C088 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cccc" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage28D carries this run.

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
extern "C" void stg28ObjLoad(void);
extern "C" void stg28ObjUnload(void);
extern "C" void stg28ObjCreate(void);
extern "C" ObjectEntry stg28ObjEntry;
extern "C" char stg28ObjDisplayName[];
extern "C" char stg28ObjFieldTypes[];
extern "C" const char* stg28ObjFieldNames[];

extern "C" void stg28ObjRegister(void)
{
	stg28ObjEntry.flags = 0;
	stg28ObjEntry.unk18 = 0;

	stg28ObjEntry.name   = stg28ObjDisplayName;
	stg28ObjEntry.load   = stg28ObjLoad;
	stg28ObjEntry.unload = stg28ObjUnload;
	stg28ObjEntry.create = stg28ObjCreate;
	stg28ObjEntry.reset  = NULL;

	stg28ObjEntry.flags = 0x80;
	stg28ObjEntry.unk18 = 0;
	stg28ObjEntry.unk20 = 0x1e;
	stg28ObjEntry.unk1C = 0x15d5;
	stg28ObjEntry.unk1E = 4;
	stg28ObjEntry.unk21 = 0;

	stg28ObjEntry.fieldTypes = stg28ObjFieldTypes;
	stg28ObjEntry.fieldNames = stg28ObjFieldNames;

	if (stg28ObjFieldTypes != NULL) {
		stg28ObjEntry.flags |= 8;
	} else {
		stg28ObjEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const stg28ObjCtorEntry)(void) = stg28ObjRegister;
