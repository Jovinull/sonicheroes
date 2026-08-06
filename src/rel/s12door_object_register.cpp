#include "types.h"

// The records that register S12DOOR OBJECT and S12DOOR COLLI_OBJECT with the editor.
//
// The claim is .text 0x950FC to 0x95240 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is S12DOOR OBJECT's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "f" is S12DOOR COLLI_OBJECT's field type string: one character per parameter the
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
extern "C" void s12doorObjectLoad(void);
extern "C" void s12doorObjectUnload(void);
extern "C" void s12doorObjectCreate(void);
extern "C" ObjectEntry s12doorObjectEntry;
extern "C" char s12doorObjectDisplayName[];
extern "C" char s12doorObjectFieldTypes[];
extern "C" const char* s12doorObjectFieldNames[];

extern "C" void s12doorColliObjectCreate(void);
extern "C" void s12doorColliObjectReset(void);
extern "C" ObjectEntry s12doorColliObjectEntry;
extern "C" char s12doorColliObjectDisplayName[];
extern "C" char s12doorColliObjectFieldTypes[];
extern "C" const char* s12doorColliObjectFieldNames[];

extern "C" void s12doorObjectRegister(void)
{
	s12doorObjectEntry.flags = 0;
	s12doorObjectEntry.unk18 = 0;

	s12doorObjectEntry.name   = s12doorObjectDisplayName;
	s12doorObjectEntry.load   = s12doorObjectLoad;
	s12doorObjectEntry.unload = s12doorObjectUnload;
	s12doorObjectEntry.create = s12doorObjectCreate;
	s12doorObjectEntry.reset  = NULL;

	s12doorObjectEntry.flags = 0x20000;
	s12doorObjectEntry.unk18 = 0;
	s12doorObjectEntry.unk20 = 0x1e;
	s12doorObjectEntry.unk1C = 0x1108;
	s12doorObjectEntry.unk1E = 2;
	s12doorObjectEntry.unk21 = 0x0;

	s12doorObjectEntry.fieldTypes = s12doorObjectFieldTypes;
	s12doorObjectEntry.fieldNames = s12doorObjectFieldNames;

	if (s12doorObjectFieldTypes != NULL) {
		s12doorObjectEntry.flags |= 8;
	} else {
		s12doorObjectEntry.flags &= ~8;
	}

	s12doorColliObjectEntry.flags = 0;
	s12doorColliObjectEntry.unk18 = 0;

	s12doorColliObjectEntry.name   = s12doorColliObjectDisplayName;
	s12doorColliObjectEntry.load   = NULL;
	s12doorColliObjectEntry.unload = NULL;
	s12doorColliObjectEntry.create = s12doorColliObjectCreate;
	s12doorColliObjectEntry.reset  = s12doorColliObjectReset;

	s12doorColliObjectEntry.flags = 0x20000;
	s12doorColliObjectEntry.unk18 = 0;
	s12doorColliObjectEntry.unk20 = 0x1e;
	s12doorColliObjectEntry.unk1C = 0x110b;
	s12doorColliObjectEntry.unk1E = 2;
	s12doorColliObjectEntry.unk21 = 0x0;

	s12doorColliObjectEntry.fieldTypes = s12doorColliObjectFieldTypes;
	s12doorColliObjectEntry.fieldNames = s12doorColliObjectFieldNames;

	if (s12doorColliObjectFieldTypes != NULL) {
		s12doorColliObjectEntry.flags |= 8;
	} else {
		s12doorColliObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s12doorObjectCtorEntry)(void) = s12doorObjectRegister;
