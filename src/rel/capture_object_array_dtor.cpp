#include "types.h"

// captureObjectGlobalArrayDtor, which rel/capture_register.cpp registers as the
// destructor of captureObjectGlobalArray: it destroys the array's eight texture
// sets.

extern "C" {
void __dt__16TEnemyMatTextureFv(void* texture, s16 flags);
void __destroy_arr(void* array, void* dtor, u32 size, u32 count);
}

extern "C" u8 captureObjectGlobalArray[];

extern "C" void captureObjectGlobalArrayDtor(void)
{
	__destroy_arr(captureObjectGlobalArray, (void*)__dt__16TEnemyMatTextureFv, 0x14, 8);
}
