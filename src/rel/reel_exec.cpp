#include "types.h"

// TObjReel::Exec (the PS2 build's name, by its place in the PS2 order;
// reelExec here). Out of range or killed, the reel ends; in the editor it
// takes its placement again and is placed (SetParameter and SetPosition
// inlined). Otherwise a reel at rest looks for a player to hang
// (CheckHangedPlayer) and a working one carries its player (ReelPlayer); when
// its length changed it is placed again, its wait counts down, and the
// collision follows it.

#include "src/rel/reel.inc"

extern "C" s32 CheckRangeOut__10TObjSetObjFv(void* setObj);
extern "C" s32 CheckMustKill__10TObjSetObjFv(void* setObj);
extern "C" s32 OnEdit__10TObjSetObjFv(void* setObj);
extern "C" void Entry__7C_COLLIFv(void* colli);
extern "C" void reelCheckHangedPlayer(Reel* object);
extern "C" void reelPlayer(Reel* object);

extern "C" void reelExec(Reel* object)
{
	if (CheckRangeOut__10TObjSetObjFv(&object->frame)
	    || CheckMustKill__10TObjSetObjFv(&object->frame)) {
		object->signal |= 1;
		return;
	}
	if (OnEdit__10TObjSetObjFv(&object->frame)) {
		reelSetParameter(object);
		reelSetPosition(object);
		return;
	}
	object->target = object->current;
	switch (object->state) {
		case 1:
			reelCheckHangedPlayer(object);
			break;
		default:
			reelPlayer(object);
			break;
	}
	if (object->current != object->target) {
		reelSetPosition(object);
	}
	if (object->wait > 0) {
		object->wait--;
	}
	object->colliPrePos = object->colliPos;
	object->colliPos    = object->pos;
	object->colliAng    = object->ang;
	Entry__7C_COLLIFv(object->colli);
}
