#include "types.h"

// e2000ObjectGlobalArrayDtor, which rel/e2000_object_register.cpp registers as
// the destructor of e2000ObjectGlobalArray: it destroys the array's four
// texture sets.

extern "C" {
void __dt__16TEnemyMatTextureFv(void* texture, s16 flags);
void __destroy_arr(void* array, void* dtor, u32 size, u32 count);
}

extern "C" u8 e2000ObjectGlobalArray[];

extern "C" void e2000ObjectGlobalArrayDtor(void)
{
	__destroy_arr(e2000ObjectGlobalArray, (void*)__dt__16TEnemyMatTextureFv, 0x14, 4);
}
