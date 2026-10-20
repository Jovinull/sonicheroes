#include "types.h"

// The breakable weight's DestroyWeightMatrix and SetWeightMatrix (the PS2
// build's TObjWeightExt names; breakableWeightDestroyMatrix and
// breakableWeightSetMatrix here; the weight's own are rel/weight_matrix.cpp).
// Destroy frees the weight's matrix and forgets it; Set is the inline one of
// breakable_weight.inc.

#include "src/rel/breakable_weight.inc"

extern "C" void breakableWeightDestroyMatrix(BreakableWeight* object)
{
	if (object->matrix != NULL) {
		delete object->matrix;
		object->matrix = NULL;
	}
}

extern "C" void breakableWeightSetMatrix(BreakableWeight* object)
{
	SetWeightMatrix(object);
}
