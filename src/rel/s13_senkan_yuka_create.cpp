#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s13SenkanYukaCreate, the editor record factory for TObjS13FBoard, the
// battleship's moving floor boards, in stage13D. It is a real new-expression of
// the class; rel/sample1_create.cpp has the long form of the allocation.
//
// In the editor a zero speed in the placement's parameters becomes the
// default. The constructor takes its model through fn_9_75A80, notes whether
// the board moves (a non-zero distance), copies the placement's position,
// gives the collision block its three shapes (with a translating reactor
// when the shapes have one), keeps the distance and height, raises the
// position by the height, and turns the frame about Y by the placement's
// angle before moving it there.

struct RwV3d;

struct FBoardParam {
	f32 unk00;    // 0x00
	f32 distance; // 0x04
	f32 unk08;    // 0x08
	f32 height;   // 0x0C
	f32 speed;    // 0x10
};

// The part of a RenderWare frame used here: its modelling matrix.
struct FBoardFrame {
	u8 unk00[0x10];
	u8 modelling[0x40]; // 0x10
};

extern "C" char* CL_TObjS13FBoard;
extern "C" u8 s13FBoardModels[];
extern "C" CCL_INFO s13FBoardCclInfo[3];
extern "C" const f32 s13FBoardZero[1];
extern "C" const f32 s13FBoardDefaultSpeed[1];
extern "C" const f32 s13FBoardOne[1];
extern "C" RwV3d AxisY;
extern "C" TObject* lbl_8042C110;
s32 Construct_CCL_REACTOR_TRANS(CCL_INFO* info);
extern "C" void fn_9_75A80(void* table, s16 index, RpClump** clump, void* frame);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" void fn_80195790(void* matrix, RwV3d* axis, f32 oneMinusCosine, f32 sine, s32 combine);
extern "C" void fn_8019E880(void* frame);
extern "C" void fn_8019EB94(void* frame, RwV3d* position, s32 combine);

class TObjS13FBoard : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s8 moving;      // 0xB8
	u8 padB9;       // 0xB9
	s16 unkBA;      // 0xBA
	f32 unkBC;      // 0xBC
	f32 unkC0;      // 0xC0
	f32 height;     // 0xC4
	RwV3d boardPos; // 0xC8
	RpClump* clump; // 0xD4

	TObjS13FBoard(TObject* parent)
	    : TObject(parent)
	{
		FBoardParam* param = (FBoardParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS13FBoard;
		DispTime  = 0xD8;

		if (OnEdit()) {
			if (s13FBoardZero[0] == param->speed) {
				param->speed = s13FBoardDefaultSpeed[0];
			}
		}
		fn_9_75A80(s13FBoardModels, 0, &clump, NULL);
		if (s13FBoardZero[0] == param->distance) {
			moving = 0;
		} else {
			moving = 1;
		}
		boardPos = ObjParam->setData.pos;
		Init(s13FBoardCclInfo, 3, 4);
		if (info != NULL) {
			Construct_CCL_REACTOR_TRANS(info);
		}
		unkBC  = s13FBoardZero[0];
		unkC0  = param->unk08;
		height = param->height;
		boardPos.y += height;
		unkBA = 0;

		FBoardFrame* frame = *(FBoardFrame**)((u8*)clump + 4);
		f32 sine           = fn_800D7B00(ObjParam->setData.ang.y);
		fn_80195790(frame->modelling, &AxisY,
		    s13FBoardOne[0] - fn_800D7AE4(ObjParam->setData.ang.y), sine, 0);
		fn_8019E880(frame);
		fn_8019EB94(frame, &boardPos, 2);
	}
	virtual ~TObjS13FBoard();
	virtual void Exec();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s13SenkanYukaCreate(void)
{
	new TObjS13FBoard(lbl_8042C110);
}
