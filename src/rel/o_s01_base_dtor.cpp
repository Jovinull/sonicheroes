#include "types.h"

// The destructor of the base class the stage-01 objects derive from. It
// restores both vtable pointers, releases the handle it registered, runs the
// embedded volume and motion bases down and then the object base, and hands the
// object back to the heap when the caller asks for it.
//
// That it is a base rather than an object of its own is read from its callers:
// rel/o_s01_ciseki.cpp and rel/o_s01_shachicolli.cpp each end their own
// destructor with a call to it, and each also declares the constructor at
// 0x0007CB30 and the method at 0x0007C9CC. The constructor confirms the shape,
// running __ct__7TObjectFP7TObject, the motion constructor at +0x28 and the
// volume constructor at +0x30 before installing the two vtable pointers.
//
// The claim is .text 0x0007CA7C to 0x0007CB30 and nothing else. The vtable
// stays in the module's data and is renamed to the name below; the function
// reads no constant, so it owns no rodata.
//
// The class name could not be recovered. `__ct__7TObjectFP7TObject` sets the
// name field and the base's own constructor does not overwrite it, and the only
// strings the unit owns are the editor parameter labels "SCALE X", "SCALE Y"
// and "SCALE Z", which are not specific to it. The names here describe the role
// and are provisional; renaming them is mechanical once the class is
// identified.
//
// Only stage01D claims this run, like the other o_s01_* units around it.
//
// The enclosing translation unit is .text 0x0007C9CC to 0x0007D9A0, argued
// from two independent readings rather than from address proximity:
// `o_s01_ciseki.cpp` takes .ctors slot 0xC4 and `o_s01_hana.cpp` takes 0xD0,
// leaving 0xC8 and 0xCC for exactly two units in the gap; and the private data
// the gap's functions share falls into two clusters, the first ending at
// 0x0007D66C and the second beginning at 0x0007D9A0, with no span crossing
// between them. The unit's static initializer sits at 0x0007D8BC inside that
// quiet zone, and an eight byte adjustor thunk at 0x0007D968 closes it, which
// is the tail shape `o_s01_ciseki.cpp` also has. Only the destructor is
// reconstructed here; the rest of the unit is still assembly.
//
// Same shape as rel/ironball_dtor.cpp, with one difference: where that one
// releases five meshes through a loop, this one releases a single handle.
//
// The delete flag is a short. It is sign extended before the test, so a plain
// s32 parameter does not reproduce the compare.

typedef struct TObject {
	const char* className;  // 0x00
	u16 signal;             // 0x04
	u16 tag;                // 0x06
	struct TObject* prev;   // 0x08
	struct TObject* next;   // 0x0C
	struct TObject* parent; // 0x10
	struct TObject* child;  // 0x14
	void** vtable;          // 0x18
	s16 unk1C;              // 0x1C
	s16 objectSize;         // 0x1E
	s16 unk20;              // 0x20
	s16 unk22;              // 0x22
	s16 unk24;              // 0x24
	s16 unk26;              // 0x26
} TObject;                  // 0x28

typedef struct Frame Frame;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;          // 0x08

typedef struct Volume {
	u8 unk0[0x88]; // 0x00
} Volume;          // 0x88

typedef struct S01ObjectBase {
	TObject base;  // 0x00
	Motion motion; // 0x28
	Volume volume; // 0x30
	void* handle;  // 0xB8
} S01ObjectBase;   // 0xBC

extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void dtor_8003C52C(Volume* volume, s32 flags);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_80063E7C(void* handle, s32 flags);

// Defined by the module, renamed to this name in its own symbols.txt.
extern "C" void* s01ObjectBaseVtable[];

extern "C" S01ObjectBase* s01ObjectBaseDtor(S01ObjectBase* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = s01ObjectBaseVtable;
		object->motion.vtable = s01ObjectBaseVtable + 0xB;

		if (object->handle != NULL) {
			fn_80063E7C(object->handle, 1);
			object->handle = NULL;
		}

		dtor_8003C52C(&object->volume, 0);
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}
