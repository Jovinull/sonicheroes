#include "types.h"

// The record that registers SEARCHER OBJECT with the editor, and the two
// file-scope objects the same translation unit constructs.
//
// The claim is .text 0x5A440 to 0x5A540 and the .ctors word that names it. Only
// the initializer is taken: the three hooks the record points at stay assembly
// and are reached by the names each module's symbols.txt gives them.
//
// The run is the same in eight of the fourteen stage modules: 01D, 03D, 05D,
// 07D, 09D, 11D, 13D and 26D. The other six build this area differently.
//
// The two constructions ahead of the record are what CodeWarrior emits for two
// objects at file scope whose class has a destructor: the constructor runs, and
// the destructor is queued on the global chain. The class itself lives in
// main.dol and is not reconstructible from here, so the calls are written out
// the way src/game/e_paralysis.cpp already writes this idiom rather than
// declared as a type.
//
// "ccccssssffffss" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.

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

extern "C" {
void* fn_80113C7C(void*);
void fn_80113C2C(void*, s16);
void __register_global_object(void*, void*, void*);
}

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void searcherObjectLoad(void);
extern "C" void searcherObjectUnload(void);
extern "C" void searcherObjectCreate(void);
extern "C" ObjectEntry searcherObjectEntry;
extern "C" char searcherObjectDisplayName[];
extern "C" char searcherObjectFieldTypes[];
extern "C" const char* searcherObjectFieldNames[];
extern "C" u8 searcherObjectGlobalA[];
extern "C" u8 searcherObjectGlobalAChain[];
extern "C" u8 searcherObjectGlobalB[];
extern "C" u8 searcherObjectGlobalBChain[];

extern "C" void searcherObjectRegister(void)
{
	void* a = fn_80113C7C(searcherObjectGlobalA);
	__register_global_object(a, (void*)fn_80113C2C, searcherObjectGlobalAChain);

	void* b = fn_80113C7C(searcherObjectGlobalB);
	__register_global_object(b, (void*)fn_80113C2C, searcherObjectGlobalBChain);

	searcherObjectEntry.flags = 0;
	searcherObjectEntry.unk18 = 0;

	searcherObjectEntry.name   = searcherObjectDisplayName;
	searcherObjectEntry.load   = searcherObjectLoad;
	searcherObjectEntry.unload = searcherObjectUnload;
	searcherObjectEntry.create = searcherObjectCreate;
	searcherObjectEntry.reset  = NULL;

	searcherObjectEntry.flags = 0x20000;
	searcherObjectEntry.unk18 = 0;
	searcherObjectEntry.unk20 = 0x1E;
	searcherObjectEntry.unk1C = 0x1500;
	searcherObjectEntry.unk1E = 4;
	searcherObjectEntry.unk21 = 0;

	searcherObjectEntry.fieldTypes = searcherObjectFieldTypes;
	searcherObjectEntry.fieldNames = searcherObjectFieldNames;

	if (searcherObjectFieldTypes != NULL) {
		searcherObjectEntry.flags |= 8;
	} else {
		searcherObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const searcherObjectCtorEntry)(void) = searcherObjectRegister;
