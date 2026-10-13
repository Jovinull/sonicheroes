#include "types.h"

// Updates the enemy's motion manager (the ENEMYMTNMAN at 0xB8).

extern "C" void UpdateMotion__11ENEMYMTNMANFv(void* motion);

extern "C" void fn_800A3D48(void* enemy)
{
	UpdateMotion__11ENEMYMTNMANFv((u8*)enemy + 0xB8);
}
