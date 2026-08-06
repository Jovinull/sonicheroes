#include "types.h"

// The record that registers RAILPOLLGOL with the editor.
//
// The claim is .text 0x89F1C to 0x89FBC and the .ctors word that names it.
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
extern "C" void railpollgolLoad(void);
extern "C" void railpollgolUnload(void);
extern "C" void railpollgolCreate(void);
extern "C" void railpollgolReset(void);
extern "C" ObjectEntry railpollgolEntry;
extern "C" char railpollgolDisplayName[];

extern "C" void railpollgolRegister(void)
{
	railpollgolEntry.flags = 0;
	railpollgolEntry.unk18 = 0;

	railpollgolEntry.name   = railpollgolDisplayName;
	railpollgolEntry.load   = railpollgolLoad;
	railpollgolEntry.unload = railpollgolUnload;
	railpollgolEntry.create = railpollgolCreate;
	railpollgolEntry.reset  = railpollgolReset;

	railpollgolEntry.flags = 0x1000;
	railpollgolEntry.unk18 = 0;
	railpollgolEntry.unk20 = 0xf;
	railpollgolEntry.unk1C = 0x78d;
	railpollgolEntry.unk1E = 2;
	railpollgolEntry.unk21 = 0;

	railpollgolEntry.fieldTypes = NULL;
	railpollgolEntry.fieldNames = NULL;

	if (railpollgolEntry.fieldTypes != NULL) {
		railpollgolEntry.flags |= 8;
	} else {
		railpollgolEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const railpollgolCtorEntry)(void) = railpollgolRegister;
