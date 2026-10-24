#include "game/effect/eff_bomb.h"

// The breakable weight's destructor (the PS2 build's TObjWeightExt;
// breakableWeightDtor here). It deletes the material, releases the model
// (DestroyClump inlined, rel/breakable_weight_clump.cpp) and the matrix; a
// player still riding is let go (when the weight was falling, mode 3, only a
// player held in state 0x26 is released by fn_80043DEC; otherwise the rider
// gets action 0xF); the piece object is deleted; then the collision, the
// set-object base and the object base run down and the object is freed when
// the delete flag asks for it.

typedef struct RpClump RpClump;

class DealMaterial
{
public:
	~DealMaterial();
};

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct SetObj {
	void* frame;   // 0x00
	void** vtable; // 0x04
} SetObj;

typedef struct BreakableWeight {
	u8 unk00[0x18];         // 0x00
	void** vtable;          // 0x18
	u8 unk1C[0xC];          // 0x1C
	SetObj setObj;          // 0x28
	u8 colli[0x88];         // 0x30 (C_COLLI)
	u8 unkB8[0x20];         // 0xB8
	s32 rider;              // 0xD8
	u8 unkDC[0x18];         // 0xDC
	RpClump* model;         // 0xF4
	RwMatrixTag* matrix;    // 0xF8
	DealMaterial* material; // 0xFC
	s32 mode;               // 0x100
	u8 unk104[0x2C];        // 0x104
	TObject* piece;         // 0x130
} BreakableWeight;

extern "C" void* breakableWeightVtable[];
extern "C" void* lbl_802AD070[];

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_80043DEC(void* player);
extern "C" void fn_800E1208(s32 player, s32 action, s32 arg);
extern "C" void __dt__7C_COLLIFv(void* colli, s32 flags);
extern "C" void __dt__10TObjSetObjFv(SetObj* setObj, s32 flags);
extern "C" void __dt__7TObjectFv(void* object, s32 flags);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* object);

extern "C" BreakableWeight* breakableWeightDtor(BreakableWeight* object, s16 flags)
{
	if (object != NULL) {
		object->vtable        = breakableWeightVtable;
		object->setObj.vtable = breakableWeightVtable + 0xB;
		if (object->material != NULL) {
			delete object->material;
		}
		if (object->model != NULL) {
			fn_80150958(object->model);
			object->model = NULL;
		}
		if (object->matrix != NULL) {
			delete object->matrix;
			object->matrix = NULL;
		}
		if (object->mode == 3 && object->rider != -1) {
			void* player = lbl_802AD070[object->rider];

			if (*(s16*)((u8*)player + 0x6F0) == 0x26) {
				fn_80043DEC(player);
			}
		} else if (object->rider != -1) {
			fn_800E1208(object->rider, 0xF, 0);
		}
		delete object->piece;
		object->piece = NULL;
		__dt__7C_COLLIFv(object->colli, 0);
		__dt__10TObjSetObjFv(&object->setObj, 0);
		__dt__7TObjectFv(object, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, object);
		}
	}
	return object;
}
