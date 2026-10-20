#include "types.h"

// TObjWeight's DestroyWeightMatrix and SetWeightMatrix (the PS2 build's names;
// weightDestroyMatrix and weightSetMatrix here). Destroy frees the weight's
// matrix and forgets it; Set is the inline one of weight.inc.

#include "src/rel/weight.inc"

extern "C" void weightDestroyMatrix(Weight* object)
{
	if (object->matrix != NULL) {
		delete object->matrix;
		object->matrix = NULL;
	}
}

extern "C" void weightSetMatrix(Weight* object)
{
	SetWeightMatrix(object);
}
