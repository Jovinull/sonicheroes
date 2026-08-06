#include "types.h"

// The record that registers RAILPOLLGOR with the editor.
//
// The claim is .text 0x8AB80 to 0x8AC20 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// The object exposes no parameter to the editor, so the type string and the
// label array are null.
//
// Only stage07D carries this run.

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
extern "C" void railpollgorLoad(void);
extern "C" void railpollgorUnload(void);
extern "C" void railpollgorCreate(void);
extern "C" void railpollgorReset(void);
extern "C" ObjectEntry railpollgorEntry;
extern "C" char railpollgorDisplayName[];

extern "C" void railpollgorRegister(void)
{
	railpollgorEntry.flags = 0;
	railpollgorEntry.unk18 = 0;

	railpollgorEntry.name   = railpollgorDisplayName;
	railpollgorEntry.load   = railpollgorLoad;
	railpollgorEntry.unload = railpollgorUnload;
	railpollgorEntry.create = railpollgorCreate;
	railpollgorEntry.reset  = railpollgorReset;

	railpollgorEntry.flags = 0x1000;
	railpollgorEntry.unk18 = 0;
	railpollgorEntry.unk20 = 0xf;
	railpollgorEntry.unk1C = 0x78e;
	railpollgorEntry.unk1E = 2;
	railpollgorEntry.unk21 = 0;

	railpollgorEntry.fieldTypes = NULL;
	railpollgorEntry.fieldNames = NULL;

	if (railpollgorEntry.fieldTypes != NULL) {
		railpollgorEntry.flags |= 8;
	} else {
		railpollgorEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const railpollgorCtorEntry)(void) = railpollgorRegister;
