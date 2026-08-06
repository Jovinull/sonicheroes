#include "types.h"

// The record that registers E2000 OBJECT with the editor.
//
// The claim is .text 0xB2370 to 0xB246C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// Ahead of the record the run builds an array of file-scope objects the same
// way rel/capture_register.cpp does; see that file for why the calls are
// written out rather than declared as a type.
//
// "ccccfffiif" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in two of the fourteen stage modules: 13D and 26D.

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
extern "C" {
void* fn_80113C7C(void*);
void fn_80113C2C(void*, s16);
void __construct_array(void*, void*, void*, s32, s32);
void __register_global_object(void*, void*, void*);
}

extern "C" void e2000ObjectLoad(void);
extern "C" void e2000ObjectUnload(void);
extern "C" void e2000ObjectCreate(void);
extern "C" u8 e2000ObjectGlobalArray[];
extern "C" u8 e2000ObjectGlobalArrayChain[];
extern "C" void e2000ObjectGlobalArrayDtor(void);
extern "C" ObjectEntry e2000ObjectEntry;
extern "C" char e2000ObjectDisplayName[];
extern "C" char e2000ObjectFieldTypes[];
extern "C" const char* e2000ObjectFieldNames[];

extern "C" void e2000ObjectRegister(void)
{
	__construct_array(e2000ObjectGlobalArray, (void*)fn_80113C7C, (void*)fn_80113C2C, 0x14, 4);
	__register_global_object(NULL, (void*)e2000ObjectGlobalArrayDtor, e2000ObjectGlobalArrayChain);

	e2000ObjectEntry.flags = 0;
	e2000ObjectEntry.unk18 = 0;

	e2000ObjectEntry.name   = e2000ObjectDisplayName;
	e2000ObjectEntry.load   = e2000ObjectLoad;
	e2000ObjectEntry.unload = e2000ObjectUnload;
	e2000ObjectEntry.create = e2000ObjectCreate;
	e2000ObjectEntry.reset  = NULL;

	e2000ObjectEntry.flags = 0x20000;
	e2000ObjectEntry.unk18 = 0;
	e2000ObjectEntry.unk20 = 0x1e;
	e2000ObjectEntry.unk1C = 0x15d0;
	e2000ObjectEntry.unk1E = 4;
	e2000ObjectEntry.unk21 = 0x0;

	e2000ObjectEntry.fieldTypes = e2000ObjectFieldTypes;
	e2000ObjectEntry.fieldNames = e2000ObjectFieldNames;

	if (e2000ObjectFieldTypes != NULL) {
		e2000ObjectEntry.flags |= 8;
	} else {
		e2000ObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const e2000ObjectCtorEntry)(void) = e2000ObjectRegister;
