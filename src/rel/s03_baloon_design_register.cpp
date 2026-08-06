#include "types.h"

// The record that registers S03 Baloon Design with the editor.
//
// The claim is .text 0x74764 to 0x74810 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cxff" is the field type string: one character per parameter the
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
extern "C" void s03BaloonDesignLoad(void);
extern "C" void s03BaloonDesignUnload(void);
extern "C" void s03BaloonDesignCreate(void);
extern "C" ObjectEntry s03BaloonDesignEntry;
extern "C" char s03BaloonDesignDisplayName[];
extern "C" char s03BaloonDesignFieldTypes[];
extern "C" const char* s03BaloonDesignFieldNames[];

extern "C" void s03BaloonDesignRegister(void)
{
	s03BaloonDesignEntry.flags = 0;
	s03BaloonDesignEntry.unk18 = 0;

	s03BaloonDesignEntry.name   = s03BaloonDesignDisplayName;
	s03BaloonDesignEntry.load   = s03BaloonDesignLoad;
	s03BaloonDesignEntry.unload = s03BaloonDesignUnload;
	s03BaloonDesignEntry.create = s03BaloonDesignCreate;
	s03BaloonDesignEntry.reset  = NULL;

	s03BaloonDesignEntry.flags = 0x20400;
	s03BaloonDesignEntry.unk18 = 0;
	s03BaloonDesignEntry.unk20 = 0x14;
	s03BaloonDesignEntry.unk1C = 0x380;
	s03BaloonDesignEntry.unk1E = 2;
	s03BaloonDesignEntry.unk21 = 0;

	s03BaloonDesignEntry.fieldTypes = s03BaloonDesignFieldTypes;
	s03BaloonDesignEntry.fieldNames = s03BaloonDesignFieldNames;

	if (s03BaloonDesignFieldTypes != NULL) {
		s03BaloonDesignEntry.flags |= 8;
	} else {
		s03BaloonDesignEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03BaloonDesignCtorEntry)(void) = s03BaloonDesignRegister;
