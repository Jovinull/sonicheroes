#include "types.h"

// TObjSpring's constructor. The code is the same in
// all thirteen stage modules that share the engine core, 115 instructions
// identical once the per module label names are set aside; stage40D is a
// different revision of the source and is left out, as everywhere else.
//
// The frame flags are read through a one-field inline accessor. Their volatile
// qualifier makes the compiler commit that load while starting the second call
// argument; leaving the mask outside the accessor then lets it fill the first
// argument between the load and the bit operations. That is the source shape
// behind the original three-instruction evaluation order.
//
// The 1.0f written into the three scale components is reached as an external
// rather than written as a literal, which is not a stylistic choice. It is one
// pooled constant of the original translation unit and three other runs still
// in assembly read the same word, so claiming it here would delete the symbol
// they resolve against and the REL link fails outright. Spelling it 1.0f would
// have the compiler emit a second copy into this object, which is the same
// problem from the other side. The module keeps the word, this file names it,
// exactly as rel/spring_object.cpp reaches its two .bss neighbours.
//
// The object is built inner first, one call per base: the TObject, the motion
// at 0x28 and the part at 0x30, and only then are the two vtables restored out
// of one address, the way the destructor tears them down.
//
// The keyframe is re-read for each group of fields rather than held in one
// local across the whole function. That is what the original does, three
// separate loads of the same word, and it is why the placement, the rotation
// and the parameter block are written as three passes below.

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

// What the path carries alongside the keyframe. Only the two fields the
// constructor copies out are named.
typedef struct PathParams {
	f32 height; // 0x00
	s16 unk4;   // 0x04
} PathParams;

typedef struct Frame {
	Vec3 position;      // 0x00
	Rot3 rotation;      // 0x0C
	volatile u32 flags; // 0x18
	u8 unk1C[0xE];      // 0x1C
	u8 unk2A;           // 0x2A
	u8 unk2B;           // 0x2B
	PathParams* params; // 0x2C
} Frame;

typedef struct TObject {
	const char* className; // 0x00
	u8 unk4[0x14];         // 0x04
	void** vtable;         // 0x18
	s16 unk1C;             // 0x1C
	s16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
} TObject;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;

typedef struct World {
	u8 unk0[0x7274]; // 0x0000
	void* scene;     // 0x7274
} World;

// The same object rel/spring_object.cpp describes, cut finer where this file
// writes through fields that one only steps over. The offsets agree; the names
// there are the ones to keep if the two are ever merged.
typedef struct Spring {
	TObject base;   // 0x000
	Motion motion;  // 0x028
	u8 list[0x8];   // 0x030
	u16 partFlags;  // 0x038
	u8 unk3A[0x7E]; // 0x03A
	s32 state;      // 0x0B8
	s8 hits[8];     // 0x0BC
	s16 unkC4;      // 0x0C4
	u8 unkC6[0x2];  // 0x0C6
	Vec3 position;  // 0x0C8
	Rot3 rotation;  // 0x0D4
	s32 unkE0;      // 0x0E0
	Vec3 scale;     // 0x0E4
	f32 height;     // 0x0F0
	u8 unkF4[0x4];  // 0x0F4
	void* model;    // 0x0F8
} Spring;           // 0x0FC

static inline u32 springFlags(Spring* object)
{
	return object->motion.frame->flags;
}

extern "C" World* lbl_8042C1D0;

extern "C" void __ct__7TObjectFP7TObject(TObject* object, void* owner);
extern "C" void fn_8003BF04(void* part, const void* params, s32 a, s32 b);
extern "C" void fn_8003C618(void* part);
extern "C" s32 fn_8005B8D8(Motion* motion);
extern "C" void fn_8005BE6C(Motion* motion);
extern "C" void fn_8005D5C8(void* model, s32 slot);
extern "C" void fn_8005E1DC(void* model, s32 a, const char* texture);
extern "C" s32* fn_8005F490(void);
extern "C" void* fn_80150588(void* source);
extern "C" void fn_8015BB08(void* scene, void* model);

// Defined by each module, renamed to these names in its own symbols.txt.
extern "C" void* springVtable[];
extern "C" const char* springClassName;
extern "C" const u8 springPartParams[];
extern "C" void* springModel;
extern "C" char springTextureName[];

extern "C" Spring* springCtor(Spring* object, void* owner)
{
	Frame* frame;
	PathParams* params;
	s32* handle;

	__ct__7TObjectFP7TObject(&object->base, owner);
	fn_8005BE6C(&object->motion);
	fn_8003C618(&object->list);

	object->base.vtable   = springVtable;
	object->motion.vtable = springVtable + 0xB;

	object->base.className  = springClassName;
	object->base.objectSize = 0xFC;

	frame              = object->motion.frame;
	object->position.x = frame->position.x;
	object->position.y = frame->position.y;
	object->position.z = frame->position.z;

	frame              = object->motion.frame;
	object->rotation.x = frame->rotation.x;
	object->rotation.y = frame->rotation.y;
	object->rotation.z = frame->rotation.z;

	params         = object->motion.frame->params;
	object->height = params->height;
	object->unkC4  = params->unk4;

	object->unkE0 = 0;

	object->scale.x = 1.0f;
	object->scale.y = 1.0f;
	object->scale.z = 1.0f;

	object->hits[0] = 0;
	object->hits[1] = 0;
	object->hits[2] = 0;
	object->hits[3] = 0;
	object->hits[4] = 0;
	object->hits[5] = 0;
	object->hits[6] = 0;
	object->hits[7] = 0;

	if (object->motion.frame->unk2A != 0) {
		object->state = 3;
	} else {
		object->state = 1;
	}

	object->model = fn_80150588(springModel);

	fn_8005D5C8(object->model, ((springFlags(object) & 0x001C0000) >> 18) + 4);
	fn_8005E1DC(object->model, 0, springTextureName);

	handle  = fn_8005F490();
	*handle = 0x10;

	if (object->state != 3 || fn_8005B8D8(&object->motion) != 0) {
		fn_8015BB08(lbl_8042C1D0->scene, object->model);
	}

	fn_8003BF04(&object->list, springPartParams, 1, 4);

	object->partFlags |= 0x40;
	return object;
}
