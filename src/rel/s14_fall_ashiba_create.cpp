#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s14FallAshibaCreate, the editor record factory for TObjS14FBoard (the class
// name its constructor stores), the falling board, in stage13D. It is a real
// new-expression of the class; rel/sample1_create.cpp has the long form of the
// allocation.
//
// The constructor takes the board and its second part through fn_9_75908 with
// the light set the placement's flags pick, as rel/s14_koware_create.cpp does,
// keeps the placement's position as its position and its start, clears its
// speed and state and takes the module's 2 shapes for its collision block (its
// third base). With the board (and then with the second part too), each
// frame is turned by the placement's Y angle and moved to the position. The
// set data gets a cleared work word when it has none.

// The part of a RenderWare frame used here: its modelling matrix.
struct FBoardFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

extern "C" char* CL_TObjS14FBoard;
extern "C" u8 s14FallAshibaModels[];
extern "C" CCL_INFO s14FallAshibaCclInfo[2];
extern "C" const f32 s14FallAshibaZero;
extern "C" const f32 s14FallAshibaOne[1];
extern "C" const RwV3d AxisY;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_9_75908(void* table, s16 index, s8 lightSet, RpClump** clump, void* frame);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(void* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* translation, s32 combine);

class TObjS14FBoard : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s8 state;        // 0xB8
	u8 padB9[3];     // 0xB9
	f32 unkBC;       // 0xBC
	RwV3d pos;       // 0xC0
	RwV3d start;     // 0xCC
	RwV3d spd;       // 0xD8
	s32 unkE4;       // 0xE4
	s32 unkE8;       // 0xE8
	RpClump* clump;  // 0xEC
	RpClump* clump2; // 0xF0

	TObjS14FBoard(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjS14FBoard;
		DispTime  = 0xF4;

		u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		fn_9_75908(s14FallAshibaModels, 0, ((flag & 0x1C0000) >> 18) + 4, &clump, NULL);
		flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
		fn_9_75908(s14FallAshibaModels, 1, ((flag & 0x1C0000) >> 18) + 4, &clump2, NULL);
		pos   = ObjParam->setData.pos;
		start = pos;
		spd.x = spd.y = spd.z = s14FallAshibaZero;
		unkE4 = unkE8 = 0;
		unkBC         = s14FallAshibaZero;
		state         = 0;
		Init(s14FallAshibaCclInfo, 2, 4);
		if (clump != NULL) {
			FBoardFrame* frame = *(FBoardFrame**)((u8*)clump + 4);
			f32 sine;

			sine = fn_800D7B00(ObjParam->setData.ang.y);
			fn_80195790(frame->modelling, &AxisY,
			    s14FallAshibaOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
			fn_8019E880(frame);
			fn_8019EB94(frame, &pos, 2);
			if (clump2 != NULL) {
				frame = *(FBoardFrame**)((u8*)clump2 + 4);
				sine  = fn_800D7B00(ObjParam->setData.ang.y);
				fn_80195790(frame->modelling, &AxisY,
				    s14FallAshibaOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
				fn_8019E880(frame);
				fn_8019EB94(frame, &pos, 2);
			}
		}
		if (ObjParam->originalWork == NULL) {
			s32* work              = new s32;
			ObjParam->originalWork = work;
			*work                  = 0;
		}
	}
	virtual ~TObjS14FBoard();
};

extern "C" void s14FallAshibaCreate(void)
{
	new TObjS14FBoard(lbl_8042C110);
}
