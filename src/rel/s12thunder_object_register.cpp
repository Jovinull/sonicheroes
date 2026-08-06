#include "types.h"

// The records that register S12THUNDER OBJECT and S12THUNDER COLLI_OBJECT with the editor.
//
// The claim is .text 0x909C4 to 0x90B08 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is S12THUNDER OBJECT's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "f" is S12THUNDER COLLI_OBJECT's field type string: one character per parameter the
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
extern "C" void s12thunderObjectLoad(void);
extern "C" void s12thunderObjectUnload(void);
extern "C" void s12thunderObjectCreate(void);
extern "C" ObjectEntry s12thunderObjectEntry;
extern "C" char s12thunderObjectDisplayName[];
extern "C" char s12thunderObjectFieldTypes[];
extern "C" const char* s12thunderObjectFieldNames[];

extern "C" void s12thunderColliObjectCreate(void);
extern "C" void s12thunderColliObjectReset(void);
extern "C" ObjectEntry s12thunderColliObjectEntry;
extern "C" char s12thunderColliObjectDisplayName[];
extern "C" char s12thunderColliObjectFieldTypes[];
extern "C" const char* s12thunderColliObjectFieldNames[];

extern "C" void s12thunderObjectRegister(void)
{
	s12thunderObjectEntry.flags = 0;
	s12thunderObjectEntry.unk18 = 0;

	s12thunderObjectEntry.name   = s12thunderObjectDisplayName;
	s12thunderObjectEntry.load   = s12thunderObjectLoad;
	s12thunderObjectEntry.unload = s12thunderObjectUnload;
	s12thunderObjectEntry.create = s12thunderObjectCreate;
	s12thunderObjectEntry.reset  = NULL;

	s12thunderObjectEntry.flags = 0x20000;
	s12thunderObjectEntry.unk18 = 0;
	s12thunderObjectEntry.unk20 = 0x1e;
	s12thunderObjectEntry.unk1C = 0x1182;
	s12thunderObjectEntry.unk1E = 2;
	s12thunderObjectEntry.unk21 = 0x0;

	s12thunderObjectEntry.fieldTypes = s12thunderObjectFieldTypes;
	s12thunderObjectEntry.fieldNames = s12thunderObjectFieldNames;

	if (s12thunderObjectFieldTypes != NULL) {
		s12thunderObjectEntry.flags |= 8;
	} else {
		s12thunderObjectEntry.flags &= ~8;
	}

	s12thunderColliObjectEntry.flags = 0;
	s12thunderColliObjectEntry.unk18 = 0;

	s12thunderColliObjectEntry.name   = s12thunderColliObjectDisplayName;
	s12thunderColliObjectEntry.load   = NULL;
	s12thunderColliObjectEntry.unload = NULL;
	s12thunderColliObjectEntry.create = s12thunderColliObjectCreate;
	s12thunderColliObjectEntry.reset  = s12thunderColliObjectReset;

	s12thunderColliObjectEntry.flags = 0x20000;
	s12thunderColliObjectEntry.unk18 = 0;
	s12thunderColliObjectEntry.unk20 = 0x1e;
	s12thunderColliObjectEntry.unk1C = 0x1183;
	s12thunderColliObjectEntry.unk1E = 2;
	s12thunderColliObjectEntry.unk21 = 0x0;

	s12thunderColliObjectEntry.fieldTypes = s12thunderColliObjectFieldTypes;
	s12thunderColliObjectEntry.fieldNames = s12thunderColliObjectFieldNames;

	if (s12thunderColliObjectFieldTypes != NULL) {
		s12thunderColliObjectEntry.flags |= 8;
	} else {
		s12thunderColliObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s12thunderObjectCtorEntry)(void)
    = s12thunderObjectRegister;
