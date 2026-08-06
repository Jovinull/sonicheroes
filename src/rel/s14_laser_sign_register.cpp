#include "types.h"

// The record that registers S14 LaserSign with the editor.
//
// The claim is .text 0xA6D14 to 0xA6DC0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "c" is the field type string: one character per parameter the
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
extern "C" void s14LaserSignLoad(void);
extern "C" void s14LaserSignUnload(void);
extern "C" void s14LaserSignCreate(void);
extern "C" ObjectEntry s14LaserSignEntry;
extern "C" char s14LaserSignDisplayName[];
extern "C" char s14LaserSignFieldTypes[];
extern "C" const char* s14LaserSignFieldNames[];

extern "C" void s14LaserSignRegister(void)
{
	s14LaserSignEntry.flags = 0;
	s14LaserSignEntry.unk18 = 0;

	s14LaserSignEntry.name   = s14LaserSignDisplayName;
	s14LaserSignEntry.load   = s14LaserSignLoad;
	s14LaserSignEntry.unload = s14LaserSignUnload;
	s14LaserSignEntry.create = s14LaserSignCreate;
	s14LaserSignEntry.reset  = NULL;

	s14LaserSignEntry.flags = 0x20000;
	s14LaserSignEntry.unk18 = 0;
	s14LaserSignEntry.unk20 = 0x32;
	s14LaserSignEntry.unk1C = 0x1404;
	s14LaserSignEntry.unk1E = 2;
	s14LaserSignEntry.unk21 = 0x64;

	s14LaserSignEntry.fieldTypes = s14LaserSignFieldTypes;
	s14LaserSignEntry.fieldNames = s14LaserSignFieldNames;

	if (s14LaserSignFieldTypes != NULL) {
		s14LaserSignEntry.flags |= 8;
	} else {
		s14LaserSignEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s14LaserSignCtorEntry)(void) = s14LaserSignRegister;
