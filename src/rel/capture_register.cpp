#include "types.h"

// The record that registers CAPTURE OBJECT with the editor.
//
// The claim is .text 0xBBFA0 to 0xBC09C and the .ctors word that names it.
// Only the record is taken: the hooks it points at stay assembly and are
// reached by the names each module's symbols.txt gives them.
//
// The object's name is the display string the record itself installs, and each
// hook is named from the entry offset it is stored into.
//
// Ahead of the record the run builds an array of eight objects of 0x14 bytes
// and queues one destructor for the whole array, which is what CodeWarrior
// emits for an array at file scope whose element class has a destructor. The
// class lives in main.dol, so the calls are written out the way
// src/game/e_paralysis.cpp already writes this idiom rather than declared as a
// type; that also keeps the array-destruction stub the retail emits just past
// this claim out of the object.
//
// "ccccfffif" is the field type string: one character per parameter the
// editor shows, and the array beside it holds their labels.
//
// The run is the same in seven of the fourteen stage modules: 03D, 05D, 07D, 09D, 11D, 13D and 26D.

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

extern "C" void captureObjectLoad(void);
extern "C" void captureObjectUnload(void);
extern "C" void captureObjectCreate(void);
extern "C" u8 captureObjectGlobalArray[];
extern "C" u8 captureObjectGlobalArrayChain[];
extern "C" void captureObjectGlobalArrayDtor(void);
extern "C" ObjectEntry captureObjectEntry;
extern "C" char captureObjectDisplayName[];
extern "C" char captureObjectFieldTypes[];
extern "C" const char* captureObjectFieldNames[];

extern "C" void captureObjectRegister(void)
{
	__construct_array(captureObjectGlobalArray, (void*)fn_80113C7C, (void*)fn_80113C2C, 0x14, 8);
	__register_global_object(
	    NULL, (void*)captureObjectGlobalArrayDtor, captureObjectGlobalArrayChain);

	captureObjectEntry.flags = 0;
	captureObjectEntry.unk18 = 0;

	captureObjectEntry.name   = captureObjectDisplayName;
	captureObjectEntry.load   = captureObjectLoad;
	captureObjectEntry.unload = captureObjectUnload;
	captureObjectEntry.create = captureObjectCreate;
	captureObjectEntry.reset  = NULL;

	captureObjectEntry.flags = 0x20000;
	captureObjectEntry.unk18 = 0;
	captureObjectEntry.unk20 = 0x1e;
	captureObjectEntry.unk1C = 0x1520;
	captureObjectEntry.unk1E = 4;
	captureObjectEntry.unk21 = 0;

	captureObjectEntry.fieldTypes = captureObjectFieldTypes;
	captureObjectEntry.fieldNames = captureObjectFieldNames;

	if (captureObjectFieldTypes != NULL) {
		captureObjectEntry.flags |= 8;
	} else {
		captureObjectEntry.flags &= ~8;
	}
}

__declspec(section ".ctors") void (*const captureObjectCtorEntry)(void) = captureObjectRegister;
