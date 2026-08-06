#include "types.h"

// The record that registers S03 PIPE with the editor.
//
// The claim is .text 0x8228C to 0x82334 and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// "cff" is the field type string: one character per parameter the
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
extern "C" void s03PipeLoad(void);
extern "C" void s03PipeUnload(void);
extern "C" void s03PipeCreate(void);
extern "C" ObjectEntry s03PipeEntry;
extern "C" char s03PipeDisplayName[];
extern "C" char s03PipeFieldTypes[];
extern "C" const char* s03PipeFieldNames[];

extern "C" void s03PipeRegister(void)
{
	s03PipeEntry.flags = 0;
	s03PipeEntry.unk18 = 0;

	s03PipeEntry.name   = s03PipeDisplayName;
	s03PipeEntry.load   = s03PipeLoad;
	s03PipeEntry.unload = s03PipeUnload;
	s03PipeEntry.create = s03PipeCreate;
	s03PipeEntry.reset  = NULL;

	s03PipeEntry.flags = 0x20000;
	s03PipeEntry.unk18 = 0;
	s03PipeEntry.unk20 = 0x14;
	s03PipeEntry.unk1C = 0x300;
	s03PipeEntry.unk1E = 2;
	s03PipeEntry.unk21 = 0;

	s03PipeEntry.fieldTypes = s03PipeFieldTypes;
	s03PipeEntry.fieldNames = s03PipeFieldNames;

	if (s03PipeFieldTypes != NULL) {
		s03PipeEntry.flags |= 8;
	} else {
		s03PipeEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s03PipeCtorEntry)(void) = s03PipeRegister;
