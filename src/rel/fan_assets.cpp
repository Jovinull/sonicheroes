#include "types.h"

// FAN OBJECT's factory and the record that registers the class.
//
// The claim is .text 0x25810 to 0x25900 and the .ctors word that names the
// registration. Both are the shape every TObj* in the module repeats: allocate
// 0xFC bytes and hand them to the constructor, then fill a 0x2C record in .bss
// with the display name, the three hooks and the editor's field layout.
//
// The run is the same in twelve of the fourteen stage modules. stage13D is
// built from a different revision here, and stage40D everywhere, so both are
// left out.
//
// "ffffcCfc" is the field type string: one character per parameter the editor
// shows, and the array beside it holds their labels.

typedef struct ObjectEntry {
	const char* name;        // 0x00
	void (*load)(void);      // 0x04
	void (*unload)(void);    // 0x08
	void (*create)(void);    // 0x0C
	void* unk10;             // 0x10
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

extern "C" void* lbl_8042C110;
extern "C" void* lbl_8042C148;

extern "C" void* fn_80018A34(void* heap, u32 size);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* fanCtor(void* object, void* owner);
extern "C" void fanLoad(void);
extern "C" void fanUnload(void);
extern "C" ObjectEntry fanEntry;
extern "C" char fanDisplayName[];
extern "C" char fanFieldTypes[];
extern "C" const char* fanFieldNames[];

extern "C" void fanCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0xFC);

	if (memory != NULL) {
		fanCtor(memory, lbl_8042C110);
	}
}

extern "C" void fanRegister(void)
{
	fanEntry.flags = 0;
	fanEntry.unk18 = 0;

	fanEntry.name   = fanDisplayName;
	fanEntry.load   = fanLoad;
	fanEntry.unload = fanUnload;
	fanEntry.create = fanCreate;
	fanEntry.unk10  = NULL;

	fanEntry.flags = 0x20000;
	fanEntry.unk18 = 0;
	fanEntry.unk20 = 0x1E;
	fanEntry.unk1C = 0x2E;
	fanEntry.unk1E = 2;
	fanEntry.unk21 = 0;

	fanEntry.fieldTypes = fanFieldTypes;
	fanEntry.fieldNames = fanFieldNames;

	if (fanFieldTypes != NULL) {
		fanEntry.flags |= 8;
	} else {
		fanEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const fanCtorEntry)(void) = fanRegister;
