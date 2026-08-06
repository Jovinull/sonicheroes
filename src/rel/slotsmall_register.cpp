#include "types.h"

// The record that registers SLOTSMALL with the editor.
//
// The claim is .text 0x99200 to 0x992B0 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "F" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// Only stage05D carries this run.

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
extern "C" void slotsmallLoad(void);
extern "C" void slotsmallUnload(void);
extern "C" void slotsmallCreate(void);
extern "C" void slotsmallReset(void);
extern "C" ObjectEntry slotsmallEntry;
extern "C" char slotsmallDisplayName[];
extern "C" char slotsmallFieldTypes[];
extern "C" const char* slotsmallFieldNames[];

extern "C" void slotsmallRegister(void)
{
	slotsmallEntry.flags = 0;
	slotsmallEntry.unk18 = 0;

	slotsmallEntry.name   = slotsmallDisplayName;
	slotsmallEntry.load   = slotsmallLoad;
	slotsmallEntry.unload = slotsmallUnload;
	slotsmallEntry.create = slotsmallCreate;
	slotsmallEntry.reset  = slotsmallReset;

	slotsmallEntry.flags = 0x20000;
	slotsmallEntry.unk18 = 0;
	slotsmallEntry.unk20 = 0xf;
	slotsmallEntry.unk1C = 0x50c;
	slotsmallEntry.unk1E = 2;
	slotsmallEntry.unk21 = 0;

	slotsmallEntry.fieldTypes = slotsmallFieldTypes;
	slotsmallEntry.fieldNames = slotsmallFieldNames;

	if (slotsmallFieldTypes != NULL) {
		slotsmallEntry.flags |= 8;
	} else {
		slotsmallEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const slotsmallCtorEntry)(void) = slotsmallRegister;
