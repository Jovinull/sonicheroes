#include "types.h"

// The record that registers S04D Shutter with the editor.
//
// The claim is .text 0x99914 to 0x999BC and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "c" is the field type string: one character per parameter the
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
extern "C" void s04dShutterLoad(void);
extern "C" void s04dShutterUnload(void);
extern "C" void s04dShutterCreate(void);
extern "C" ObjectEntry s04dShutterEntry;
extern "C" char s04dShutterDisplayName[];
extern "C" char s04dShutterFieldTypes[];
extern "C" const char* s04dShutterFieldNames[];

extern "C" void s04dShutterRegister(void)
{
	s04dShutterEntry.flags = 0;
	s04dShutterEntry.unk18 = 0;

	s04dShutterEntry.name   = s04dShutterDisplayName;
	s04dShutterEntry.load   = s04dShutterLoad;
	s04dShutterEntry.unload = s04dShutterUnload;
	s04dShutterEntry.create = s04dShutterCreate;
	s04dShutterEntry.reset  = NULL;

	s04dShutterEntry.flags = 0x20000;
	s04dShutterEntry.unk18 = 0;
	s04dShutterEntry.unk20 = 0xa;
	s04dShutterEntry.unk1C = 0x410;
	s04dShutterEntry.unk1E = 2;
	s04dShutterEntry.unk21 = 0;

	s04dShutterEntry.fieldTypes = s04dShutterFieldTypes;
	s04dShutterEntry.fieldNames = s04dShutterFieldNames;

	if (s04dShutterFieldTypes != NULL) {
		s04dShutterEntry.flags |= 8;
	} else {
		s04dShutterEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04dShutterCtorEntry)(void) = s04dShutterRegister;
