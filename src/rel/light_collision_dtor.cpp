#include "types.h"

// The light collision's destructor (lightCollisionDtor here; TObjLightColli's
// in the PS2 build). It restores both vtable pointers, takes the collision out
// of the module's list of light collisions, runs the placement and object
// bases down and frees the object when the delete flag asks for it.

typedef struct TObject {
	u8 unk00[0x18];
	void** vtable; // 0x18
	u8 unk1C[0xC];
} TObject; // 0x28

typedef struct Motion {
	void* frame;   // 0x00
	void** vtable; // 0x04
} Motion;          // 0x08

typedef struct LightCollision {
	TObject base;  // 0x00
	Motion motion; // 0x28
	u8 unk30[0xC];
	struct LightCollision* next; // 0x3C
} LightCollision;

extern "C" void* lbl_8042C148;
extern "C" void* lightCollisionVtable[];
extern "C" LightCollision* lightCollisionHead;

extern "C" void __dt__7TObjectFv(TObject* object, s32 flags);
extern "C" void __dt__10TObjSetObjFv(Motion* motion, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, TObject* object);

extern "C" LightCollision* lightCollisionDtor(LightCollision* object, s16 flags)
{
	if (object != NULL) {
		object->base.vtable   = lightCollisionVtable;
		object->motion.vtable = lightCollisionVtable + 0xB;

		if (lightCollisionHead == object) {
			lightCollisionHead = object->next;
		} else {
			LightCollision* prev = lightCollisionHead;

			while (prev->next != object) {
				prev = prev->next;
			}
			prev->next = object->next;
		}

		__dt__10TObjSetObjFv(&object->motion, 0);
		__dt__7TObjectFv(&object->base, 0);

		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, &object->base);
		}
	}
	return object;
}
