#include "types.h"

// The record that registers S04D ECylinder with the editor.
//
// The claim is .text 0x92584 to 0x9262C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cff" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage03D carries this run.

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
extern "C" void s04dECylinderLoad(void);
extern "C" void s04dECylinderUnload(void);
extern "C" void s04dECylinderCreate(void);
extern "C" ObjectEntry s04dECylinderEntry;
extern "C" char s04dECylinderDisplayName[];
extern "C" char s04dECylinderFieldTypes[];
extern "C" const char* s04dECylinderFieldNames[];

extern "C" void s04dECylinderRegister(void)
{
	s04dECylinderEntry.flags = 0;
	s04dECylinderEntry.unk18 = 0;

	s04dECylinderEntry.name   = s04dECylinderDisplayName;
	s04dECylinderEntry.load   = s04dECylinderLoad;
	s04dECylinderEntry.unload = s04dECylinderUnload;
	s04dECylinderEntry.create = s04dECylinderCreate;
	s04dECylinderEntry.reset  = NULL;

	s04dECylinderEntry.flags = 0x20000;
	s04dECylinderEntry.unk18 = 0;
	s04dECylinderEntry.unk20 = 0xa;
	s04dECylinderEntry.unk1C = 0x401;
	s04dECylinderEntry.unk1E = 2;
	s04dECylinderEntry.unk21 = 0;

	s04dECylinderEntry.fieldTypes = s04dECylinderFieldTypes;
	s04dECylinderEntry.fieldNames = s04dECylinderFieldNames;

	if (s04dECylinderFieldTypes != NULL) {
		s04dECylinderEntry.flags |= 8;
	} else {
		s04dECylinderEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04dECylinderCtorEntry)(void) = s04dECylinderRegister;
