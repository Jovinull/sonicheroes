#include "game/object.h"

// The item box's constructor (itemBoxCtor here), called by the factory in the
// module's item box hooks.
//
// It takes the placement's position, angle, item kind and flag, and makes the
// box's clump with the placement's light set. The first atomic using one of the
// box's textures and the atomic with the material's sixth texture get the
// custom render mode 0x10. A box with no flag is marked in its collision. A box
// with no work block looks through its group's placements for an object of type
// 0x24 closer than 100 and, at the first one, makes the block, marked
// 0x12345678 and holding the box's position.

typedef struct RpAtomic RpAtomic;
typedef struct RpMaterial RpMaterial;

typedef struct ItemBoxTexture {
	u8 unk00[0x10]; // 0x00
	char name[32];  // 0x10
} ItemBoxTexture;

typedef struct ItemBoxAngle {
	s32 x, y, z;
} ItemBoxAngle;

typedef struct ItemBoxParams {
	u8 kind; // 0x00
	s8 flag; // 0x01
} ItemBoxParams;

typedef struct ItemBoxWork {
	u32 mark;  // 0x00
	RwV3d pos; // 0x04
	u8 unk10[4];
} ItemBoxWork; // 0x14

typedef struct ItemBoxFrame {
	RwV3d pos;                 // 0x00
	ItemBoxAngle ang;          // 0x0C
	u32 condition;             // 0x18
	u8 unk1C[0xC];             // 0x1C
	u16 type;                  // 0x28
	u8 group;                  // 0x2A
	u8 pad2B;                  // 0x2B
	ItemBoxParams* params;     // 0x2C
	ItemBoxWork* work;         // 0x30
	u8 unk34[4];               // 0x34
	struct ItemBoxFrame* next; // 0x38
} ItemBoxFrame;

typedef struct ItemBoxTask {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u16 tag;               // 0x06
	u8 unk08[0x10];        // 0x08
	void** vtable;         // 0x18
	s16 unk1C;             // 0x1C
	s16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
} ItemBoxTask;             // 0x28

typedef struct ItemBoxMotion {
	ItemBoxFrame* frame; // 0x00
	void** vtable;       // 0x04
} ItemBoxMotion;         // 0x08

typedef struct ItemBox {
	ItemBoxTask base;     // 0x00
	ItemBoxMotion motion; // 0x28
	u8 colli[8];          // 0x30
	u16 colliFlags;       // 0x38
	u8 colli3A[0x7E];     // 0x3A
	u8 kind;              // 0xB8
	u8 item;              // 0xB9
	u8 padBA[2];          // 0xBA
	s32 unkBC;            // 0xBC
	RwV3d pos;            // 0xC0
	ItemBoxAngle ang;     // 0xCC
	s32 unkD8;            // 0xD8
	RwV3d scale;          // 0xDC
	RpClump* clump;       // 0xE8
	s32 flag;             // 0xEC
} ItemBox;                // 0xF0

extern "C" u8* lbl_8042C298;
extern "C" void* itemBoxVtable[];
extern "C" const char* itemBoxClassName;
extern "C" RpClump* itemBoxModel;
extern "C" RpMaterial* itemBoxMaterial;
extern "C" char* itemBoxTextureNames[];
extern "C" u8 itemBoxCclInfo[];
extern "C" const f32 itemBoxOne[1];
extern "C" const f32 itemBoxRange[1];

extern "C" void __ct__7TObjectFP7TObject(ItemBoxTask* object, void* owner);
extern "C" void __ct__10TObjSetObjFv(ItemBoxMotion* motion);
extern "C" void __ct__7C_COLLIFv(void* colli);
extern "C" void fn_8003BF04(void* colli, void* info, s32 count, s32 kind);
extern "C" void* __nw__FUl(u32 size);
extern "C" RpClump* fn_80150588(RpClump* model);
extern "C" void* fn_80146BC8(RpMaterial* material, s32 index);
extern "C" ItemBoxTexture* fn_80146990(void* list, s32 index);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 light);
RpAtomic* objRpClumpGetAtomicWithTexture(RpClump* clump, RpAtomic* atomic, char* name);
f32 Distance2P2P(const RwV3d* a, const RwV3d* b);

extern "C" ItemBox* itemBoxCtor(ItemBox* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	__ct__10TObjSetObjFv(&object->motion);
	__ct__7C_COLLIFv(object->colli);
	object->base.vtable     = itemBoxVtable;
	object->motion.vtable   = itemBoxVtable + 0xB;
	object->base.className  = itemBoxClassName;
	object->base.objectSize = 0xF0;
	object->pos             = object->motion.frame->pos;
	object->ang             = object->motion.frame->ang;

	ItemBoxParams* params = object->motion.frame->params;
	object->item = object->kind = params->kind;
	object->flag                = params->flag;
	object->unkD8               = 0;
	object->scale.z = object->scale.y = object->scale.x = itemBoxOne[0];
	object->unkBC                                       = 1;

	object->clump = fn_80150588(itemBoxModel);
	u32 flag      = *(volatile u32*)&object->motion.frame->condition;
	objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
	    object->clump, ((flag & 0x1C0000) >> 18) + 4);

	RpAtomic* atomic = NULL;
	for (s32 i = 0; atomic == NULL; i++) {
		atomic = objRpClumpGetAtomicWithTexture(object->clump, NULL, itemBoxTextureNames[i]);
	}
	OBJ_CUSTOMRENDER* render = RpAtomicMCCGetCustomRenderCallBack(atomic);
	render->pData            = (void*)0x10;

	void* list = fn_80146BC8(itemBoxMaterial, 6);
	if (list != NULL) {
		char* name = fn_80146990(list, 1)->name;
		render     = RpAtomicMCCGetCustomRenderCallBack(
		    objRpClumpGetAtomicWithTexture(object->clump, NULL, name));
		render->pData = (void*)0x10;
	}

	fn_8003BF04(object->colli, itemBoxCclInfo, 1, 5);
	if (object->flag == 0) {
		object->colliFlags |= 0x40;
	}

	if (object->motion.frame->work == NULL) {
		ItemBoxFrame* other = ((ItemBoxFrame**)(lbl_8042C298 + 0x30))[object->motion.frame->group];
		f32 range           = itemBoxRange[0];
		for (; other != NULL; other = other->next) {
			if (other->type == 0x24
			    && Distance2P2P(&object->motion.frame->pos, &other->pos) < range) {
				object->motion.frame->work       = (ItemBoxWork*)__nw__FUl(0x14);
				object->motion.frame->work->mark = 0x12345678;
				object->motion.frame->work->pos  = object->motion.frame->pos;
				break;
			}
		}
	}
	return object;
}
