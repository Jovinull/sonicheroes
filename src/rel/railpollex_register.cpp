#include "types.h"

// The record that registers RAILPOLLEX with the editor.
//
// The claim is .text 0x892B8 to 0x89358 and the .ctors word that names it.
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
extern "C" void railpollexLoad(void);
extern "C" void railpollexUnload(void);
extern "C" void railpollexCreate(void);
extern "C" void railpollexReset(void);
extern "C" ObjectEntry railpollexEntry;
extern "C" char railpollexDisplayName[];

extern "C" void railpollexRegister(void)
{
	railpollexEntry.flags = 0;
	railpollexEntry.unk18 = 0;

	railpollexEntry.name   = railpollexDisplayName;
	railpollexEntry.load   = railpollexLoad;
	railpollexEntry.unload = railpollexUnload;
	railpollexEntry.create = railpollexCreate;
	railpollexEntry.reset  = railpollexReset;

	railpollexEntry.flags = 0x1000;
	railpollexEntry.unk18 = 0;
	railpollexEntry.unk20 = 0xf;
	railpollexEntry.unk1C = 0x78c;
	railpollexEntry.unk1E = 2;
	railpollexEntry.unk21 = 0;

	railpollexEntry.fieldTypes = NULL;
	railpollexEntry.fieldNames = NULL;

	if (railpollexEntry.fieldTypes != NULL) {
		railpollexEntry.flags |= 8;
	} else {
		railpollexEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const railpollexCtorEntry)(void) = railpollexRegister;
