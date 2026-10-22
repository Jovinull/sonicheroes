#include "types.h"

// TObjFlowerCommon's destructor (the PS2 build's name): it releases the three
// stem models and the flower model, takes the model added to the world out of
// it and releases it, then the collision, the set-object base and the object
// base run down and the object is freed when the delete flag asks for it.

#include "src/rel/flower_common.inc"

typedef struct World {
	u8 unk0[0x725C]; // 0x0000
	void* scene;     // 0x725C
} World;

extern "C" World* lbl_8042C1D0;
extern "C" void* lbl_8042C148;
extern "C" void* flowerCommonVtable[];

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_8015BBF8(void* scene, RpClump* clump);
extern "C" void __dt__7C_COLLIFv(void* colli, s32 flags);
extern "C" void __dt__10TObjSetObjFv(void* setObj, s32 flags);
extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" FlowerCommon* __dt__16TObjFlowerCommonFv(FlowerCommon* flower, s16 flags)
{
	if (flower != NULL) {
		flower->vtable       = flowerCommonVtable;
		flower->setObjVtable = flowerCommonVtable + 0xB;
		if (flower->models[0] != NULL) {
			fn_80150958(flower->models[0]);
			flower->models[0] = NULL;
		}
		if (flower->models[1] != NULL) {
			fn_80150958(flower->models[1]);
			flower->models[1] = NULL;
		}
		if (flower->models[2] != NULL) {
			fn_80150958(flower->models[2]);
			flower->models[2] = NULL;
		}
		if (flower->model != NULL) {
			fn_80150958(flower->model);
			flower->model = NULL;
		}
		if (flower->worldModel != NULL) {
			fn_8015BBF8(lbl_8042C1D0->scene, flower->worldModel);
			fn_80150958(flower->worldModel);
			flower->worldModel = NULL;
		}
		__dt__7C_COLLIFv(flower->colli, 0);
		__dt__10TObjSetObjFv(&flower->frame, 0);
		__dt__7TObjectFv(flower, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, flower);
		}
	}
	return flower;
}
