// Complete setObj.cpp: nine surviving bodies and two inlined lifecycle methods.
// Metadata and GameCube evidence are recorded in docs/setobj-unit-evidence.md.
#include "game/setObj.h"

// External GameCube views contain only fields corroborated by accesses here.
struct TObjTeam {
	u8 pad0[0x3a];
	s8 leaderNo;
	u8 pad3B[0x110 - 0x3b];
	s8 member_player_no[3];
	s32 GetLeaderPlayerNo() const { return member_player_no[leaderNo]; }
};
struct SetObjModeView {
	u8 pad0[0x1e];
	s8 multiplayer;
};
class PlayerMaster
{
public:
	RwV3d* GetPlayerPositionHistory(s32, u8);
};
class TObjSetGen
{
public:
	void RebuildCommunicateIdList(u8);
};
extern "C" {
extern TObjTeam* lbl_80303DC8[4];
extern SetObjModeView* lbl_8042C180;
extern PlayerMaster lbl_8042C1BC;
extern TObjSetGen* lbl_8042C298;
extern void* lbl_8042C278;
extern s32 lbl_8042C28C;
extern SETOBJ_PARAM* lbl_8042C290;
f32 fn_800D71DC(const RwV3d*, const RwV3d*);
}

void TObjSetObj::EditOnChange(SETDATA_PARAM*) { }
s32 TObjSetObj::CheckMustKill()
{
	return TstConditionBit(4);
}
s32 TObjSetObj::OnEdit()
{
	return 0;
}

s32 TObjSetObj::CheckRangeOutWithoutIgnorRangeFlag()
{
	s32 result;
	SETOBJ_PARAM* param;
	f32 range  = 100.0f * (param = ObjParam)->setData.range;
	f32 range2 = range * range;
	if (fn_800D71DC(lbl_8042C1BC.GetPlayerPositionHistory(lbl_80303DC8[0]->GetLeaderPlayerNo(), 0),
	        &param->setData.pos)
	    <= range2)
		result = 0;
	else if (!lbl_8042C180->multiplayer)
		result = 1;
	else if (fn_800D71DC(
	             lbl_8042C1BC.GetPlayerPositionHistory(lbl_80303DC8[1]->GetLeaderPlayerNo(), 0),
	             &param->setData.pos)
	    <= range2)
		result = 0;
	else
		result = 1;
	return result;
}
s32 TObjSetObj::CheckRangeOut()
{
	s32 result;
	if (TstConditionBit(0x400))
		return 0;
	SETOBJ_PARAM* param = ObjParam;
	f32 range           = 100.0f * (param->setData.range + 1);
	f32 range2          = range * range;
	if (fn_800D71DC(lbl_8042C1BC.GetPlayerPositionHistory(lbl_80303DC8[0]->GetLeaderPlayerNo(), 0),
	        &param->setData.pos)
	    <= range2)
		result = 0;
	else if (!lbl_8042C180->multiplayer)
		result = 1;
	else if (fn_800D71DC(
	             lbl_8042C1BC.GetPlayerPositionHistory(lbl_80303DC8[1]->GetLeaderPlayerNo(), 0),
	             &param->setData.pos)
	    <= range2)
		result = 0;
	else
		result = 1;
	return result;
}
s32 setobjCheckRangeOut2(const RwV3d* pos, f32 range2)
{
	f32 dist2 = fn_800D71DC(
	    lbl_8042C1BC.GetPlayerPositionHistory(lbl_80303DC8[0]->GetLeaderPlayerNo(), 0), pos);
	if (dist2 <= range2)
		return 0;
	if (!lbl_8042C180->multiplayer)
		return 1;
	return !(
	    fn_800D71DC(
	        lbl_8042C1BC.GetPlayerPositionHistory(lbl_80303DC8[1]->GetLeaderPlayerNo(), 0), pos)
	    <= range2);
}

inline void TObjSetObj::SetDestroy()
{
	if (lbl_8042C298 && lbl_8042C278) {
		ClrConditionBit(2);
		ClrConditionBit(4);
		ObjParam->objPointer = 0;
		if (TstConditionBit(0x10)) {
			ClrConditionBit(0x10);
			if (ObjParam->originalWork) {
				::operator delete(ObjParam->originalWork);
				ObjParam->originalWork = 0;
			}
		}
		if (lbl_8042C28C == 1) {
			ClrConditionBit(1);
			ClrConditionBit(0x10);
			if (ObjParam->originalWork) {
				::operator delete(ObjParam->originalWork);
				ObjParam->originalWork = 0;
			}
		}
	}
}
void TObjSetObj::SetEnd()
{
	ClrConditionBit(1);
	SetDestroy();
	if (ObjParam->originalWork) {
		::operator delete(ObjParam->originalWork);
		ObjParam->originalWork = 0;
	}
	lbl_8042C298->RebuildCommunicateIdList(ObjParam->setData.communicateId);
}
inline void TObjSetObj::SetInit()
{
	if (lbl_8042C298 && lbl_8042C278) {
		ObjParam = lbl_8042C290;
		SetConditionBit(2);
		ClrConditionBit(4);
		ObjParam->objPointer = this;
	}
}
TObjSetObj::~TObjSetObj()
{
	SetDestroy();
}
TObjSetObj::TObjSetObj()
{
	SetInit();
}
