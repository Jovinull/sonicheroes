#include "types.h"

// The record that registers STG27 OBJ with the editor.
//
// The claim is .text 0xB5C68 to 0xB5D10 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cccc" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in two of the fourteen stage modules: 26D and 27D.

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
extern "C" void stg27ObjLoad(void);
extern "C" void stg27ObjUnload(void);
extern "C" void stg27ObjCreate(void);
extern "C" ObjectEntry stg27ObjEntry;
extern "C" char stg27ObjDisplayName[];
extern "C" char stg27ObjFieldTypes[];
extern "C" const char* stg27ObjFieldNames[];

extern "C" void stg27ObjRegister(void)
{
	stg27ObjEntry.flags = 0;
	stg27ObjEntry.unk18 = 0;

	stg27ObjEntry.name   = stg27ObjDisplayName;
	stg27ObjEntry.load   = stg27ObjLoad;
	stg27ObjEntry.unload = stg27ObjUnload;
	stg27ObjEntry.create = stg27ObjCreate;
	stg27ObjEntry.reset  = NULL;

	stg27ObjEntry.flags = 0x80;
	stg27ObjEntry.unk18 = 0;
	stg27ObjEntry.unk20 = 0x1e;
	stg27ObjEntry.unk1C = 0x15d4;
	stg27ObjEntry.unk1E = 4;
	stg27ObjEntry.unk21 = 0;

	stg27ObjEntry.fieldTypes = stg27ObjFieldTypes;
	stg27ObjEntry.fieldNames = stg27ObjFieldNames;

	if (stg27ObjFieldTypes != NULL) {
		stg27ObjEntry.flags |= 8;
	} else {
		stg27ObjEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const stg27ObjCtorEntry)(void) = stg27ObjRegister;
