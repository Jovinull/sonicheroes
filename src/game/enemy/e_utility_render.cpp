// Complete C++ enemy render utility unit. GC accesses determine platform offsets.
#include "game/enemy/e_utility_render.h"
struct RpWorld;
// Accessed prefixes only; no allocation or sizeof of these external objects.
struct RenderLandManagerView {
	u8 unknown[0x7250];
	RpWorld* world[25];
};
struct RenderLightView {
	u8 unknown[0x4be];
	s8 current_num;
};
enum RwBlendFunction {
	rwBLENDNABLEND                  = 0,
	rwBLENDZERO                     = 1,
	rwBLENDONE                      = 2,
	rwBLENDSRCCOLOR                 = 3,
	rwBLENDINVSRCCOLOR              = 4,
	rwBLENDSRCALPHA                 = 5,
	rwBLENDINVSRCALPHA              = 6,
	rwBLENDDESTALPHA                = 7,
	rwBLENDINVDESTALPHA             = 8,
	rwBLENDDESTCOLOR                = 9,
	rwBLENDINVDESTCOLOR             = 10,
	rwBLENDSRCALPHASAT              = 11,
	rwBLENDFUNCTIONFORCEENUMSIZEINT = 2147483647
};
enum RwCullMode {
	rwCULLMODENACULLMODE       = 0,
	rwCULLMODECULLNONE         = 1,
	rwCULLMODECULLBACK         = 2,
	rwCULLMODECULLFRONT        = 3,
	rwCULLMODEFORCEENUMSIZEINT = 2147483647
};

static RwBlendFunction src, dst;
static RwCullMode cullmode;
static s32 fog;
extern "C" {
extern RenderLandManagerView* lbl_8042C1D0;
extern RenderLightView lbl_802D5E80;
s32 fn_80194234(s32, void*);
s32 fn_80194294(s32, void*);
void StartIgnoreLight__6CLIGHTFP7RpWorld(RenderLightView*, RpWorld*);
void EndIgnoreLight__6CLIGHTFP7RpWorld(RenderLightView*, RpWorld*);
void SetCurrentNum__6CLIGHTFSc(RenderLightView*, s8);
void SetLightRegular__6CLIGHTFSc(RenderLightView*, s8);
}
namespace nRender
{
void FogDisable()
{
	fn_80194234(14, (void*)0);
}
void FogEnable()
{
	fn_80194234(14, (void*)1);
}
void DisableLight(s32 world_num)
{
	StartIgnoreLight__6CLIGHTFP7RpWorld(&lbl_802D5E80, lbl_8042C1D0->world[world_num]);
}
void EnableLight(s32 world_num)
{
	EndIgnoreLight__6CLIGHTFP7RpWorld(&lbl_802D5E80, lbl_8042C1D0->world[world_num]);
}
void SetLightNum(u32 lightnum)
{
	SetCurrentNum__6CLIGHTFSc(&lbl_802D5E80, (s8)lightnum);
	SetLightRegular__6CLIGHTFSc(&lbl_802D5E80, lbl_802D5E80.current_num);
}
void SetRenderStateForBlendAdd()
{
	fn_80194234(10, (void*)rwBLENDSRCALPHA);
	fn_80194234(11, (void*)rwBLENDONE);
	fn_80194234(20, (void*)rwCULLMODECULLNONE);
}
void LoadRenderState()
{
	fn_80194234(20, (void*)cullmode);
	fn_80194234(10, (void*)src);
	fn_80194234(11, (void*)dst);
	fn_80194234(14, (void*)fog);
}
void SaveRenderState()
{
	fn_80194294(10, &src);
	fn_80194294(11, &dst);
	fn_80194294(20, &cullmode);
	fn_80194294(14, &fog);
}
}
