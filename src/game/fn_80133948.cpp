// Starts a path camera on the current player's leader (HYPOTHESIS; names inferred): installs the
// camera context callback fn_80133B50, takes the camera path from the parameters (or the default
// lbl_802D59F0) into lbl_8042C7A0 and finds the leader's parameter t on it (fn_80133570, within
// lbl_8042EF78). Outside [lbl_8042EF68, lbl_8042EF60 - lbl_8042EF7C] it falls back to
// fn_801348D0; otherwise it aims at the leader, raised by the character's height, and places the
// eye lbl_8042EF78 back along the path direction at t (fn_8014D308), raised by lbl_8042EF80.
#include "game/object.h"

struct Team80133948 {
	u8 pad0[0x3C];
	s8 current; // 0x3C
	u8 pad3D[0x110 - 0x3D];
	s8 members[3]; // 0x110
};

struct Character80133948 {
	u8 pad0[0x18];
	RwV3d position; // 0x18
};

struct CharacterParam80133948 {
	u8 pad0[0x7C];
	f32 height; // 0x7C
	u8 pad80[0x84 - 0x80];
};

struct Path80133948 {
	void* points;  // 0x0
	void* normals; // 0x4
	void* spline;  // 0x8
	s32 unkC;      // 0xC
};

struct Params80133948 {
	u8 pad0[0x8];
	s32 hasPath; // 0x8
	u8 padC[0x14 - 0xC];
	Path80133948 path; // 0x14
};

struct Camera80133948 {
	s32 unk0;  // 0x0
	s32 unk4;  // 0x4
	s32 unk8;  // 0x8
	s32 unkC;  // 0xC
	RwV3d eye; // 0x10
	u8 pad1C[0x24 - 0x1C];
	s32 unk24; // 0x24
	u8 pad28[0x34 - 0x28];
	RwV3d target; // 0x34
};

struct Context80133948 {
	u8 pad0[0x58];
	void (*callback)(void); // 0x58
};

extern "C" {
extern s32 lbl_8042C1FC;
extern Team80133948* lbl_80303DC8[];
extern Character80133948* lbl_802AD090[];
extern CharacterParam80133948 lbl_80241560[];
extern Path80133948 lbl_802D59F0;
extern Path80133948* lbl_8042C7A0;
extern Context80133948* lbl_8042C1F8;
extern const f32 lbl_8042EF60;
extern const f32 lbl_8042EF68;
extern const f32 lbl_8042EF78;
extern const f32 lbl_8042EF7C;
extern const f32 lbl_8042EF80;
void fn_80133B50(void);
f32 fn_80133570(void* points, void* normals, RwV3d* position, f32 distance, RwV3d* point);
void fn_801348D0(Camera80133948* camera, Params80133948* params);
void fn_8014D308(void* spline, s32 kind, f32 t, RwV3d* point, s32 flags);
// HYPOTHESIS: RwV3dNormalize.
f32 fn_801990E0(RwV3d* out, const RwV3d* in);

void fn_80133948(Camera80133948* camera, Params80133948* params)
{
	RwV3d pathPoint;
	RwV3d point;
	RwV3d direction;
	Path80133948* path        = &params->path;
	Team80133948* team        = lbl_80303DC8[lbl_8042C1FC];
	s32 character             = team->members[team->current];
	Character80133948* leader = lbl_802AD090[character];
	f32 t;

	lbl_8042C1F8->callback = fn_80133B50;
	if (params->hasPath == 0) {
		*path = lbl_802D59F0;
	}
	lbl_8042C7A0 = path;
	t = fn_80133570(path->points, path->normals, &leader->position, lbl_8042EF78, &pathPoint);
	if (t < lbl_8042EF68 || lbl_8042EF7C + t > lbl_8042EF60) {
		fn_801348D0(camera, params);
		return;
	}
	camera->unk0   = 0;
	camera->unk4   = 0;
	camera->target = leader->position;
	camera->target.y += lbl_80241560[character].height;
	fn_8014D308(path->spline, 10, t, &point, 0);
	direction.x = point.x - pathPoint.x;
	direction.y = point.y - pathPoint.y;
	direction.z = point.z - pathPoint.z;
	fn_801990E0(&direction, &direction);
	direction.x   = lbl_8042EF78 * direction.x;
	direction.y   = lbl_8042EF78 * direction.y;
	direction.z   = lbl_8042EF78 * direction.z;
	camera->eye.x = camera->target.x - direction.x;
	camera->eye.y = camera->target.y - direction.y;
	camera->eye.z = camera->target.z - direction.z;
	camera->eye.y += lbl_8042EF80;
	camera->unk24 = 0;
	camera->unk8  = 0;
	camera->unkC  = 0;
}
}
