// Probe step (HYPOTHESIS; the owner and roles are UNKNOWN): runs fn_8004D9B8 and fn_800516E4 on
// lbl_8042C1F8 around fn_80018C4C and fn_80135C30, installs fn_80130F74 as its callback (0x58),
// records the probe segment (0x10 to 0x34) and the constant lbl_8042EEA8 in lbl_803EA4B8, casts
// the segment against the collision octree lbl_8042C150 (DetectLineCollisionWithPolygons, hit
// point and polygon into lbl_803EA4B8) and clears the probe's words 0x8 and 0xC.
#include "game/octree.h"

struct Hit80130E70 {
	RwV3d from;     // 0x00
	RwV3d to;       // 0x0C
	RwV3d point;    // 0x18
	POLYDATA* poly; // 0x24
	f32 f28;        // 0x28
	u8 pad2C[0x30 - 0x2C];
};

struct Probe80130E70 {
	u8 pad0[0x8];
	s32 f8;     // 0x08
	s32 fC;     // 0x0C
	RwV3d from; // 0x10
	u8 pad1C[0x34 - 0x1C];
	RwV3d to; // 0x34
};

struct Camera80130E70 {
	u8 pad0[0x58];
	void (*callback)(void); // 0x58
};

extern "C" {
extern Camera80130E70* lbl_8042C1F8;
extern OCTREE* lbl_8042C150;
extern Hit80130E70 lbl_803EA4B8;
extern f32 lbl_8042EEA8;
void fn_8004D9B8(Camera80130E70* camera);
void fn_80018C4C(void);
void fn_80135C30(Probe80130E70* probe, s32 arg);
void fn_800516E4(Camera80130E70* camera);
void fn_80130F74(void);

void fn_80130E70(Probe80130E70* probe, s32 arg)
{
	RwV3d dir;

	fn_8004D9B8(lbl_8042C1F8);
	fn_80018C4C();
	fn_80135C30(probe, arg);
	fn_800516E4(lbl_8042C1F8);
	dir.x                  = probe->to.x - probe->from.x;
	dir.y                  = probe->to.y - probe->from.y;
	dir.z                  = probe->to.z - probe->from.z;
	lbl_8042C1F8->callback = fn_80130F74;
	lbl_803EA4B8.from.x    = probe->from.x;
	lbl_803EA4B8.from.y    = probe->from.y;
	lbl_803EA4B8.from.z    = probe->from.z;
	lbl_803EA4B8.to.x      = probe->to.x;
	lbl_803EA4B8.to.y      = probe->to.y;
	lbl_803EA4B8.to.z      = probe->to.z;
	lbl_803EA4B8.f28       = lbl_8042EEA8;
	lbl_803EA4B8.poly      = lbl_8042C150->DetectLineCollisionWithPolygons(
	    &probe->from, &dir, &lbl_803EA4B8.point, NULL);
	probe->f8 = 0;
	probe->fC = 0;
}
}
