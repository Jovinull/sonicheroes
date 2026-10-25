#include "types.h"

// The lighthouse's Unload and Load hooks (s20dLighthouseUnload and s20dLighthouseLoad here): its model
// list is released; the list is loaded and the two models it keeps at hand,
// entries 3 and 4, are looked up in it.

extern "C" u8 s20dLighthouseModelList[];
extern "C" void* s20dLighthouseModels[2];

extern "C" void fn_3_B92FC(void* list, void* a, void* b);
extern "C" void* fn_3_B9D10(void* list, s16 index);
extern "C" void fn_3_BA3E8(s32 a, void* list, void* b, void* c);

extern "C" void s20dLighthouseUnload(void)
{
	fn_3_BA3E8(0, s20dLighthouseModelList, NULL, NULL);
}

extern "C" void s20dLighthouseLoad(void)
{
	fn_3_B92FC(s20dLighthouseModelList, NULL, NULL);
	s20dLighthouseModels[0] = fn_3_B9D10(s20dLighthouseModelList, 3);
	s20dLighthouseModels[1] = fn_3_B9D10(s20dLighthouseModelList, 4);
}
