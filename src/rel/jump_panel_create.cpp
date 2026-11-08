// jumpPanelCreate, the factory of TObjJumppanel (the PS2 build's name), the jump
// panel: a flat model, turned about X by the placement's first angle, whose
// collision shape is tilted to match. The constructor is inline here. Large
// enough that inline_max_size has to be raised for the factory to take it, and
// compiled without common subexpression elimination (the retail works the
// frame's matrix address out again for each turn). The placement's light bits
// are read once before the clump is handed to the light callback.
//
// The angle and the two reaches are converted with the module's shared
// int-to-float bias, whose 8 bytes of .rodata this unit owns.

#pragma inline_max_size(2048)
#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct RpAtomic;
struct RwFrame;

extern "C" char* CL_TObjJumppanel;
extern "C" CCL_INFO jumppanelInfo;
extern "C" RpClump* jumpPanelModel;
extern "C" char jumpPanelTexture[];
extern "C" const f32 jumpPanelAngleScale[1];
extern "C" const f32 jumpPanelBias[1];
extern "C" const f32 jumpPanelOne[1];
extern "C" const f32 jumpPanelTwo[1];
extern "C" const f32 jumpPanelZero[1];
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" TObject* lbl_8042C110;
extern "C" u8* lbl_8042C1D0;

struct JumpPanelClump {
	u8 unk00[4];
	RwFrame* frame; // 0x04
};

struct JumpPanelParams {
	f32 reachA; // 0x00
	f32 reachB; // 0x04
	s16 kind;   // 0x08
};

struct OBJ_CUSTOMRENDER {
	void* callback;
	void* pData;
};

extern "C" JumpPanelClump* fn_80150588(RpClump* clump);
extern "C" void fn_8015BB08(void* world, JumpPanelClump* clump);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_8019ED68(RwFrame* frame, const RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* pos, s32 combine);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" RpAtomic* objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(
    JumpPanelClump* clump, RpAtomic* atomic);
extern "C" void fn_801491A8(RpAtomic* atomic);
extern "C" void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
    JumpPanelClump* clump, u32 light);
extern "C" RpAtomic* objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(
    JumpPanelClump* clump, RpAtomic* atomic, char* name);
extern "C" OBJ_CUSTOMRENDER* RpAtomicMCCGetCustomRenderCallBack(RpAtomic* atomic);

class TObjJumppanel : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s32 state;   // 0xB8
	u8 flags[8]; // 0xBC
	s16 kind;    // 0xC4
	u8 padC6[2];
	RwV3d pos;             // 0xC8
	sAngle ang;            // 0xD4
	f32 turn;              // 0xE0
	f32 reachA;            // 0xE4
	f32 reachB;            // 0xE8
	JumpPanelClump* clump; // 0xEC
	s32 zeroF0;            // 0xF0

	TObjJumppanel(TObject* parent);

	virtual void Exec();
	virtual ~TObjJumppanel();
	virtual void EditOnChange(SETDATA_PARAM*);
};

#pragma opt_common_subs off
inline TObjJumppanel::TObjJumppanel(TObject* parent)
    : TObject(parent)
{
	ClassName               = CL_TObjJumppanel;
	DispTime                = 0xF4;
	pos                     = ObjParam->setData.pos;
	ang                     = ObjParam->setData.ang;
	turn                    = jumpPanelAngleScale[0] * (f32)ang.x;
	ang.z                   = 0;
	JumpPanelParams* params = (JumpPanelParams*)ObjParam->setData.setBuffer;
	reachA                  = jumpPanelBias[0] + params->reachA;
	reachB                  = jumpPanelBias[0] + params->reachB;
	kind                    = params->kind;
	flags[0]                = 0;
	flags[1]                = 0;
	flags[2]                = 0;
	flags[3]                = 0;
	flags[4]                = 0;
	flags[5]                = 0;
	flags[6]                = 0;
	flags[7]                = 0;
	zeroF0                  = 0;
	state                   = 1;
	clump                   = fn_80150588(jumpPanelModel);
	fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x725C), clump);
	RwFrame* frame = clump->frame;
	fn_8019ED68(frame, &AxisX, turn, 0);
	f32 sin = fn_800D7B00(ang.y);
	fn_80195790((u8*)frame + 0x10, &AxisY, jumpPanelOne[0] - fn_800D7AE4(ang.y), sin, 2);
	fn_80195790((u8*)frame + 0x10, &AxisY, jumpPanelTwo[0], jumpPanelZero[0], 1);
	fn_8019EB94(frame, &pos, 2);
	Init(&jumppanelInfo, 1, 4);
	if (info != NULL) {
		*(s32*)((u8*)info + 0x28) = 0x4000;
		*(s32*)((u8*)info + 0x2C) = ang.x - 0x1200;
		CalcRange();
	}
	fn_801491A8(objRpClumpGetAtomic__FP7RpClumpP8RpAtomic(clump, NULL));
	u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
	objRpClumpForAllAtomicsToSetRenderCallbackToUseLight__FP7RpClumpUi(
	    clump, ((flag & 0x1C0000) >> 18) + 4);
	OBJ_CUSTOMRENDER* cr = RpAtomicMCCGetCustomRenderCallBack(
	    objRpClumpGetAtomicWithTexture__FP7RpClumpP8RpAtomicPc(clump, NULL, jumpPanelTexture));
	cr->callback = (void*)0x10;
}

extern "C" void jumpPanelCreate(void)
{
	new TObjJumppanel(lbl_8042C110);
}
