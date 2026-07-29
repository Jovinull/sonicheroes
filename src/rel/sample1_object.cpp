#include "types.h"

// TObjSample, the first of the two sample objects every stage module ships.
// The second one is rel/sample2_object.cpp, and the two share a base: the four
// stubs at 0x550 to 0x560 that both vtables point at belong to this run.
//
// The claim is .text 0xD8 to 0x3E0 and .rodata 0x0 to 0x18, the same code at
// the same addresses in thirteen of the fourteen stage modules, so it is one
// source that each module's splits.txt names and each module's symbols.txt
// renames into. stage40D is a different revision of the source and is left out,
// as it is for rel/prolog.c and rel/sample2_object.cpp.
//
// stage13D is the one module where the addresses move: two doubles from another
// unit land first, so its copy of the five constants sits at .rodata 0x10 to
// 0x28 and its splits.txt says so. Everything else is at the same address in
// all thirteen.
//
// The run stops at 0x3E0 rather than carrying on to the registration function:
// the factory at 0x3E0 has the same shape sample2Create does, where the
// original keeps the allocator's result and the pointer the construction runs
// on in separate registers and no source form reproduces the extra copy. That
// one is left to the module, and so is fn_N_494, which fills the registration
// record in .bss and reaches three of the stubs here.
//
// Both the constructor and Exec read the keyframe through a local rather than
// assigning the position across whole, for the reason written up in
// rel/sample2_object.cpp: a struct assignment makes the compiler hold the
// function back and emit it after the rest of the file, which would put the
// constructor last instead of fourth. The spelling below compiles to the same
// one load and three moves.
//
// 182.04445 is 65536 divided by 360, so the angle at 0x3C is a binary angle and
// the signed byte the path carries is a turn rate in degrees per frame. The
// counter at 0x40 retires the object after 600 frames, ten seconds, by raising
// bit 16 in the keyframe's flags.

typedef struct Vec3 {
	f32 x;
	f32 y;
	f32 z;
} Vec3;

typedef struct Rot3 {
	s32 x;
	s32 y;
	s32 z;
} Rot3;

// What the path carries alongside the keyframe: how far out the object orbits
// and how fast it turns. sample1Clamp is the only thing that bounds them.
typedef struct PathParams {
	f32 distance; // 0x00
	s8 speed;     // 0x04
} PathParams;

typedef struct Frame {
	Vec3 position;      // 0x00
	u8 unk0C[0xC];      // 0x0C
	u32 flags;          // 0x18
	u8 unk1C[0x10];     // 0x1C
	PathParams* params; // 0x2C
} Frame;

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
} TObject;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;

typedef struct Sample1 {
	TObject base;  // 0x00
	Motion motion; // 0x28
	Vec3 position; // 0x30
	s32 angle;     // 0x3C
	s32 timer;     // 0x40
} Sample1;         // 0x44

// The block at .data 0x44: the class name pointer the constructor reads, and
// two spare floats nothing in this run touches.
typedef struct Sample1Defaults {
	const char* className; // 0x00
	f32 unk4;              // 0x04
	f32 unk8;              // 0x08
} Sample1Defaults;

// Msg_KillOk, the bit Exec raises once the path has run out.
#define SIGNAL_KILL_OK 1

extern "C" void* lbl_8042B088;
extern "C" void* lbl_8042C148;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void __ct__7TObjectFP7TObject(TObject* object, void* owner);
extern "C" void fn_800189A4(void* heap, TObject* object);
extern "C" void fn_80051EF0(void* context, Vec3* vector, const Rot3* rotation);
extern "C" s32 fn_8005B8BC(Motion* motion);
extern "C" s32 fn_8005B8D8(Motion* motion);
extern "C" s32 fn_8005B9F0(Motion* motion);
extern "C" void dtor_8005BD3C(Motion* motion, s32 flags);
extern "C" void fn_8005BE6C(Motion* motion);
extern "C" void fn_800D72F4(const Vec3* a, const Vec3* b, Vec3* out);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" Sample1Defaults sample1Defaults;
extern "C" void* sample1Vtable[];

extern "C" void sample1Disp(void) { }

extern "C" void sample1Exec(Sample1* object)
{
	Vec3 offset;
	Rot3 rotation;
	PathParams* params = object->motion.frame->params;

	if (fn_8005B9F0(&object->motion) != 0 || fn_8005B8BC(&object->motion) != 0) {
		object->base.signal |= SIGNAL_KILL_OK;
	} else if (fn_8005B8D8(&object->motion) != 0) {
		Frame* frame = object->motion.frame;

		object->position.x = frame->position.x;
		object->position.y = frame->position.y;
		object->position.z = frame->position.z;
	} else {
		object->angle += (s32)(182.04445f * params->speed);

		offset.y = 0.0f;
		offset.x = 0.0f;
		offset.z = params->distance;

		rotation.z = 0;
		rotation.x = 0;
		rotation.y = object->angle;

		fn_80051EF0(lbl_8042B088, &offset, &rotation);
		fn_800D72F4(&object->motion.frame->position, &offset, &object->position);

		object->timer++;
		if (object->timer > 600) {
			object->motion.frame->flags |= 0x10000;
		}
	}
}

extern "C" Sample1* sample1Dtor(Sample1* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = sample1Vtable;
		object->motion.vtable = sample1Vtable + 0xB;
		dtor_8005BD3C(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);
		if (flags > 0) {
			fn_800189A4(lbl_8042C148, &object->base);
		}
	}
	return object;
}

extern "C" Sample1* sample1Ctor(Sample1* object, void* owner)
{
	Frame* frame;

	__ct__7TObjectFP7TObject(&object->base, owner);
	fn_8005BE6C(&object->motion);

	object->base.vtable   = sample1Vtable;
	object->motion.vtable = sample1Vtable + 0xB;

	object->base.className  = sample1Defaults.className;
	object->base.objectSize = 0x44;

	frame              = object->motion.frame;
	object->position.x = frame->position.x;
	object->position.y = frame->position.y;
	object->position.z = frame->position.z;

	object->angle = 0;
	object->timer = 0;
	return object;
}

// The last slot of the second base's vtable. The object it is called on is not
// used: everything it touches hangs off the keyframe it is handed.
extern "C" void sample1Clamp(Sample1* object, Frame* frame)
{
	PathParams* params = frame->params;

	if (params->distance < 1.0f) {
		params->distance = 1.0f;
	}
	if (params->distance > 10.0f) {
		params->distance = 10.0f;
	}
	if (params->speed < 1) {
		params->speed = 1;
	}
	if (params->speed > 5) {
		params->speed = 5;
	}
}

extern "C" void sample1Stub1(void) { }

extern "C" void sample1Stub2(void) { }

extern "C" void sample1Stub3(void) { }
