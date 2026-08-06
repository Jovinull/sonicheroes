#include "types.h"

// The record that registers HINTRING OBJECT with the editor.
//
// The claim is .text 0x707DC to 0x708B0 and the .ctors word that names it. Only
// the record is taken: the four hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The run is the same in thirteen of the fourteen stage modules. stage40D
// registers the same object from a different build and does not share it.
//
// Unlike the other records this one does something before filling the entry: it
// copies the class's model handle into two resource descriptors that live in
// .data. Their layout is not identified beyond that slot, so they are declared
// only as far as the record reaches into them. Both take the same handle, and
// the compiler reads it once and stores it twice.
//
// "Sc" is the field type string: one character per parameter the editor shows,
// and the array beside it holds their labels.

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

typedef struct ObjectResource {
	u8 unk00[0xC]; // 0x00
	void* model;   // 0x0C
	u8 unk10[0x8]; // 0x10
} ObjectResource;  // 0x18

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void hintringObjectLoad(void);
extern "C" void hintringObjectUnload(void);
extern "C" void hintringObjectCreate(void);
extern "C" void hintringObjectReset(void);
extern "C" ObjectEntry hintringObjectEntry;
extern "C" ObjectResource hintringObjectResourceA;
extern "C" ObjectResource hintringObjectResourceB;
extern "C" void* hintringObjectModel;
extern "C" char hintringObjectDisplayName[];
extern "C" char hintringObjectFieldTypes[];
extern "C" const char* hintringObjectFieldNames[];

extern "C" void hintringObjectRegister(void)
{
	hintringObjectResourceA.model = hintringObjectModel;
	hintringObjectResourceB.model = hintringObjectModel;

	hintringObjectEntry.flags = 0;
	hintringObjectEntry.unk18 = 0;

	hintringObjectEntry.name   = hintringObjectDisplayName;
	hintringObjectEntry.load   = hintringObjectLoad;
	hintringObjectEntry.unload = hintringObjectUnload;
	hintringObjectEntry.create = hintringObjectCreate;
	hintringObjectEntry.reset  = hintringObjectReset;

	hintringObjectEntry.flags = 0x20000;
	hintringObjectEntry.unk18 = 0;
	hintringObjectEntry.unk20 = 0x1E;
	hintringObjectEntry.unk1C = 4;
	hintringObjectEntry.unk1E = 2;
	hintringObjectEntry.unk21 = 0;

	hintringObjectEntry.fieldTypes = hintringObjectFieldTypes;
	hintringObjectEntry.fieldNames = hintringObjectFieldNames;

	if (hintringObjectFieldTypes != NULL) {
		hintringObjectEntry.flags |= 8;
	} else {
		hintringObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const hintringObjectCtorEntry)(void) = hintringObjectRegister;
