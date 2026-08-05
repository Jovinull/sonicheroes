#include "types.h"

// The record that registers S20D LightHouse  with the editor.
//
// The claim is .text 0xBCB98 to 0xBCC34 and the .ctors word at 0x144 that names
// it. Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, which is
// what names every symbol here, and each hook is named from the entry offset it
// is stored into.
//
// It shows no editor fields, so the type and label slots take NULL. The flags word is 0x1021000; its width is what sets this run's length apart
// from others of the same shape.
//
// The .ctors slot is derived: every function owning a .ctors word, sorted by run
// address, at position times four.
//
// Only stage01D carries this run.

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

// Defined by the module, renamed to these names in its own symbols.txt.
extern "C" void s20dLighthouseLoad(void);
extern "C" void s20dLighthouseUnload(void);
extern "C" void s20dLighthouseCreate(void);
extern "C" ObjectEntry s20dLighthouseEntry;
extern "C" char s20dLighthouseDisplayName[];

extern "C" void s20dLighthouseRegister(void)
{
	s20dLighthouseEntry.flags = 0;
	s20dLighthouseEntry.unk18 = 0;

	s20dLighthouseEntry.name   = s20dLighthouseDisplayName;
	s20dLighthouseEntry.load   = s20dLighthouseLoad;
	s20dLighthouseEntry.unload = s20dLighthouseUnload;
	s20dLighthouseEntry.create = s20dLighthouseCreate;
	s20dLighthouseEntry.reset  = NULL;

	s20dLighthouseEntry.flags = 0x1021000;
	s20dLighthouseEntry.unk18 = 0;
	s20dLighthouseEntry.unk20 = 20;
	s20dLighthouseEntry.unk1C = 8322;
	s20dLighthouseEntry.unk1E = 2;
	s20dLighthouseEntry.unk21 = 0;

	s20dLighthouseEntry.fieldTypes = NULL;
	s20dLighthouseEntry.fieldNames = NULL;

	if (s20dLighthouseEntry.fieldTypes != NULL) {
		s20dLighthouseEntry.flags |= 8;
	} else {
		s20dLighthouseEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const s20dLighthouseCtorEntry)(void) = s20dLighthouseRegister;
