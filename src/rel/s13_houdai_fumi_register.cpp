#include "types.h"

// The record that registers S13 HOUDAI FUMI with the editor.
//
// The claim is .text 0x83260 to 0x83308 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "f" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage13D carries this run.

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
extern "C" void s13HoudaiFumiLoad(void);
extern "C" void s13HoudaiFumiUnload(void);
extern "C" void s13HoudaiFumiCreate(void);
extern "C" ObjectEntry s13HoudaiFumiEntry;
extern "C" char s13HoudaiFumiDisplayName[];
extern "C" char s13HoudaiFumiFieldTypes[];
extern "C" const char* s13HoudaiFumiFieldNames[];

extern "C" void s13HoudaiFumiRegister(void)
{
	s13HoudaiFumiEntry.flags = 0;
	s13HoudaiFumiEntry.unk18 = 0;

	s13HoudaiFumiEntry.name   = s13HoudaiFumiDisplayName;
	s13HoudaiFumiEntry.load   = s13HoudaiFumiLoad;
	s13HoudaiFumiEntry.unload = s13HoudaiFumiUnload;
	s13HoudaiFumiEntry.create = s13HoudaiFumiCreate;
	s13HoudaiFumiEntry.reset  = NULL;

	s13HoudaiFumiEntry.flags = 0x20000;
	s13HoudaiFumiEntry.unk18 = 0;
	s13HoudaiFumiEntry.unk20 = 0x14;
	s13HoudaiFumiEntry.unk1C = 0x1303;
	s13HoudaiFumiEntry.unk1E = 2;
	s13HoudaiFumiEntry.unk21 = 0;

	s13HoudaiFumiEntry.fieldTypes = s13HoudaiFumiFieldTypes;
	s13HoudaiFumiEntry.fieldNames = s13HoudaiFumiFieldNames;

	if (s13HoudaiFumiFieldTypes != NULL) {
		s13HoudaiFumiEntry.flags |= 8;
	} else {
		s13HoudaiFumiEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13HoudaiFumiCtorEntry)(void) = s13HoudaiFumiRegister;
