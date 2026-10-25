#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s03PipeCreate, the factory rel/s03_pipe_register.cpp puts in the editor
// record: a new TObjS03Pipe (the class name its constructor stores). For the
// pipe's own set id (0x300) it makes its frame (fn_8019E344), falls back to
// kind 0 for a kind out of range, takes its part count from the kind's table
// entry, notes whether it is on stage 5, clears its state and runs its first
// own virtual (vtable slot 0x38, fn_4_80C28) before asking whether the editor
// is on. The allocation is a real new-expression of the class
// (rel/sample1_create.cpp).

// one of the pipe kinds: the two bytes multiplied into its part count
struct S03PipeKind {
	u8 unk00[0x5];
	u8 columns; // 0x05
	u8 rows;    // 0x06
	u8 unk07[0x31];
}; // 0x38

// the set data's parameters
struct S03PipeParam {
	s8 kind; // 0x00
};

// the game state: only the stage is read here
struct S03PipeGameState {
	u8 unk00[0x2C];
	s32 stage; // 0x2C
};

struct RwFrame;

extern "C" char* CL_TObjS03Pipe;
extern "C" s8 lbl_4_bss_1388;
extern "C" S03PipeKind* lbl_4_bss_1390;
extern "C" S03PipeGameState lbl_8029C310;
extern "C" TObject* lbl_8042C110;
extern "C" RwFrame* fn_8019E344(void);

class TObjS03Pipe : public TObject, public TObjSetObj, public C_COLLI
{
public:
	s8 unkB8;    // 0xB8
	s8 onStage5; // 0xB9
	s8 unkBA;    // 0xBA
	u8 parts;    // 0xBB
	u8 padBC[0x18];
	RwFrame* frame; // 0xD4
	s32 unkD8;      // 0xD8
	s32 unkDC;      // 0xDC
	s32 unkE0;      // 0xE0
	s32 unkE4;      // 0xE4
	u8 padE8[0x24];

	TObjS03Pipe(TObject* parent)
	    : TObject(parent)
	{
		S03PipeParam* param = (S03PipeParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS03Pipe;
		DispTime  = 0x10C;
		if (ObjParam->setData.uniqueId == 0x300) {
			frame = fn_8019E344();
			if (param->kind < 0 || param->kind >= lbl_4_bss_1388) {
				param->kind = 0;
			}
			parts = lbl_4_bss_1390[param->kind].rows * lbl_4_bss_1390[param->kind].columns;
			if (lbl_8029C310.stage == 5) {
				onStage5 = 1;
			} else {
				onStage5 = 0;
			}
			unkB8 = unkE0 = unkDC = unkD8 = unkBA = 0;
			Virtual38();
			OnEdit();
		}
		unkE4 = 0;
	}
	virtual ~TObjS03Pipe();
	// the class's own virtuals (vtable slots 0x38 and 0x3C); its EditOnChange
	// comes after them, at 0x40, with the thunk for the set-object base at 0x34
	virtual void Virtual38();
	virtual void Virtual3C();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s03PipeCreate(void)
{
	new TObjS03Pipe(lbl_8042C110);
}
