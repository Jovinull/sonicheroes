#include "types.h"

// The light collision's constructor (lightCollisionCtor here), called by the
// factory in rel/light_collision_create.cpp.
//
// The first light collision of a stage makes the manager they share: a plain
// object under the task at lbl_8042C118 with sixteen slots set to -1. When the
// manager cannot be made, the new collision raises its kill bit and gives up.
// Otherwise it takes a default size of 10 when its placement gives none,
// clears its flags, keeps the placement's first two bytes and goes to the end
// of the module's list of light collisions.

typedef struct TObject {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u16 tag;               // 0x06
	u8 unk08[0x10];        // 0x08
	void** vtable;         // 0x18
	s16 unk1C;             // 0x1C
	s16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
} TObject;                 // 0x28

typedef struct LightCollisionParams {
	u8 kind;     // 0x00
	u8 unk01;    // 0x01
	u8 pad02[2]; // 0x02
	f32 x, y, z; // 0x04: the size
} LightCollisionParams;

typedef struct Frame {
	u8 unk00[0x2C];               // 0x00
	LightCollisionParams* params; // 0x2C
} Frame;

typedef struct Motion {
	Frame* frame;  // 0x00
	void** vtable; // 0x04
} Motion;          // 0x08

typedef struct LightCollision {
	TObject base;                // 0x00
	Motion motion;               // 0x28
	u8 flags[8];                 // 0x30
	u8 kind;                     // 0x38
	u8 unk39;                    // 0x39
	u8 pad3A[2];                 // 0x3A
	struct LightCollision* next; // 0x3C
} LightCollision;                // 0x40

extern "C" void* lbl_8042C118;
extern "C" void* lbl_8042C148;
extern "C" void* lightCollisionVtable[];
extern "C" const char* lightCollisionClassName;
extern "C" TObject* lightCollisionManager;
extern "C" void* lightCollisionManagerVtable[];
extern "C" const char* lightCollisionManagerClassName;
extern "C" s8 lightCollisionSlots[16];
extern "C" const f32 lightCollisionNoSize[1];
extern "C" const f32 lightCollisionDefaultSize[1];
extern "C" LightCollision* lightCollisionHead;

extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void __ct__7TObjectFP7TObject(TObject* object, void* owner);
extern "C" void __ct__10TObjSetObjFv(Motion* motion);

extern "C" LightCollision* lightCollisionCtor(LightCollision* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	__ct__10TObjSetObjFv(&object->motion);
	object->base.vtable          = lightCollisionVtable;
	object->motion.vtable        = lightCollisionVtable + 0xB;
	LightCollisionParams* params = object->motion.frame->params;
	object->base.className       = lightCollisionClassName;
	object->base.objectSize      = 0x40;

	if (lightCollisionManager == NULL) {
		TObject* manager = (TObject*)Malloc__9THeapCtrlFUi(lbl_8042C148, 0x28);
		if (manager != NULL) {
			__ct__7TObjectFP7TObject(manager, lbl_8042C118);
			manager->vtable         = lightCollisionManagerVtable;
			manager->className      = lightCollisionManagerClassName;
			manager->objectSize     = 0x28;
			lightCollisionSlots[0]  = -1;
			lightCollisionSlots[1]  = -1;
			lightCollisionSlots[2]  = -1;
			lightCollisionSlots[3]  = -1;
			lightCollisionSlots[4]  = -1;
			lightCollisionSlots[5]  = -1;
			lightCollisionSlots[6]  = -1;
			lightCollisionSlots[7]  = -1;
			lightCollisionSlots[8]  = -1;
			lightCollisionSlots[9]  = -1;
			lightCollisionSlots[10] = -1;
			lightCollisionSlots[11] = -1;
			lightCollisionSlots[12] = -1;
			lightCollisionSlots[13] = -1;
			lightCollisionSlots[14] = -1;
			lightCollisionSlots[15] = -1;
		}
		lightCollisionManager = manager;
		if (manager == NULL) {
			object->base.signal |= 1;
			return object;
		}
	}

	if (lightCollisionNoSize[0] == params->x && lightCollisionNoSize[0] == params->y
	    && lightCollisionNoSize[0] == params->z) {
		params->z = params->y = params->x = lightCollisionDefaultSize[0];
	}
	object->flags[0] = 0;
	object->flags[1] = 0;
	object->flags[2] = 0;
	object->flags[3] = 0;
	object->flags[4] = 0;
	object->flags[5] = 0;
	object->flags[6] = 0;
	object->flags[7] = 0;
	object->kind     = params->kind;
	object->unk39    = params->unk01;

	if (lightCollisionHead == NULL) {
		lightCollisionHead = object;
	} else {
		LightCollision* last = lightCollisionHead;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = object;
	}
	object->next = NULL;
	return object;
}
