#include "types.h"

// TObjBushsq's destructor (bushsqDtor here; the class name its constructor
// stores is "TObjBushSq"). It restores both vtables (the object's and its
// TObjSetObj base's at 0x28, 0xB words further), takes its clump out of the
// model file's world slot if it was added, destroys it and clears both
// fields, as TObjWaterPlant's destructor does (rel/water_plant_dtor.cpp), then
// runs the two bases down and frees the object when the delete flag asks for
// it. The model file's address is taken once, before the test.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject;

typedef struct SetObj {
	void* frame;   // 0x00
	void** vtable; // 0x04
} SetObj;

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
typedef struct BushsqModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
} BushsqModelFile;

typedef struct Bushsq {
	TObject base;   // 0x00
	SetObj setObj;  // 0x28
	u8 unk30[0x18]; // 0x30
	void* clump;    // 0x48
	s32 added;      // 0x4C
} Bushsq;

extern "C" void* lbl_8042C148;
extern "C" u8* lbl_8042C1D0;
extern "C" void* bushsqVtable[];
extern "C" BushsqModelFile bushsqModelFile;

extern "C" void fn_8015BBF8(void* world, void* clump);
extern "C" void fn_80150958(void* clump);
extern "C" void __dt__10TObjSetObjFv(SetObj* setObj, s32 flags);
extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);

extern "C" Bushsq* bushsqDtor(Bushsq* object, s16 flags)
{
	if (object != NULL) {
		BushsqModelFile* file;

		object->base.vtable   = bushsqVtable;
		object->setObj.vtable = bushsqVtable + 0xB;

		file = &bushsqModelFile;
		if (object->added == 1) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), object->clump);
			object->added = 0;
		}
		fn_80150958(object->clump);
		object->clump = NULL;

		__dt__10TObjSetObjFv(&object->setObj, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
