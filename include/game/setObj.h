#ifndef GAME_SET_OBJ_H
#define GAME_SET_OBJ_H
#include "game/pathctrl.h"

struct sBitFlag {
	u32 Flag;
};
struct SETDATA_PARAM {
	RwV3d pos;
	sAngle ang;
	sBitFlag condition, condition2, originalCondition, originalCondition2;
	u16 uniqueId;
	u8 communicateId, range;
	s32* setBuffer;
};
struct SETOBJ_PARAM {
	SETDATA_PARAM setData;
	void* originalWork;
	SETOBJ_PARAM *prev, *next;
	void* objPointer;
};
class TObjSetObj
{
public:
	SETOBJ_PARAM* ObjParam;
	virtual void EditOnChange(SETDATA_PARAM*);
	s32 CheckMustKill();
	s32 OnEdit();
	s32 CheckRangeOutWithoutIgnorRangeFlag();
	s32 CheckRangeOut();
	void SetDestroy();
	void SetEnd();
	void SetInit();
	~TObjSetObj();
	TObjSetObj();
	void ClrConditionBit(u32 flag) { ObjParam->setData.condition.Flag &= ~flag; }
	void SetConditionBit(u32 flag) { ObjParam->setData.condition.Flag |= flag; }
	s32 TstConditionBit(u32 flag)
	{
		const sBitFlag& condition = ObjParam->setData.condition;
		return (condition.Flag & flag) != 0;
	}
};
s32 setobjCheckRangeOut2(const RwV3d*, f32);
#endif
