#include "game/object.h"

// The switch's constructor (switchCtor here), called by the factory in the
// module's switch hooks.
//
// It takes the placement's position, angle and parameters: the kind, whether
// the switch starts pressed (state 2, else 1) and a value. It makes the
// switch's clump with the placement's light set and finds its atomics: the
// panel, the panel's frame and the first one using one of the state textures,
// which shows the "off" texture through its material pointer and draws through
// switchGuard. A switch not yet pressed is added to the world. The placement's
// work block keeps the switch's state between visits; it is made when there is
// none, and the state picks the panel's render mode (the light set while off,
// 0x10 once pressed). Last, a type-0x24 object of the switch's group closer
// than switchNearbyRange marks the block with 0x12345678 and the position.

typedef struct RpAtomic RpAtomic;
typedef struct RpMaterial RpMaterial;

typedef struct SwitchAngle {
	s32 x, y, z;
} SwitchAngle;

typedef struct SwitchParams {
	s8 kind;  // 0x00
	s8 mode;  // 0x01
	u8 unk02; // 0x02
	u8 value; // 0x03
} SwitchParams;

typedef struct SwitchWork {
	u32 mark;  // 0x00
	RwV3d pos; // 0x04
	s32 state; // 0x10
} SwitchWork;  // 0x14

typedef struct SwitchFrame {
	RwV3d pos;                // 0x00
	SwitchAngle ang;          // 0x0C
	u32 condition;            // 0x18
	u8 unk1C[0xC];            // 0x1C
	u16 type;                 // 0x28
	u8 group;                 // 0x2A
	u8 pad2B;                 // 0x2B
	SwitchParams* params;     // 0x2C
	SwitchWork* work;         // 0x30
	u8 unk34[4];              // 0x34
	struct SwitchFrame* next; // 0x38
} SwitchFrame;

typedef struct SwitchShape {
	u8 unk00[2]; // 0x00
	u8 flags;    // 0x02
} SwitchShape;

typedef struct SwitchAtomic {
	u8 unk00[0x48];       // 0x00
	void* renderCallBack; // 0x48
} SwitchAtomic;

typedef struct SwitchTask {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u16 tag;               // 0x06
	u8 unk08[0x10];        // 0x08
	void** vtable;         // 0x18
	s16 unk1C;             // 0x1C
	s16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
} SwitchTask;              // 0x28

typedef struct SwitchMotion {
	SwitchFrame* frame; // 0x00
	void** vtable;      // 0x04
} SwitchMotion;         // 0x08

typedef struct Switch {
	SwitchTask base;       // 0x00
	SwitchMotion motion;   // 0x28
	u8 colli[0x10];        // 0x30
	SwitchShape* shape;    // 0x40
	u8 colli44[0x74];      // 0x44
	s32 state;             // 0xB8
	s32 workState;         // 0xBC
	s8 kind;               // 0xC0
	s8 unkC1;              // 0xC1
	u8 padC2[2];           // 0xC2
	RwV3d pos;             // 0xC4
	RwV3d panel;           // 0xD0
	SwitchAngle ang;       // 0xDC
	s32 value;             // 0xE8
	RpClump* clump;        // 0xEC
	RpAtomic* panelAtomic; // 0xF0
	SwitchAtomic* light;   // 0xF4
	RpAtomic* frameAtomic; // 0xF8
} Switch;                  // 0xFC

extern "C" u8* lbl_8042C1D0;
extern "C" u8* lbl_8042C298;
extern "C" void* switchVtable[];
extern "C" const char* switchClassName;
extern "C" RpClump* switchModel;
extern "C" char switchPanelNodeName[];
extern "C" char switchPanelMaterialName[];
extern "C" char* switchStateNames[];
extern "C" RpMaterial* switchOffHandle;
extern "C" u8 switchCclInfo[];
extern "C" const f32 switchPanelHeight[1];
extern "C" const f32 switchNearbyRange[1];

extern "C" void __ct__7TObjectFP7TObject(SwitchTask* object, void* owner);
extern "C" void __ct__10TObjSetObjFv(SwitchMotion* motion);
extern "C" void __ct__7C_COLLIFv(void* colli);
extern "C" void Init__7C_COLLIFP8CCL_INFOiUc(void* colli, void* info, s32 count, u8 kind);
extern "C" void* __nw__FUl(u32 size);
extern "C" RpClump* fn_80150588(RpClump* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" RpAtomic* switchGuard(RpAtomic* atomic);
extern "C" RpAtomic* fn_8014F1B0(RpAtomic* atomic);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump* clump, u32 light);
RpAtomic* objRpClumpGetAtomicWithTexture(RpClump* clump, RpAtomic* atomic, char* name);
f32 Distance2P2P(const RwV3d* a, const RwV3d* b);

static inline void switchSetPanelRender(Switch* object)
{
	OBJ_CUSTOMRENDER* render;

	switch (object->workState) {
		case 0:
			render        = RpAtomicMCCGetCustomRenderCallBack(object->panelAtomic);
			render->pData = (void*)(((object->motion.frame->condition & 0x1C0000) >> 18) + 4);
			render        = RpAtomicMCCGetCustomRenderCallBack(object->frameAtomic);
			render->pData = (void*)(((object->motion.frame->condition & 0x1C0000) >> 18) + 4);
			break;
		case 1:
		case 2:
			render        = RpAtomicMCCGetCustomRenderCallBack(object->panelAtomic);
			render->pData = (void*)0x10;
			render        = RpAtomicMCCGetCustomRenderCallBack(object->frameAtomic);
			render->pData = (void*)0x10;
			break;
	}
}

extern "C" Switch* switchCtor(Switch* object, void* owner)
{
	__ct__7TObjectFP7TObject(&object->base, owner);
	__ct__10TObjSetObjFv(&object->motion);
	__ct__7C_COLLIFv(object->colli);
	object->base.vtable     = switchVtable;
	object->motion.vtable   = switchVtable + 0xB;
	SwitchParams* params    = object->motion.frame->params;
	object->base.className  = switchClassName;
	object->base.objectSize = 0xFC;
	object->panel           = object->motion.frame->pos;
	object->pos             = object->panel;
	object->panel.y         = switchPanelHeight[0];
	object->ang             = object->motion.frame->ang;
	object->kind            = params->kind;
	object->value           = params->value;
	if (params->mode != 0) {
		object->state = 2;
	} else {
		object->state = 1;
	}

	object->clump = fn_80150588(switchModel);
	u32 flag      = *(volatile u32*)&object->motion.frame->condition;
	objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(
	    object->clump, ((flag & 0x1C0000) >> 18) + 4);
	object->panelAtomic = objRpClumpGetAtomicWithTexture(object->clump, NULL, switchPanelNodeName);
	object->frameAtomic
	    = objRpClumpGetAtomicWithTexture(object->clump, NULL, switchPanelMaterialName);
	object->light = NULL;
	for (s32 i = 0; object->light == NULL; i++) {
		object->light = (SwitchAtomic*)objRpClumpGetAtomicWithTexture(
		    object->clump, NULL, switchStateNames[i]);
	}
	RpAtomicMCCSetMaterialPointer((RpAtomic*)object->light, (RpMaterial*)switchOffHandle);
	RpAtomicMCCSetActive((RpAtomic*)object->light, 1);
	object->light->renderCallBack = (void*)switchGuard;
	if (object->light->renderCallBack == NULL) {
		object->light->renderCallBack = (void*)fn_8014F1B0;
	}

	if (object->state != 2) {
		fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), object->clump);
	}
	Init__7C_COLLIFP8CCL_INFOiUc(object->colli, switchCclInfo, 1, 4);
	object->unkC1 = 0;
	if (object->shape != NULL && object->kind == 3) {
		object->shape->flags |= 0x10;
	}

	if (object->motion.frame->work != NULL) {
		object->workState = object->motion.frame->work->state;
		switchSetPanelRender(object);
	} else {
		SwitchWork* work           = (SwitchWork*)__nw__FUl(0x14);
		object->motion.frame->work = work;
		object->workState          = 0;
		switchSetPanelRender(object);
		work->state = object->workState;
	}

	RpAtomicMCCSetMaterialPointer((RpAtomic*)object->light, (RpMaterial*)switchOffHandle);
	OBJ_CUSTOMRENDER* render = RpAtomicMCCGetCustomRenderCallBack((RpAtomic*)object->light);
	render->pData            = (void*)0x10;

	if (object->motion.frame->work != NULL) {
		SwitchFrame* other = ((SwitchFrame**)(lbl_8042C298 + 0x30))[object->motion.frame->group];
		f32 range          = switchNearbyRange[0];
		for (; other != NULL; other = other->next) {
			if (other->type == 0x24
			    && Distance2P2P(&object->motion.frame->pos, &other->pos) < range) {
				object->motion.frame->work->mark = 0x12345678;
				object->motion.frame->work->pos  = object->motion.frame->pos;
				break;
			}
		}
	}
	return object;
}
