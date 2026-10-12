#include "types.h"

#include "src/rel/signal_class.inc"

// TObjSignal::Exec (signalExec here). Out of range or marked to die, it ends.
// While the editor moves it, it takes the placement again and sets the model.
// Otherwise it bobs: its height is the base height plus signalBobScale times the
// sine of the game's frame counter (shifted into an angle), the model follows,
// and it records the volume's position and angles and re-enters its collision.

extern "C" u8* lbl_8042C180;
extern "C" const f32 signalBobScale[1];

extern "C" s32 CheckRangeOut__10TObjSetObjFv(void* setobj);
extern "C" s32 CheckMustKill__10TObjSetObjFv(void* setobj);
extern "C" s32 OnEdit__10TObjSetObjFv(void* setobj);
extern "C" void Entry__7C_COLLIFv(void* colli);

#pragma opt_common_subs off
extern "C" void signalExec(Signal* object)
{
	if (CheckRangeOut__10TObjSetObjFv(&object->setdata)
	    || CheckMustKill__10TObjSetObjFv(&object->setdata)) {
		object->signal |= 1;
		return;
	}
	if (OnEdit__10TObjSetObjFv(&object->setdata)) {
		signalSetParameter(object);
		signalSetPosition(object);
		return;
	}
	object->pos.y
	    = object->basePos.y + signalBobScale[0] * fn_800D7B00(*(s32*)(lbl_8042C180 + 0x30) << 8);
	signalSetPosition(object);
	object->colliOldPos.x = object->colliPos.x;
	object->colliOldPos.y = object->colliPos.y;
	object->colliOldPos.z = object->colliPos.z;
	object->colliPos.x    = object->pos.x;
	object->colliPos.y    = object->pos.y;
	object->colliPos.z    = object->pos.z;
	object->colliAngX     = object->angX;
	object->colliAngY     = object->angY;
	object->colliAngZ     = object->angZ;
	Entry__7C_COLLIFv(object->colli);
}
#pragma opt_common_subs reset
