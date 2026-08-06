#include "types.h"

// The records that register S12BONE OBJECT and S12BONE COLLI_OBJECT with the editor.
//
// The claim is .text 0xCDB88 to 0xCDCD4 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "i" is S12BONE OBJECT's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "fff" is S12BONE COLLI_OBJECT's field type string: one character per parameter the
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
extern "C" void s12boneObjectLoad(void);
extern "C" void s12boneObjectUnload(void);
extern "C" void s12boneObjectCreate(void);
extern "C" void s12boneObjectReset(void);
extern "C" ObjectEntry s12boneObjectEntry;
extern "C" char s12boneObjectDisplayName[];
extern "C" char s12boneObjectFieldTypes[];
extern "C" const char* s12boneObjectFieldNames[];

extern "C" void s12boneColliObjectCreate(void);
extern "C" void s12boneColliObjectReset(void);
extern "C" ObjectEntry s12boneColliObjectEntry;
extern "C" char s12boneColliObjectDisplayName[];
extern "C" char s12boneColliObjectFieldTypes[];
extern "C" const char* s12boneColliObjectFieldNames[];

extern "C" void s12boneObjectRegister(void)
{
	s12boneObjectEntry.flags = 0;
	s12boneObjectEntry.unk18 = 0;

	s12boneObjectEntry.name   = s12boneObjectDisplayName;
	s12boneObjectEntry.load   = s12boneObjectLoad;
	s12boneObjectEntry.unload = s12boneObjectUnload;
	s12boneObjectEntry.create = s12boneObjectCreate;
	s12boneObjectEntry.reset  = s12boneObjectReset;

	s12boneObjectEntry.flags = 0x20000;
	s12boneObjectEntry.unk18 = 0;
	s12boneObjectEntry.unk20 = 0x1e;
	s12boneObjectEntry.unk1C = 0x1185;
	s12boneObjectEntry.unk1E = 2;
	s12boneObjectEntry.unk21 = 0x0;

	s12boneObjectEntry.fieldTypes = s12boneObjectFieldTypes;
	s12boneObjectEntry.fieldNames = s12boneObjectFieldNames;

	if (s12boneObjectFieldTypes != NULL) {
		s12boneObjectEntry.flags |= 8;
	} else {
		s12boneObjectEntry.flags &= ~8;
	}

	s12boneColliObjectEntry.flags = 0;
	s12boneColliObjectEntry.unk18 = 0;

	s12boneColliObjectEntry.name   = s12boneColliObjectDisplayName;
	s12boneColliObjectEntry.load   = NULL;
	s12boneColliObjectEntry.unload = NULL;
	s12boneColliObjectEntry.create = s12boneColliObjectCreate;
	s12boneColliObjectEntry.reset  = s12boneColliObjectReset;

	s12boneColliObjectEntry.flags = 0x20000;
	s12boneColliObjectEntry.unk18 = 0;
	s12boneColliObjectEntry.unk20 = 0x1e;
	s12boneColliObjectEntry.unk1C = 0x1186;
	s12boneColliObjectEntry.unk1E = 2;
	s12boneColliObjectEntry.unk21 = 0x0;

	s12boneColliObjectEntry.fieldTypes = s12boneColliObjectFieldTypes;
	s12boneColliObjectEntry.fieldNames = s12boneColliObjectFieldNames;

	if (s12boneColliObjectFieldTypes != NULL) {
		s12boneColliObjectEntry.flags |= 8;
	} else {
		s12boneColliObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s12boneObjectCtorEntry)(void) = s12boneObjectRegister;
