#include "types.h"

// The records that register S13 HOUDAI S and S14 HOUDAI HI and S13 HOUDAI FIX with the editor.
//
// The claim is .text 0x74F94 to 0x75184 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "CSXXfCCC" is S13 HOUDAI S's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "CSXXfCCC" is S14 HOUDAI HI's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
// "CSXXfCCC" is S13 HOUDAI FIX's field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in two of the fourteen stage modules: 13D and 26D.

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
extern "C" void s13HoudaiSLoad(void);
extern "C" void s13HoudaiSUnload(void);
extern "C" void s13HoudaiSCreate(void);
extern "C" ObjectEntry s13HoudaiSEntry;
extern "C" char s13HoudaiSDisplayName[];
extern "C" char s13HoudaiSFieldTypes[];
extern "C" const char* s13HoudaiSFieldNames[];

extern "C" void s14HoudaiHiCreate(void);
extern "C" ObjectEntry s14HoudaiHiEntry;
extern "C" char s14HoudaiHiDisplayName[];

extern "C" void s13HoudaiFixCreate(void);
extern "C" ObjectEntry s13HoudaiFixEntry;
extern "C" char s13HoudaiFixDisplayName[];

extern "C" void s13HoudaiSRegister(void)
{
	s13HoudaiSEntry.flags = 0;
	s13HoudaiSEntry.unk18 = 0;

	s13HoudaiSEntry.name   = s13HoudaiSDisplayName;
	s13HoudaiSEntry.load   = s13HoudaiSLoad;
	s13HoudaiSEntry.unload = s13HoudaiSUnload;
	s13HoudaiSEntry.create = s13HoudaiSCreate;
	s13HoudaiSEntry.reset  = NULL;

	s13HoudaiSEntry.flags = 0x20000;
	s13HoudaiSEntry.unk18 = 0;
	s13HoudaiSEntry.unk20 = 0x14;
	s13HoudaiSEntry.unk1C = 0x1300;
	s13HoudaiSEntry.unk1E = 2;
	s13HoudaiSEntry.unk21 = 0;

	s13HoudaiSEntry.fieldTypes = s13HoudaiSFieldTypes;
	s13HoudaiSEntry.fieldNames = s13HoudaiSFieldNames;

	if (s13HoudaiSFieldTypes != NULL) {
		s13HoudaiSEntry.flags |= 8;
	} else {
		s13HoudaiSEntry.flags &= ~8;
	}

	s14HoudaiHiEntry.flags = 0;
	s14HoudaiHiEntry.unk18 = 0;

	s14HoudaiHiEntry.name   = s14HoudaiHiDisplayName;
	s14HoudaiHiEntry.load   = s13HoudaiSLoad;
	s14HoudaiHiEntry.unload = s13HoudaiSUnload;
	s14HoudaiHiEntry.create = s14HoudaiHiCreate;
	s14HoudaiHiEntry.reset  = NULL;

	s14HoudaiHiEntry.flags = 0x20000;
	s14HoudaiHiEntry.unk18 = 0;
	s14HoudaiHiEntry.unk20 = 0x14;
	s14HoudaiHiEntry.unk1C = 0x1401;
	s14HoudaiHiEntry.unk1E = 2;
	s14HoudaiHiEntry.unk21 = 0;

	s14HoudaiHiEntry.fieldTypes = s13HoudaiSFieldTypes;
	s14HoudaiHiEntry.fieldNames = s13HoudaiSFieldNames;

	if (s13HoudaiSFieldTypes != NULL) {
		s14HoudaiHiEntry.flags |= 8;
	} else {
		s14HoudaiHiEntry.flags &= ~8;
	}

	s13HoudaiFixEntry.flags = 0;
	s13HoudaiFixEntry.unk18 = 0;

	s13HoudaiFixEntry.name   = s13HoudaiFixDisplayName;
	s13HoudaiFixEntry.load   = s13HoudaiSLoad;
	s13HoudaiFixEntry.unload = s13HoudaiSUnload;
	s13HoudaiFixEntry.create = s13HoudaiFixCreate;
	s13HoudaiFixEntry.reset  = NULL;

	s13HoudaiFixEntry.flags = 0x20000;
	s13HoudaiFixEntry.unk18 = 0;
	s13HoudaiFixEntry.unk20 = 0x14;
	s13HoudaiFixEntry.unk1C = 0x1315;
	s13HoudaiFixEntry.unk1E = 2;
	s13HoudaiFixEntry.unk21 = 0;

	s13HoudaiFixEntry.fieldTypes = s13HoudaiSFieldTypes;
	s13HoudaiFixEntry.fieldNames = s13HoudaiSFieldNames;

	if (s13HoudaiSFieldTypes != NULL) {
		s13HoudaiFixEntry.flags |= 8;
	} else {
		s13HoudaiFixEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13HoudaiSCtorEntry)(void) = s13HoudaiSRegister;
