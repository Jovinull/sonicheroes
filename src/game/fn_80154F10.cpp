// Appends a material to a material list (HYPOTHESIS: _rpMaterialListAppendMaterial): grows the
// pointer array by 20 entries when it is full (engine realloc, or malloc for an empty list;
// failure records error 0x80000013 with the size for plugin 2 and returns -1), stores the
// material, adds a reference to it and returns its index.
// NonMatching: the retail code computes the new size in r4 and copies it to r29; ours computes it
// in r29 (7 words differ).
#include "game/rw_engine.h"

struct Material80154F10 {
	u8 pad0[0x18];
	s16 refCount; // 0x18
};

// Material list (HYPOTHESIS: RpMaterialList).
struct MaterialList80154F10 {
	Material80154F10** materials; // 0x0
	s32 numMaterials;             // 0x4
	s32 space;                    // 0x8
};

static inline s32 MaterialListAdd(MaterialList80154F10* list, Material80154F10* material)
{
	list->materials[list->numMaterials] = material;
	material->refCount++;
	list->numMaterials++;
	return list->numMaterials - 1;
}

extern "C" {
s32 fn_80154F10(MaterialList80154F10* list, Material80154F10* material)
{
	Material80154F10** materials;
	u32 size;

	if (list->space > list->numMaterials) {
		return MaterialListAdd(list, material);
	}
	size = (list->space + 20) * sizeof(Material80154F10*);
	if (list->materials) {
		materials = (Material80154F10**)lbl_8042C9A4->rwrealloc(list->materials, size);
	} else {
		materials = (Material80154F10**)lbl_8042C9A4->rwmalloc(size);
	}
	if (!materials) {
		RwError error;
		error.pluginID  = 2;
		error.errorCode = fn_8019408C(RW_ERROR_NO_MEMORY, size);
		fn_80193FE8(&error);
		return -1;
	}
	list->materials = materials;
	list->space += 20;
	materials[list->numMaterials] = material;
	material->refCount++;
	list->numMaterials++;
	return list->numMaterials - 1;
}
}
