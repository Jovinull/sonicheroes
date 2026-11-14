// Empties a material list (HYPOTHESIS: _rpMaterialListDeinitialize): drops the list's reference to
// every material through fn_80154910 (RpMaterialDestroy), frees the array with the engine memory
// function and clears the count and capacity. Returns the list.
#include "game/rw_engine.h"

extern "C" {
s32 fn_80154910(RpMaterial* material);

RpMaterialList* fn_80154E54(RpMaterialList* list)
{
	RpMaterial** material;
	RpMaterial** materials;
	s32 count;
	s32 i;
	materials = list->materials;
	if (materials != 0) {
		count    = list->numMaterials;
		material = materials;
		for (i = 0; i < count; i++) {
			fn_80154910(*material);
			*material = 0;
			material++;
		}
		lbl_8042C9A4->rwfree(materials);
		list->materials = 0;
	}
	list->numMaterials = 0;
	list->space        = 0;
	return list;
}
}
