#include "game/memorycard_crypt.h"
#include "MSL_C/string.h"

// TDes::TDes(): clears the whole cipher state.

TDes::TDes()
{
	memset(mWork, 0, sizeof(mWork));
}
