#include "types.h"

// Four methods of the base class the stage-01 objects derive from, in the order
// the original emits them: the per-frame update; the destructor, which restores
// both vtable pointers, releases the handle it registered, runs the embedded
// volume and motion bases down and then the object base, and hands the object
// back to the heap when the caller asks for it; the constructor; and the editor
// callback.
//
// That it is a base rather than an object of its own is read from its callers:
// rel/o_s01_ciseki.cpp and rel/o_s01_shachicolli.cpp each end their own
// destructor with a call to it, and each also declares the constructor at
// 0x0007CB30 and the method at 0x0007C9CC. The constructor confirms the shape,
// running __ct__7TObjectFP7TObject, the motion constructor at +0x28 and the
// volume constructor at +0x30 before installing the two vtable pointers.
//
// The claim is .text 0x0007C9CC to 0x0007CCD0 and .rodata 0x00001348 to
// 0x00001358. The four functions are contiguous. The rodata is the four float
// constants the constructor and the editor callback need, emitted in first-use
// order; `lbl_3_rodata_1354` was sized 0x28 only because nothing referenced
// 0x1358 yet, and is split here so the claim ends on a symbol boundary.
//
// `-pool off` is needed: with pooling on, CodeWarrior gathers those four
// constants behind one base register, where the original addresses each with
// its own lis/addi pair.
//
// The vtable stays in the module's data and is renamed to the name below.
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
// is the tail shape `o_s01_ciseki.cpp` also has. Only these four functions are
// reconstructed here; the rest of the unit is still assembly. The eight byte
// adjustor thunk at 0x0007CCD0 forwards into the editor callback and belongs to
// this unit, but reproducing it needs the multiple inheritance modelled, so it
// is left out.
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

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct SETDATA_PARAM {
	Vec3 position; // 0x00
	s32 angleX;    // 0x0C
	s32 angleY;    // 0x10
	s32 angleZ;    // 0x14
	u32 flags;     // 0x18
	u8 pad1C[0x10];
	Vec3* params; // 0x2C
} SETDATA_PARAM;

typedef struct Motion {
	SETDATA_PARAM* frame; // 0x00
	void** vtable;        // 0x04
} Motion;                 // 0x08

typedef struct VolumeBody {
	u8 unk0[0x14]; // 0x00
	Vec3 scale;    // 0x14
} VolumeBody;

typedef struct Volume {
	u8 unk0[0x08];    // 0x00
	u16 flags;        // 0x08
	u8 unk0A[0x06];   // 0x0A
	VolumeBody* body; // 0x10
	u8 unk14[0x74];   // 0x14
} Volume;             // 0x88

typedef struct S01ObjectBase {
	TObject base;  // 0x00
	Motion motion; // 0x28
	Volume volume; // 0x30
	void* handle;  // 0xB8
	u32 unkBC;     // 0xBC
	Vec3 position; // 0xC0
} S01ObjectBase;   // 0xCC

extern "C" void* lbl_8042C148;
extern "C" void* lbl_8042C180;

// The unit's own editor parameter descriptor, and the collision entry the
// volume registers with. The entry is defined by rel/o_s01_ciseki.cpp.
extern "C" u32 lbl_3_data_A170[];
extern "C" u32 cisekiEntry[12];

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void dtor_8003C52C(Volume* volume, s32 flags);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_80063E7C(void* handle, s32 flags);
extern "C" s32 fn_8005B8BC(Motion* motion);
extern "C" s32 fn_8005B8D8(Motion* motion);
extern "C" s32 fn_8005B9F0(Motion* motion);
extern "C" void __ct__7TObjectFP7TObject(TObject* object, TObject* parent);
extern "C" void fn_8003C200(Volume* volume, u32* entry, s32 kind, s32 count);
extern "C" void fn_8003C618(Volume* volume);
extern "C" void fn_80021384(Volume* volume);
extern "C" void fn_8005BE6C(Motion* motion);

// Defined by the module, renamed to this name in its own symbols.txt.
extern "C" void* s01ObjectBaseVtable[];

// Runs once a frame. When the motion reports it has started or finished, the
// object raises its own signal bit; otherwise it tracks the editor frame's
// position while the global at +0x1F says the editor is not holding it.
extern "C" void s01ObjectBaseUpdate(S01ObjectBase* object)
{
	Vec3* params = object->motion.frame->params;

	if (fn_8005B9F0(&object->motion) != 0 || fn_8005B8BC(&object->motion) != 0) {
		object->base.signal = object->base.signal | 1;
	} else if (((s8*)lbl_8042C180)[0x1F] == 0) {
		if (fn_8005B8D8(&object->motion) != 0) {
			object->position.x = params->x;
			object->position.y = params->y;
			object->position.z = params->z;
		}
	}
}

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

// Builds the base: the object, motion and volume bases in declaration order,
// then both vtable pointers, then the editor frame's scale. A frame that leaves
// the scale at zero gets the default instead. The volume registers with the
// shared collision entry and takes half the scale as its extent.
extern "C" S01ObjectBase* s01ObjectBaseCtor(S01ObjectBase* object, TObject* parent)
{
	Vec3* params;
	VolumeBody* body;

	__ct__7TObjectFP7TObject(&object->base, parent);
	fn_8005BE6C(&object->motion);
	fn_8003C618(&object->volume);

	object->base.vtable   = s01ObjectBaseVtable;
	object->motion.vtable = s01ObjectBaseVtable + 0xB;

	params = object->motion.frame->params;

	if (params->x == 0.0f && params->y == 0.0f && params->z == 0.0f) {
		params->x = 100.0f;
		params->y = 100.0f;
		params->z = 10.0f;
	}

	object->position.x = params->x;
	object->position.y = params->y;
	object->position.z = params->z;

	object->unkBC  = lbl_3_data_A170[0];
	object->handle = NULL;

	fn_8003C200(&object->volume, cisekiEntry, 1, 4);

	body = object->volume.body;

	body->scale.x = 0.5f * object->position.x;
	body->scale.y = 0.5f * object->position.y;
	body->scale.z = 0.5f * object->position.z;

	fn_80021384(&object->volume);

	object->volume.flags = object->volume.flags & ~0x40;

	return object;
}

// The editor callback. It refuses a negative scale on any axis, clamping each
// component of the frame's parameters back to zero.
extern "C" void s01ObjectBaseEditOnChange(S01ObjectBase* object, SETDATA_PARAM* frame)
{
	Vec3* params = frame->params;

	if (params->x < 0.0f) {
		params->x = 0.0f;
	}

	if (params->y < 0.0f) {
		params->y = 0.0f;
	}

	if (params->z < 0.0f) {
		params->z = 0.0f;
	}
}
