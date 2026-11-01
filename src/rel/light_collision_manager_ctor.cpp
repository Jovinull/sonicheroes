#include "types.h"

// TObjLightColliMaster's constructor (lightCollisionManagerCtor here; the PS2
// build's __ct__20TObjLightColliMasterFv), the same in the thirteen stage
// modules that share the engine core: a bare TObject under the task at
// lbl_8042C118 with the master's vtable and class name, whose sixteen light
// slots all start free (-1). rel/light_collision_manager_dtor.cpp is its
// destructor.

typedef struct TObject {
	char* className; // 0x00
	u8 unk04[0x14];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	s16 dispTime; // 0x1E
	u8 unk20[0x8];
} TObject; // 0x28

extern "C" TObject* lbl_8042C118;
extern "C" void* lightCollisionManagerVtable[];
extern "C" char* lightCollisionManagerClassName;
extern "C" s8 lightCollisionSlots[16];

extern "C" void __ct__7TObjectFP7TObject(TObject* object, TObject* parent);

extern "C" TObject* lightCollisionManagerCtor(TObject* object)
{
	__ct__7TObjectFP7TObject(object, lbl_8042C118);
	object->vtable          = lightCollisionManagerVtable;
	object->className       = lightCollisionManagerClassName;
	object->dispTime        = 0x28;
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
	return object;
}
