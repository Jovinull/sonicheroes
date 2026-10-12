#include "types.h"

// TEnemyGadgetBomb's constructor (the PS2 build's name and arguments): the
// bomb a searcher drops, an object under the stage's enemy task. It keeps its
// searcher, starts a little above the given position with the given angles,
// takes the searcher's light set, gives its collision its shape there (without
// flag 0x40), finds the ground below it for its shadow, and starts unscaled
// with its fuse (0x78 frames) and life (0x708 frames) set.

typedef struct RpClump RpClump;

struct RwV3d {
	f32 x, y, z;
};

struct sAngle {
	s32 x, y, z;
};

typedef struct CCL_INFO CCL_INFO;

// The searcher, only as far as the virtual the bomb calls: its light set, the
// 35th slot (vtable offset 0x90).
class GadgetSearcher
{
public:
	u8 unk00[0x18];
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual u32 GetLightNum();
};

typedef struct GadgetBomb {
	char* className; // 0x00
	u8 unk04[0x14];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 dispTime; // 0x1E
	u8 unk20[0x8];
	u8 colli[0x8]; // 0x28, C_COLLI
	u16 colliFlag; // 0x30
	u8 unk32[0x56];
	RwV3d colliPos; // 0x88
	u8 unk94[0x1C];
	GadgetSearcher* searcher; // 0xB0
	s32 unkB4;                // 0xB4
	RpClump* clump;           // 0xB8
	RwV3d pos;                // 0xBC
	RwV3d scale;              // 0xC8
	sAngle ang;               // 0xD4
	u32 light;                // 0xE0
	f32 shadowY;              // 0xE4
	s32 fuse;                 // 0xE8
	s32 life;                 // 0xEC
	s32 unkF0;                // 0xF0
} GadgetBomb;

extern "C" void* lbl_8042C10C;
extern "C" void* __vt__16TEnemyGadgetBomb[];
extern "C" char* CL_TEnemyGadgetBomb;
extern "C" CCL_INFO gadgetBombCclInfo;
extern "C" const f32 gadgetBombLift[1];
extern "C" const f32 gadgetBombShadowLift[1];
extern "C" const f32 gadgetBombScaleXZ[1];
extern "C" const f32 gadgetBombScaleY[1];

extern "C" void __ct__7TObjectFP7TObject(void* object, void* parent);
extern "C" void __ct__7C_COLLIFv(void* colli);
extern "C" void Init__7C_COLLIFP8CCL_INFOiUc(void* colli, CCL_INFO* info, s32 count, u8 kind);
f32 GetShadowPos(RwV3d* pos, sAngle* ang, int kind);

extern "C" GadgetBomb* __ct__16TEnemyGadgetBombFP17TObjEnemySearcherP5RwV3dP6sAngle(
    GadgetBomb* object, GadgetSearcher* searcher, RwV3d* pos, sAngle* ang)
{
	sAngle ground;

	__ct__7TObjectFP7TObject(object, lbl_8042C10C);
	__ct__7C_COLLIFv(object->colli);
	object->vtable    = __vt__16TEnemyGadgetBomb;
	object->className = CL_TEnemyGadgetBomb;
	object->dispTime  = 0xF4;
	object->searcher  = searcher;
	object->pos       = *pos;
	object->pos.y += gadgetBombLift[0];
	object->ang   = *ang;
	object->light = object->searcher->GetLightNum();
	Init__7C_COLLIFP8CCL_INFOiUc(object->colli, &gadgetBombCclInfo, 1, 3);
	object->colliPos = object->pos;
	object->colliFlag &= ~0x40;
	object->shadowY = GetShadowPos(&object->pos, &ground, 1);
	object->shadowY += gadgetBombShadowLift[0];
	object->scale.x = gadgetBombScaleXZ[0];
	object->scale.y = gadgetBombScaleY[0];
	object->scale.z = gadgetBombScaleXZ[0];
	object->unkB4   = 0;
	object->fuse    = 0x78;
	object->unkF0   = 0;
	object->clump   = NULL;
	object->life    = 0x708;
	return object;
}
