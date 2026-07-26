#include "types.h"

// CASE OBJECT's factory and the record that registers the class.
//
// The claim is .text 0x415B0 to 0x416A0 and the .ctors word that names the
// registration. Both are the shape every TObj* in the module repeats: allocate
// 0x100 bytes and hand them to the constructor, then fill a 0x2C record in .bss
// with the display name, the three hooks and the editor's field layout.
//
// The run is the same in nine of the fourteen stage modules. stage13D, 26D, 27D
// and 28D are built from a different revision this far in, and stage40D
// everywhere, so those five are left out.
//
// "fffCc" is the field type string: one character per parameter the editor
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
extern "C" void* caseObjCtor(void* object, void* owner);
extern "C" void caseObjLoad(void);
extern "C" void caseObjUnload(void);
extern "C" ObjectEntry caseObjEntry;
extern "C" char caseObjDisplayName[];
extern "C" char caseObjFieldTypes[];
extern "C" const char* caseObjFieldNames[];

extern "C" void caseObjCreate(void)
{
	void* memory = fn_80018A34(lbl_8042C148, 0x100);

	if (memory != NULL) {
		caseObjCtor(memory, lbl_8042C110);
	}
}

extern "C" void caseObjRegister(void)
{
	caseObjEntry.flags = 0;
	caseObjEntry.unk18 = 0;

	caseObjEntry.name   = caseObjDisplayName;
	caseObjEntry.load   = caseObjLoad;
	caseObjEntry.unload = caseObjUnload;
	caseObjEntry.create = caseObjCreate;
	caseObjEntry.unk10  = NULL;

	caseObjEntry.flags = 0x20000;
	caseObjEntry.unk18 = 0;
	caseObjEntry.unk20 = 0x1E;
	caseObjEntry.unk1C = 0x31;
	caseObjEntry.unk1E = 2;
	caseObjEntry.unk21 = 0;

	caseObjEntry.fieldTypes = caseObjFieldTypes;
	caseObjEntry.fieldNames = caseObjFieldNames;

	if (caseObjFieldTypes != NULL) {
		caseObjEntry.flags |= 8;
	} else {
		caseObjEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const caseObjCtorEntry)(void) = caseObjRegister;
