#include "types.h"

// What stays here of stage11D's rinoliner collision run: the iron ball the
// rinoliner throws (TObjEnemyIronBall, by its class-name string), the
// collision strategy's mode handlers, and the data of TObjColliCommunication
// up to its vtable. That class's code is the shared
// rel/colli_communication_*.cpp and rel/rino_col_register.cpp units.
//
// The 8-byte fn_8_B49D8 in front of this unit is not its code: it is the
// compiler-generated this-adjusting thunk (-0xB0) for the rinoliner's
// fn_8_B43E8, emitted at the end of the rinoliner's own translation unit.
//
// The vtables are written out as arrays because retail keeps their address
// names; they hold the same entries MWCC would emit for the classes.

typedef s32 M2C_UNK;

#define M2C_FIELD(base, type, offset) (*(type)((u8*)(u32)(base) + (offset)))
#define M2C_ERROR(...)
#define M2C_BITWISE(type, value) (*(type*)&(value))

struct Vec3 {
	f32 x;
	f32 y;
	f32 z;

	void operator*=(const f32& s)
	{
		x *= s;
		y *= s;
		z *= s;
	}
	void operator+=(const Vec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}
};

struct sAngle {
	s32 x;
	s32 y;
	s32 z;
};

struct Sphere {
	Vec3 center;
	f32 radius;
};

struct TObject {
	/* 0x00 */ char* className;
	/* 0x04 */ u16 signal;
	/* 0x06 */ u8 pad06[0x12];
	/* 0x18 */ void** vtable;
	/* 0x1C */ s16 pad1C;
	/* 0x1E */ s16 objectSize;
	/* 0x20 */ u8 pad20[8];
};

struct C_COLLI {
	/* 0x00 */ u8 pad00[8];
	/* 0x08 */ u16 flags;
	/* 0x0A */ u8 pad0A[6];
	/* 0x10 */ void* info;
	/* 0x14 */ u8 pad14[0x4C];
	/* 0x60 */ Vec3 pos;
	/* 0x6C */ sAngle angle;
	/* 0x78 */ u8 pad78[4];
	/* 0x7C */ Vec3 oldPos;
};

/* The editor parameters the iron ball is created from. */
struct IronBallParam {
	/* 0x00 */ Vec3 pos;
	/* 0x0C */ Vec3 dir;
	/* 0x18 */ f32 speed;
	/* 0x1C */ sAngle angle;
	/* 0x28 */ s32 life;
	/* 0x2C */ s32 homing;
	/* 0x30 */ s32 light;
};

/* TObjEnemyIronBall, named by its class-name string. Field names are
 * descriptive guesses. */
struct IronBall : TObject {
	/* 0x28 */ C_COLLI colli;
	/* 0xB0 */ IronBallParam param;
	/* 0xE4 */ s32 state;
	/* 0xE8 */ Vec3 rot;
};

/* A player character: its position at +0x18. */
struct PlayerObj {
	u8 pad00[0x18];
	Vec3 pos;
};

/* The game state lbl_8029C310 points into: the mode at +0x18. */
struct GameState {
	u8 pad00[0x18];
	s32 mode;
};

/* The pause/event flags lbl_8042C180 points at. */
struct GameFlags {
	u8 pad00[0x1F];
	s8 flag1F;
	s8 flag20;
	s8 flag21;
};

/* Dispatch view of the object's vtable. The handler at vtable offset 0x10 is
 * reached through genuine virtual dispatch in retail: the target loads the
 * vtable through the already-materialised `this` in r3 and keeps the slot in
 * r12, which manual vtable indexing does not reproduce. Two implicit
 * destructor slots plus the two placeholders below put Release at slot 4. */
class TObjectDispatch
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void Release(s32, s32);
	virtual s32 vslot5();
};

/* Dispatch view of the object handed to the state jumptable: retail reads the
 * vtable through the incoming `this` in r3 and calls the slot with the state
 * argument in r4, so the call has to go through a class. Slot numbers are the
 * retail vtable offsets, and the two implicit destructor slots occupy 0 and 4. */
class TStateDispatch
{
public:
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void Slot18(s32);
	virtual void Slot1C(s32);
	virtual void Slot20(s32);
	virtual void Slot24(s32);
	virtual void Slot28(s32);
	virtual void Slot2C(s32);
	virtual void Slot30(s32);
};

extern "C" {

void* __ct__7TObjectFP7TObject(TObject* self, TObject* parent);
M2C_UNK __dl__FPv(void* arg0);
void* __dt__7TObjectFv(TObject* self, s16 destroyFlag);
M2C_UNK __dt__7C_COLLIFv(C_COLLI*, M2C_UNK);
s32 fn_80017800(void*);
M2C_UNK Free__9THeapCtrlFPv(s32, void*);
void* Malloc__9THeapCtrlFUi(s32, u32);
M2C_UNK Entry__7C_COLLIFv(C_COLLI*);
M2C_UNK ClearInfo__7C_COLLIFv(C_COLLI*);
M2C_UNK Init__7C_COLLIFP8CCL_INFOiUc(C_COLLI*, void*, s32, u8);
M2C_UNK __ct__7C_COLLIFv(C_COLLI*);
void* objPointerReadFromClumpAnim__FPc(const char*);
M2C_UNK fn_800A31B8(void*, s32);
s32 fn_800A3ED4(void*);
M2C_UNK AdjustPoint__FP5RwV3dPC5RwV3df(Vec3*, Vec3*, f32);
f32 Distance2P2P__FPC5RwV3dPC5RwV3d(Vec3*, Vec3*);
s32 GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(Vec3*, f32);
M2C_UNK SetLightNum__7nRenderFUi(s32);
M2C_UNK fn_8014FF2C(void*);
M2C_UNK fn_801990E0(Vec3*, Vec3*);
s32 fn_8019CE34(s32, Sphere*);
M2C_UNK fn_8019EB94(void*, Vec3*, M2C_UNK);
M2C_UNK fn_8019ED68(void*, M2C_UNK*, f32, s32);
s32 fn_8_B0A74(void*);
extern GameState lbl_8029C310;
extern PlayerObj* lbl_802AD090[];
extern M2C_UNK AxisX;
extern M2C_UNK AxisY;
extern M2C_UNK AxisZ;
extern TObject* lbl_8042C10C;
extern s32 lbl_8042C148;
extern GameFlags* lbl_8042C180;
extern s32* lbl_8042C9A4;

void TDisp__7TObjectFv();
void PDisp__7TObjectFv();
void Disp__7TObjectFv();
void ImmAftSetRaster__7TObjectFv();
void Debug__7TObjectFv();
void Error__7TObjectFPc();
void Render__7TObjectFv();
void __dt__22TObjColliCommunicationFv();
void Exec__22TObjColliCommunicationFv();
void TDisp__22TObjColliCommunicationFv();
void EditOnChange__22TObjColliCommunicationFP13SETDATA_PARAM();
void fn_8_B7210();

void fn_8_B49E4(void* arg0, u32 arg1);
void fn_8_B4A7C(IronBall* self);
void fn_8_B4DB0(IronBall* self);
IronBall* fn_8_B4F70(IronBall* self, s16 flags);
void fn_8_B533C(void* arg0, s32 arg1);
void fn_8_B5408(void* arg0, s32 arg1);
void fn_8_B5428(void* arg0, s32 arg1);
void fn_8_B54E4(void* arg0, s32 arg1);
void fn_8_B5504(void* arg0, s32 arg1);
void fn_8_B55C0(void* arg0, s32 arg1);
void fn_8_B55E0(void* arg0, s32 arg1);
void fn_8_B5600(void* arg0, s32 arg1);
s32 fn_8_B5694(void* arg0);
void fn_8_B59F8(void** arg0, u32 arg1, s32 arg2);
M2C_UNK** fn_8_B5AD8(M2C_UNK** arg0, s16 arg1);
M2C_UNK** fn_8_B5B74(M2C_UNK** arg0, s16 arg1);
M2C_UNK** fn_8_B5BE8(M2C_UNK** arg0, s16 arg1);

/* The iron ball's collision setup. */
u32 lbl_8_data_16FD8[12] = { 0x17009022, 0x00080000, 0x00000000, 0x00000000, 0x00000000, 0x41000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
char lbl_8_data_17008[]  = "TObjEnemyIronBall";
char* lbl_8_data_1701C   = lbl_8_data_17008;

/* TObjEnemyIronBall's vtable: destructor, Exec, Disp, then TObject's. */
void* lbl_8_data_17020[11] = {
	0,
	0,
	(void*)fn_8_B4F70,
	(void*)fn_8_B4DB0,
	(void*)fn_8_B4A7C,
	(void*)TDisp__7TObjectFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
};

/* Retail starts the next vtable on an 8-byte boundary, the alignment MWCC gives
 * the class vtables these arrays stand in for; the name buffer's zero tail
 * reproduces that gap. */
char lbl_8_data_1704C[0x14] = "OBJ_SPIKEB.DFF";

/* The collision strategy's vtables, most derived first: the mode
 * dispatcher, the change-request check and the seven mode handlers. */
void* lbl_8_data_17060[13] = {
	0,
	0,
	(void*)fn_8_B5B74,
	(void*)fn_8_B49E4,
	(void*)fn_8_B59F8,
	(void*)fn_8_B5694,
	(void*)fn_8_B5600,
	(void*)fn_8_B55E0,
	(void*)fn_8_B533C,
	(void*)fn_8_B5504,
	(void*)fn_8_B54E4,
	(void*)fn_8_B5428,
	(void*)fn_8_B5408,
};

extern void* lbl_8_data_170B0[6];
extern void* lbl_8_data_170C8[14];

/* The iron ball model, read by the load hook. */
struct {
	void* p;
	void* unk4;
} lbl_8_bss_1A90;

/* The editor record the TObjColliCommunication register hook fills. */
typedef struct ObjectEntry {
	const char* name;        /* 0x00 */
	void (*load)(void);      /* 0x04 */
	void (*unload)(void);    /* 0x08 */
	void (*create)(void);    /* 0x0C */
	void* unk10;             /* 0x10 */
	u32 flags;               /* 0x14 */
	u32 unk18;               /* 0x18 */
	s16 unk1C;               /* 0x1C */
	s16 unk1E;               /* 0x1E */
	u8 unk20;                /* 0x20 */
	u8 unk21;                /* 0x21 */
	u8 pad22[2];             /* 0x22 */
	const char* fieldTypes;  /* 0x24 */
	const char** fieldNames; /* 0x28 */
	u8 pad2C[4];             /* 0x2C */
} ObjectEntry;               /* 0x30 */

ObjectEntry rinoColObjectEntry;

/* The unreferenced { 0, 1.5, 0 } vector every Stage 11 object unit carries at
 * the head of its .rodata, the way an internal-linkage const from a shared
 * header lands in each translation unit that includes it. */
#pragma force_active on
static const Vec3 lbl_8_rodata_1C58 = { 0.0f, 1.5f, 0.0f };
#pragma force_active reset

extern const f32 lbl_8_rodata_1C64[3] = { 0.0f, 2.0f, 0.0f };
extern const f32 lbl_8_rodata_1C70[1] = { 20.0f };
extern const f32 lbl_8_rodata_1C74[1] = { 100000000.0f };
extern const f32 lbl_8_rodata_1C78[1] = { 2500.0f };
extern const f32 lbl_8_rodata_1C7C[1] = { 0.0f };
extern const f32 lbl_8_rodata_1C80[1] = { 0.05000000074505806f };

void fn_8_B49E0(void) { }

void fn_8_B49E4(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	M2C_FIELD(arg0, s32*, 0x10) = 0;
	if (((TObjectDispatch*)arg0)->vslot5() != 0) {
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 2);
	}
	((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 1);
	if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
		fn_800A31B8((void*)M2C_FIELD(arg0, u32*, 0x14), M2C_FIELD(arg0, s32*, 0x10));
	}
}

void fn_8_B4A7C(IronBall* self)
{
	Sphere sphere;
	void* frame;

	if (lbl_8_bss_1A90.p != NULL) {
		sphere.center = self->param.pos;
		sphere.radius = lbl_8_rodata_1C70[0];
		if (fn_8019CE34(*lbl_8042C9A4, &sphere) != 0) {
			frame = *(void**)((u8*)lbl_8_bss_1A90.p + 4);
			fn_8019ED68(frame, &AxisZ, self->rot.z, 0);
			fn_8019ED68(frame, &AxisX, self->rot.x, 2);
			fn_8019ED68(frame, &AxisY, self->rot.y, 2);
			fn_8019EB94(frame, &self->param.pos, 2);
			SetLightNum__7nRenderFUi(self->param.light);
			fn_8014FF2C(lbl_8_bss_1A90.p);
		}
	}
}

void fn_8_B4B88(IronBall* self)
{
	self->signal |= 1;
}

/* RenderWare's RwV3dDotProductMacro. */
#define RwV3dDotProduct(a, b) ((((a)->x * (b)->x) + ((a)->y * (b)->y)) + ((a)->z * (b)->z))

// Retail calls the movement step out of line from Exec.
#pragma auto_inline off
void fn_8_B4B9C(IronBall* self)
{
	Vec3 dir;
	s32 leader;
	PlayerObj* player;
	f32 y;

	if (--self->param.life < 0) {
		self->state = 2;
		return;
	}
	if (self->param.homing != 0) {
		leader = GetNearestLeaderNum__13nSearchPlayerFPC5RwV3df(
		    &self->param.pos, lbl_8_rodata_1C74[0]);
		if (leader != -1) {
			player = lbl_802AD090[leader];
			if (player != NULL) {
				if (Distance2P2P__FPC5RwV3dPC5RwV3d(&self->param.pos, &player->pos)
				    < lbl_8_rodata_1C78[0]) {
					self->param.homing = 0;
				}
				dir.x = player->pos.x - self->param.pos.x;
				dir.y = player->pos.y - self->param.pos.y;
				dir.z = player->pos.z - self->param.pos.z;
				fn_801990E0(&dir, &dir);
				if (RwV3dDotProduct(&self->param.dir, &dir) > lbl_8_rodata_1C7C[0]) {
					y = self->param.dir.y;
					AdjustPoint__FP5RwV3dPC5RwV3df(&self->param.dir, &dir, lbl_8_rodata_1C80[0]);
					self->param.dir.y = y;
				} else {
					self->param.homing = 0;
				}
			}
		}
	}
	{
		Vec3 move = self->param.dir;
		move *= self->param.speed;
		self->param.pos += move;
	}
	self->rot.x += lbl_8_rodata_1C64[0];
	self->rot.y += lbl_8_rodata_1C64[1];
	self->rot.z += lbl_8_rodata_1C64[2];
}

#pragma auto_inline reset

void fn_8_B4DA4(IronBall* self)
{
	self->state = 1;
}

/* Whether the stage is ending: game modes 1 and 2, or 3. */
inline u32 GameModeIsClear(s32 mode)
{
	return (u32)(mode - 1) <= 1;
}

inline BOOL GameModeEnds()
{
	u8 clear;
	u8 ends;
	s32 mode = lbl_8029C310.mode;

	ends  = 1;
	clear = 1;
	if (!GameModeIsClear(mode)) {
		clear = 0;
	}
	if (!clear && mode != 3) {
		ends = 0;
	}
	return ends;
}

/* Whether no pause or event flag is up. */
inline s32 GameRunning()
{
	if (lbl_8042C180->flag1F != 0) {
		return 0;
	} else if (lbl_8042C180->flag20 != 0) {
		return 0;
	} else if (lbl_8042C180->flag21 != 0) {
		return 0;
	}
	return 1;
}

void fn_8_B4DB0(IronBall* self)
{
	if (GameModeEnds()) {
		self->signal |= 1;
		return;
	}
	if (!GameRunning()) {
		ClearInfo__7C_COLLIFv(&self->colli);
		return;
	}
	switch (self->state) {
		case 0:
			self->state = 1;
			break;
		case 1:
			fn_8_B4B9C(self);
			break;
		case 2:
			self->signal |= 1;
			break;
	}
	if (fn_80017800(self) != 0 && self->colli.info != NULL) {
		self->colli.oldPos = self->colli.pos;
		self->colli.pos    = self->param.pos;
		self->colli.angle  = self->param.angle;
		Entry__7C_COLLIFv(&self->colli);
	}
}

IronBall* fn_8_B4F70(IronBall* self, s16 flags)
{
	if (self != NULL) {
		self->vtable = lbl_8_data_17020;
		__dt__7C_COLLIFv(&self->colli, 0);
		__dt__7TObjectFv(self, 0);
		if (flags > 0) {
			Free__9THeapCtrlFPv(lbl_8042C148, self);
		}
	}
	return self;
}

IronBall* fn_8_B4FF4(IronBall* self, TObject* parent, IronBallParam* param)
{
	__ct__7TObjectFP7TObject(self, parent);
	__ct__7C_COLLIFv(&self->colli);
	self->vtable      = lbl_8_data_17020;
	self->param.pos.x = self->param.pos.y = self->param.pos.z = lbl_8_rodata_1C7C[0];
	self->param.dir.x = self->param.dir.y = self->param.dir.z = lbl_8_rodata_1C7C[0];
	self->param.angle.x = self->param.angle.y = self->param.angle.z = 0;
	self->param.life                                                = 300;
	self->param.homing                                              = 1;
	self->param.light                                               = 8;
	self->className                                                 = lbl_8_data_1701C;
	self->objectSize                                                = sizeof(IronBall);
	self->state                                                     = 0;
	self->param                                                     = *param;
	self->rot.x = self->rot.y = self->rot.z = lbl_8_rodata_1C7C[0];
	Init__7C_COLLIFP8CCL_INFOiUc(&self->colli, lbl_8_data_16FD8, 1, 3);
	self->colli.pos = self->param.pos;
	self->colli.flags &= ~0x40;
	return self;
}

/* The create hook's allocation is a placement new-expression; see
 * IronBallStorage. */
struct ObjectStorage {
	~ObjectStorage();
};

struct IronBallStorage : ObjectStorage {
	u8 data[sizeof(IronBall)];

	IronBallStorage(IronBallParam* param) { fn_8_B4FF4((IronBall*)this, lbl_8042C10C, param); }
	static void* operator new(unsigned long size, s32 heap)
	{
		return Malloc__9THeapCtrlFUi(heap, size);
	}
};

void fn_8_B5160(IronBallParam* param)
{
	new (lbl_8042C148) IronBallStorage(param);
}

void fn_8_B52F4(void)
{
	lbl_8_bss_1A90.p = NULL;
}

void fn_8_B5308(void)
{
	lbl_8_bss_1A90.p = objPointerReadFromClumpAnim__FPc(lbl_8_data_1704C);
}

void fn_8_B533C(void* arg0, s32 arg1)
{
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18)
			    = (s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x2B0);
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			break;
		case 1:
			if (fn_8_B0A74(M2C_FIELD(arg0, void**, 0x14)) != 0) {
				temp_r0                     = M2C_FIELD(arg0, s32*, 0x18) - 1;
				M2C_FIELD(arg0, s32*, 0x18) = temp_r0;
				if (temp_r0 < 0) {
					M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
					M2C_FIELD(arg0, s32*, 4) = 2;
					((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				}
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B5408(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x1D;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_B5428(void* arg0, s32 arg1)
{
	s32 temp_r31;
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x1C) = 0xF0;
			M2C_FIELD(arg0, s32*, 0x10) = 0x24;
			break;
		case 1:
			temp_r0                     = M2C_FIELD(arg0, s32*, 0x1C) - 1;
			M2C_FIELD(arg0, s32*, 0x1C) = temp_r0;
			if (temp_r0 < 0) {
				temp_r31                 = M2C_FIELD(arg0, s32*, 8);
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = temp_r31;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B54E4(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x26;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_B5504(void* arg0, s32 arg1)
{
	s32 temp_r31;
	s32 temp_r0;

	switch (arg1) { /* irregular */
		case 0:
			M2C_FIELD(arg0, s32*, 0x18) = 1;
			M2C_FIELD(arg0, s32*, 0x10) = 0x20;
			break;
		case 1:
			temp_r0                     = M2C_FIELD(arg0, s32*, 0x18) - 1;
			M2C_FIELD(arg0, s32*, 0x18) = temp_r0;
			if (temp_r0 < 0) {
				temp_r31                 = M2C_FIELD(arg0, s32*, 8);
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = temp_r31;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			}
			break;
		case 2:
		case 3:
			break;
	}
}

void fn_8_B55C0(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 2;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_B55E0(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 0x27;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_B5600(void* arg0, s32 arg1)
{
	switch (arg1) {
		case 0:
			M2C_FIELD(arg0, s32*, 0x10) = 1;
			break;
		case 1:
		case 2:
		case 3:
			break;
	}
}

void fn_8_B5620(void* arg0, u32 arg1)
{
	M2C_FIELD(arg0, u32*, 0x14) = arg1;
	if ((u32)M2C_FIELD(arg0, u32*, 0x14) != 0U) {
		M2C_FIELD(arg0, s32*, 0xC)  = 0;
		M2C_FIELD(arg0, s32*, 0x10) = 0;
		M2C_FIELD(arg0, s32*, 4)    = 0;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		if ((s32)M2C_FIELD(arg0, s32*, 0x10) != 0) {
			fn_800A31B8((void*)M2C_FIELD(arg0, u32*, 0x14), M2C_FIELD(arg0, s32*, 0x10));
		}
	}
}

s32 fn_8_B5694(void* arg0)
{
	s32 var_r3;
	void* temp_r3;
	s32 temp_r0;
	s32 temp_r0_2;

	if ((fn_800A3ED4(M2C_FIELD(arg0, void**, 0x14)) != 0)
	    && ((s32)M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x19C) != 0x1D)) {
		M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
		M2C_FIELD(arg0, s32*, 4) = 6;
		((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
		return 1;
	}
	temp_r3 = M2C_FIELD(arg0, void**, 0x14);
	temp_r0 = M2C_FIELD(temp_r3, s32*, 0x240);
	if (temp_r0 != 0) {
		var_r3 = 0;
		switch (temp_r0) { /* irregular */
			case 1:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 0;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 2:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 1;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 38:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 3;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 29:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 6;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 39:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 4;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
			case 32:
				M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
				M2C_FIELD(arg0, s32*, 4) = 2;
				((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
				var_r3 = 1;
				break;
		}
		M2C_FIELD(M2C_FIELD(arg0, void**, 0x14), s32*, 0x240) = 0;
		return var_r3;
	}
	if ((u32)(M2C_FIELD(temp_r3, s32*, 0x18C) & 0x2000) != 0) {
		temp_r0_2 = M2C_FIELD(temp_r3, s32*, 0x19C);
		switch (temp_r0_2) {
			case 1:
			case 2:
				break;
			default:
				goto block_28;
		}
		{
			M2C_FIELD(arg0, s32*, 8) = (s32)M2C_FIELD(arg0, s32*, 4);
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 3);
			M2C_FIELD(arg0, s32*, 4) = 5;
			((TObjectDispatch*)arg0)->Release((s32)M2C_FIELD(arg0, s32*, 4), 0);
			return 1;
		}
	block_28:
		return 0;
	}
	return 0;
}

void fn_8_B59F8(void** arg0, u32 arg1, s32 arg2)
{
	switch (arg1) {
		case 0:
			((TStateDispatch*)arg0)->Slot18(arg2);
			return;
		case 4:
			((TStateDispatch*)arg0)->Slot1C(arg2);
			return;
		case 1:
			((TStateDispatch*)arg0)->Slot20(arg2);
			return;
		case 3:
			((TStateDispatch*)arg0)->Slot28(arg2);
			return;
		case 2:
			((TStateDispatch*)arg0)->Slot24(arg2);
			return;
		case 5:
			((TStateDispatch*)arg0)->Slot2C(arg2);
			return;
		case 6:
			((TStateDispatch*)arg0)->Slot30(arg2);
			/* fallthrough */
		default:
			return;
	}
}

/* The base strategy's vtable keeps only the destructor and slot 3. */
void* lbl_8_data_170B0[6] = {
	0,
	0,
	(void*)fn_8_B5BE8,
	(void*)fn_8_B49E4,
	0,
	0,
};

void* lbl_8_data_170C8[14] = {
	0,
	0,
	(void*)fn_8_B5AD8,
	(void*)fn_8_B49E4,
	(void*)fn_8_B59F8,
	(void*)fn_8_B5694,
	(void*)fn_8_B5600,
	(void*)fn_8_B55E0,
	(void*)fn_8_B55C0,
	(void*)fn_8_B5504,
	(void*)fn_8_B54E4,
	(void*)fn_8_B5428,
	(void*)fn_8_B5408,
	0,
};

/* The base classes' destructors, inlined into the derived ones. */
static inline void DestroyStrategyBase(M2C_UNK** self)
{
	if (self != NULL) {
		*self = (M2C_UNK*)lbl_8_data_170B0;
	}
}

static inline void DestroyStrategyMid(M2C_UNK** self)
{
	if (self != NULL) {
		*self = (M2C_UNK*)lbl_8_data_170C8;
		DestroyStrategyBase(self);
	}
}

M2C_UNK** fn_8_B5AD8(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_170C8;
		DestroyStrategyBase(arg0);
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

void fn_8_B5B3C(void* arg0)
{
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_170B0;
	M2C_FIELD(arg0, s32*, 4)      = 0;
	M2C_FIELD(arg0, s32*, 8)      = 0;
	M2C_FIELD(arg0, s32*, 0xC)    = 0;
	M2C_FIELD(arg0, s32*, 0x14)   = 0;
	M2C_FIELD(arg0, s32*, 0x10)   = 0;
	M2C_FIELD(arg0, M2C_UNK**, 0) = (M2C_UNK*)lbl_8_data_170C8;
	M2C_FIELD(arg0, s32*, 0x18)   = 0;
}

M2C_UNK** fn_8_B5B74(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_17060;
		DestroyStrategyMid(arg0);
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

M2C_UNK** fn_8_B5BE8(M2C_UNK** arg0, s16 arg1)
{
	if (arg0 != NULL) {
		*arg0 = (M2C_UNK*)lbl_8_data_170B0;
		if (arg1 > 0) {
			__dl__FPv(arg0);
		}
	}
	return arg0;
}

/* TObjColliCommunication's data. Its code is the shared
 * rel/colli_communication_*.cpp units; the data stays with this run. */
u32 colliCommunicationCclInfo[12] = { 0x0000F000, 0x00708000, 0x00000000, 0x00000000, 0x00000000,
	0x41200000, 0x41200000, 0x41200000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

char lbl_8_data_17130[] = "COLLI TYPE";
char lbl_8_data_1713C[] = "SPEED CTRL";
char lbl_8_data_17148[] = "Not in use";
char lbl_8_data_17154[] = "RADIUS";
char lbl_8_data_1715C[] = "TARGET X";
char lbl_8_data_17168[] = "TARGET Y";
char lbl_8_data_17174[] = "TARGET Z";

char* rinoColObjectFieldNames[8] = {
	lbl_8_data_17130,
	lbl_8_data_1713C,
	lbl_8_data_17148,
	lbl_8_data_17148,
	lbl_8_data_17154,
	lbl_8_data_1715C,
	lbl_8_data_17168,
	lbl_8_data_17174,
};

char lbl_8_data_171A0[] = "START";
char lbl_8_data_171A8[] = "END";
char lbl_8_data_171AC[] = "CHANGE PATH";
char lbl_8_data_171B8[] = "CHANGE PATH SET";
char lbl_8_data_171C8[] = "ATTACK";
char lbl_8_data_171D0[] = "ATTACK SET";

char* rinoColKindNames[7] = {
	lbl_8_data_171A0,
	lbl_8_data_171A8,
	lbl_8_data_171AC,
	lbl_8_data_171B8,
	lbl_8_data_171C8,
	lbl_8_data_171D0,
	lbl_8_data_1713C,
};

char lbl_8_data_171F8[] = "ENABLE";
char lbl_8_data_17200[] = "DISABLE";
char lbl_8_data_17208[] = "DISABLE MIN";
char lbl_8_data_17214[] = "DISABLE STANDARD";
char lbl_8_data_17228[] = "DISABLE MAX";

char* rinoColActionNames[5] = {
	lbl_8_data_171F8,
	lbl_8_data_17200,
	lbl_8_data_17208,
	lbl_8_data_17214,
	lbl_8_data_17228,
};

#pragma explicit_zero_data on
u8 rinoColKindMin = 0;
#pragma explicit_zero_data reset
u8 rinoColKindMax = 6;
#pragma explicit_zero_data on
u8 rinoColActionMin = 0;
#pragma explicit_zero_data reset
u8 rinoColActionMax = 4;

char lbl_8_data_1724C[]         = "TObjColliCommunication";
char* CL_TObjColliCommunication = lbl_8_data_1724C;

void* __vt__22TObjColliCommunication[15] = {
	0,
	0,
	(void*)__dt__22TObjColliCommunicationFv,
	(void*)Exec__22TObjColliCommunicationFv,
	(void*)Disp__7TObjectFv,
	(void*)TDisp__22TObjColliCommunicationFv,
	(void*)PDisp__7TObjectFv,
	(void*)ImmAftSetRaster__7TObjectFv,
	(void*)Debug__7TObjectFv,
	(void*)Error__7TObjectFPc,
	(void*)Render__7TObjectFv,
	0,
	0,
	(void*)fn_8_B7210,
	(void*)EditOnChange__22TObjColliCommunicationFP13SETDATA_PARAM,
};
}
