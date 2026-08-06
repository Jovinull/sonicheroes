#include "types.h"

// The record that registers S13 SENKAN MOV with the editor.
//
// The claim is .text 0x84660 to 0x84708 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "ffff" is the field type string: one character per parameter the
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
extern "C" void s13SenkanMovLoad(void);
extern "C" void s13SenkanMovUnload(void);
extern "C" void s13SenkanMovCreate(void);
extern "C" ObjectEntry s13SenkanMovEntry;
extern "C" char s13SenkanMovDisplayName[];
extern "C" char s13SenkanMovFieldTypes[];
extern "C" const char* s13SenkanMovFieldNames[];

extern "C" void s13SenkanMovRegister(void)
{
	s13SenkanMovEntry.flags = 0;
	s13SenkanMovEntry.unk18 = 0;

	s13SenkanMovEntry.name   = s13SenkanMovDisplayName;
	s13SenkanMovEntry.load   = s13SenkanMovLoad;
	s13SenkanMovEntry.unload = s13SenkanMovUnload;
	s13SenkanMovEntry.create = s13SenkanMovCreate;
	s13SenkanMovEntry.reset  = NULL;

	s13SenkanMovEntry.flags = 0x20000;
	s13SenkanMovEntry.unk18 = 0;
	s13SenkanMovEntry.unk20 = 0x14;
	s13SenkanMovEntry.unk1C = 0x1304;
	s13SenkanMovEntry.unk1E = 2;
	s13SenkanMovEntry.unk21 = 0;

	s13SenkanMovEntry.fieldTypes = s13SenkanMovFieldTypes;
	s13SenkanMovEntry.fieldNames = s13SenkanMovFieldNames;

	if (s13SenkanMovFieldTypes != NULL) {
		s13SenkanMovEntry.flags |= 8;
	} else {
		s13SenkanMovEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s13SenkanMovCtorEntry)(void) = s13SenkanMovRegister;
