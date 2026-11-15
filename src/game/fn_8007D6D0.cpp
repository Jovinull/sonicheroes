#include "types.h"

typedef struct {
	f32 x, y, z;
} RwV3d;

typedef struct {
	u16 vertexIndexNo[3], neighbor[3];
	RwV3d norm;
	u32 attribute;
	u16 groupIndexNo;
	u8 dummy[2];
} POLYDATA;

extern "C" {
extern RwV3d lbl_80303DB8;
extern f32 lbl_8042D728;

bool fn_8007D6D0(POLYDATA* pData)
{
	f32 nz, nx, ny;

	if (pData->attribute & 0xC002)
		return 0;
	if ((pData->attribute & 0x80000) == 0)
		return 0;
	nz = pData->norm.z * lbl_80303DB8.z;
	nx = pData->norm.x * lbl_80303DB8.x;
	ny = pData->norm.y * lbl_80303DB8.y;
	return !(nz + (nx + ny) >= lbl_8042D728);
}
}
