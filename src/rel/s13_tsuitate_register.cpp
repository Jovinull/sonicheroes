#include "types.h"

// The record that registers S13 TSUITATE with the editor.
//
// The claim is .text 0x84FE4 to 0x8507C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
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
extern "C" void s13TsuitateLoad(void);
extern "C" void s13TsuitateUnload(void);
extern "C" void s13TsuitateCreate(void);
extern "C" ObjectEntry s13TsuitateEntry;
extern "C" char s13TsuitateDisplayName[];

extern "C" void s13TsuitateRegister(void)
{
	s13TsuitateEntry.flags = 0;
	s13TsuitateEntry.unk18 = 0;

	s13TsuitateEntry.name   = s13TsuitateDisplayName;
	s13TsuitateEntry.load   = s13TsuitateLoad;
	s13TsuitateEntry.unload = s13TsuitateUnload;
	s13TsuitateEntry.create = s13TsuitateCreate;
	s13TsuitateEntry.reset  = NULL;

	s13TsuitateEntry.flags = 0x20000;
	s13TsuitateEntry.unk18 = 0;
	s13TsuitateEntry.unk20 = 0x14;
	s13TsuitateEntry.unk1C = 0x1307;
	s13TsuitateEntry.unk1E = 2;
	s13TsuitateEntry.unk21 = 0;

	s13TsuitateEntry.fieldTypes = NULL;
	s13TsuitateEntry.fieldNames = NULL;

	if (s13TsuitateEntry.fieldTypes != NULL) {
		s13TsuitateEntry.flags |= 8;
	} else {
		s13TsuitateEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13TsuitateCtorEntry)(void) = s13TsuitateRegister;
