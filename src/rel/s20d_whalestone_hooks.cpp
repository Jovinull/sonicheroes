#include "types.h"

// The whalestone's Unload and Load hooks (s20dWhalestoneUnload and s20dWhalestoneLoad here): its model
// list is released; the list is loaded and the two models it keeps at hand,
// entries 6 and 7, are looked up in it.

extern "C" u8 s20dWhalestoneModelList[];
extern "C" void* s20dWhalestoneModels[2];

extern "C" void fn_3_B92FC(void* list, void* a, void* b);
extern "C" void* fn_3_B9D10(void* list, s16 index);
extern "C" void fn_3_BA3E8(s32 a, void* list, void* b, void* c);

extern "C" void s20dWhalestoneUnload(void)
{
	fn_3_BA3E8(0, s20dWhalestoneModelList, NULL, NULL);
}

extern "C" void s20dWhalestoneLoad(void)
{
	fn_3_B92FC(s20dWhalestoneModelList, NULL, NULL);
	s20dWhalestoneModels[0] = fn_3_B9D10(s20dWhalestoneModelList, 6);
	s20dWhalestoneModels[1] = fn_3_B9D10(s20dWhalestoneModelList, 7);
}
