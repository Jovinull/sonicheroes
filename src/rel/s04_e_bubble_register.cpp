#include "types.h"

// The record that registers S04 EBubble with the editor.
//
// The claim is .text 0x89ED0 to 0x89F78 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "xxf" is the field type string: one character per parameter the
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
extern "C" void s04EBubbleLoad(void);
extern "C" void s04EBubbleUnload(void);
extern "C" void s04EBubbleCreate(void);
extern "C" ObjectEntry s04EBubbleEntry;
extern "C" char s04EBubbleDisplayName[];
extern "C" char s04EBubbleFieldTypes[];
extern "C" const char* s04EBubbleFieldNames[];

extern "C" void s04EBubbleRegister(void)
{
	s04EBubbleEntry.flags = 0;
	s04EBubbleEntry.unk18 = 0;

	s04EBubbleEntry.name   = s04EBubbleDisplayName;
	s04EBubbleEntry.load   = s04EBubbleLoad;
	s04EBubbleEntry.unload = s04EBubbleUnload;
	s04EBubbleEntry.create = s04EBubbleCreate;
	s04EBubbleEntry.reset  = NULL;

	s04EBubbleEntry.flags = 0x20000;
	s04EBubbleEntry.unk18 = 0;
	s04EBubbleEntry.unk20 = 0xa;
	s04EBubbleEntry.unk1C = 0x406;
	s04EBubbleEntry.unk1E = 2;
	s04EBubbleEntry.unk21 = 0;

	s04EBubbleEntry.fieldTypes = s04EBubbleFieldTypes;
	s04EBubbleEntry.fieldNames = s04EBubbleFieldNames;

	if (s04EBubbleFieldTypes != NULL) {
		s04EBubbleEntry.flags |= 8;
	} else {
		s04EBubbleEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s04EBubbleCtorEntry)(void) = s04EBubbleRegister;
