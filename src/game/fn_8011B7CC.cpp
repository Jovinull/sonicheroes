#include "game/rw_engine.h"

extern "C" {
void fn_8020C700(void* block);
void fn_8020C2D8(RtAnimAnimation* animation);

s32 fn_8011B7CC(RpUVAnimAnimation* animation)
{
	fn_8020C700(animation->instance);
	fn_8020C2D8(animation->pAnim);
	lbl_8042C9A4->rwfree(animation);
	return 1;
}
}
