#include "types.h"

// The capture enemy's shine display (captureDispShine here), the same in the
// seven stage modules that carry the capture: while spinning, with additive
// blending, its three parts are tinted by the module's shine color at the
// pulse's strength, the other texture sets get ready, the parts are rendered,
// and the shine model is drawn once per bubble, scaled to the bubble and at
// its place.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwRGBAReal {
	f32 red, green, blue, alpha;
} RwRGBAReal;

struct RwFrame;

struct RpClump {
	u8 unk00[0x4];
	RwFrame* frame; // 0x04
};

typedef struct CaptureBubble {
	RwV3d pos;   // 0x00
	RwV3d speed; // 0x0C
	f32 scale;   // 0x18
	f32 grow;    // 0x1C
	f32 top;     // 0x20
} CaptureBubble; // 0x24

class TEnemyMatTexture
{
public:
	void PreDisp(s32 kind);

	u8 unk00[0x14];
}; // 0x14

namespace nRender
{
void SetLightNum(u32 light);
void SaveRenderState();
void SetRenderStateForBlendAdd();
void LoadRenderState();
}

struct CaptureBase {
	u8 unk000[0x18];
};

// TObjEnemy's virtual functions up to GetCurrentLightNum (slot 0x90).
class Capture : public CaptureBase
{
public:
	virtual ~Capture();
	virtual void Virtual0C();
	virtual void Virtual10();
	virtual void Virtual14();
	virtual void Virtual18();
	virtual void Virtual1C();
	virtual void Virtual20();
	virtual void Virtual24();
	virtual void Virtual28();
	virtual void Virtual2C();
	virtual void Virtual30();
	virtual void Virtual34();
	virtual void Virtual38();
	virtual void Virtual3C();
	virtual void Virtual40();
	virtual void Virtual44();
	virtual void Virtual48();
	virtual void Virtual4C();
	virtual void Virtual50();
	virtual void Virtual54();
	virtual void Virtual58();
	virtual void Virtual5C();
	virtual void Virtual60();
	virtual void Virtual64();
	virtual void Virtual68();
	virtual void Virtual6C();
	virtual void Virtual70();
	virtual void Virtual74();
	virtual void Virtual78();
	virtual void Virtual7C();
	virtual void Virtual80();
	virtual void Virtual84();
	virtual void Virtual88();
	virtual void Virtual8C();
	virtual u32 GetCurrentLightNum();

	u8 unk01C[0x26C];
	f32 pulse; // 0x288
	s32 spin;  // 0x28C
	u8 unk290[0x48];
	RpClump* parts[3]; // 0x2D8
	RpClump* shine;    // 0x2E4
	u8 unk2E8[0x44];
	s32 count;                 // 0x32C
	CaptureBubble bubbles[16]; // 0x330
	u8 unk570[0xC];
	s32 special; // 0x57C
};

extern "C" TEnemyMatTexture captureObjectGlobalArray[8];
extern "C" const RwRGBAReal captureShineColor;
extern "C" const RwV3d captureShineScale;

void objRpClumpForAllMaterialsToChangeMaterialColor(RpClump* clump, RwRGBAReal* color);

extern "C" {
void fn_8014FF2C(RpClump* clump);
void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);
void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
}

extern "C" void captureDispShine(Capture* object)
{
	if (object->spin != 0) {
		nRender::SetLightNum(object->GetCurrentLightNum());
		nRender::SaveRenderState();
		nRender::SetRenderStateForBlendAdd();
		nRender::SetLightNum(0x10);
		{
			RwRGBAReal color = captureShineColor;

			color.alpha = object->pulse;
			objRpClumpForAllMaterialsToChangeMaterialColor(object->parts[0], &color);
			objRpClumpForAllMaterialsToChangeMaterialColor(object->parts[1], &color);
			objRpClumpForAllMaterialsToChangeMaterialColor(object->parts[2], &color);
		}
		{
			s32 i;

			for (i = 2; i < 8; i++) {
				captureObjectGlobalArray[i].PreDisp(object->special);
			}
		}
		if (object->parts[0] != NULL) {
			fn_8014FF2C(object->parts[0]);
		}
		if (object->parts[1] != NULL) {
			fn_8014FF2C(object->parts[1]);
		}
		if (object->parts[2] != NULL) {
			fn_8014FF2C(object->parts[2]);
		}
		{
			RwFrame* frame = object->shine->frame;
			s32 i;

			for (i = 0; i < object->count; i++) {
				// (an initializer in the original; the volatile read keeps the per-bubble load)
				RwV3d scale = *(const volatile RwV3d*)&captureShineScale;

				scale.z = scale.x = object->bubbles[i].scale;
				fn_8019EC30(frame, &scale, 0);
				fn_8019EB94(frame, &object->bubbles[i].pos, 2);
				fn_8014FF2C(object->shine);
			}
		}
		nRender::LoadRenderState();
	}
}
