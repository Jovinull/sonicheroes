// Vector module shutdown (HYPOTHESIS: _rwVectorClose): frees the reciprocal square-root and square
// root tables with the engine memory function, clears them and drops the instance count. Returns
// the instance.
#include "game/rw_engine.h"

extern "C" {
void* fn_801994D4(void* instance)
{
	if (RW_INV_SQRT_TABLE != 0) {
		lbl_8042C9A4->rwfree(RW_INV_SQRT_TABLE);
		RW_INV_SQRT_TABLE = 0;
	}
	if (RW_SQRT_TABLE != 0) {
		lbl_8042C9A4->rwfree(RW_SQRT_TABLE);
		RW_SQRT_TABLE = 0;
	}
	lbl_8042C990.numInstances--;
	return instance;
}
}
