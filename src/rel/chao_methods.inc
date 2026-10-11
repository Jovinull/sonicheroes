// TObjChao::SearchCage and TObjChao::SetPosition. The constructor and Exec
// inline both; rel/chao_search_cage.cpp and rel/chao_set_position.cpp each
// define one of the two macros empty to emit that member's out-of-line copy,
// which has no caller and is kept with force_active. Include after
// chao_class.inc.

#include "game/object.h"

#ifndef CHAO_SEARCH_CAGE_INLINE
#define CHAO_SEARCH_CAGE_INLINE inline
#endif
#ifndef CHAO_SET_POSITION_INLINE
#define CHAO_SET_POSITION_INLINE inline
#endif

struct ChaoTask {
	u8 pad00[0x28];
	u16 classId; // 0x28
	u8 pad2A[0xE];
	ChaoTask* next; // 0x38
};

struct ChaoTaskLists {
	u8 pad00[0x30];
	ChaoTask* lists[1]; // 0x30
};

struct ChaoWork {
	u32 magic; // 0x00
	RwV3d pos; // 0x04
	u32 unk10; // 0x10
};

extern "C" ChaoTaskLists* lbl_8042C298;
extern "C" const f32 chaoCageReach[1];

f32 Distance2P2P(const RwV3d* a, const RwV3d* b);

CHAO_SEARCH_CAGE_INLINE void TObjChao::SearchCage()
{
	if (ObjParam->originalWork == NULL) {
		ChaoTask* task;
		for (task = lbl_8042C298->lists[ObjParam->setData.communicateId]; task != NULL;
		    task  = task->next) {
			if (task->classId == 0x24
			    && Distance2P2P(&ObjParam->setData.pos, (RwV3d*)task) < chaoCageReach[0]) {
				ObjParam->originalWork                     = new ChaoWork;
				((ChaoWork*)ObjParam->originalWork)->magic = 0x12345678;
				((ChaoWork*)ObjParam->originalWork)->pos   = ObjParam->setData.pos;
				return;
			}
		}
	}
}

extern "C" const f32 chaoZero[1];
extern "C" const f32 chaoQuarter[1];
extern "C" const f32 chaoMinusQuarter[1];
extern "C" f32 chaoScale;
extern "C" RwV3d AxisY;
extern RwMatrix* pCurrentMatrix;
extern "C" void fn_8019EB94(RwFrame* frame, RwV3d* translation, s32 combine);
extern "C" void fn_8019ED68(RwFrame* frame, RwV3d* axis, f32 angle, s32 combine);
extern "C" void fn_8019EC30(RwFrame* frame, RwV3d* scale, s32 combine);

CHAO_SET_POSITION_INLINE void TObjChao::SetPosition()
{
	s32 inCage     = 0;
	ChaoWork* work = (ChaoWork*)ObjParam->originalWork;

	if (work != NULL && work->magic == 0x12345678) {
		pos    = work->pos;
		inCage = 1;
	}

	RwFrame* frame = (RwFrame*)((RwObject*)clump)->parent;
	angle += spin;
	fn_8019EB94(frame, &pos, 0);
	fn_8019ED68(frame, &AxisY, angle, 1);
	if (!inCage) {
		RwV3d out;
		out.x = out.y = chaoZero[0];
		out.z         = offset;
		fn_8019EB94(frame, &out, 1);
		fn_8019ED68(frame, &AxisY, spin > chaoZero[0] ? chaoQuarter[0] : chaoMinusQuarter[0], 1);
	}

	// The shared matrix-position convention substitutes the current matrix for null.
	worldPos = (!&frame->modelling) ? pCurrentMatrix->pos : frame->modelling.pos;

	RwV3d scale;
	scale.x = scale.y = scale.z = chaoScale;
	fn_8019EC30(frame, &scale, 1);
}
