// ENEMY_SHOT (the PS2 build's name): the enemies' shot object, with its
// constructor and Init. Create and SetEnemyShot inline both;
// rel/enemy_shot_ctor.cpp has the out-of-line copies (ENEMY_SHOT_INLINE empty).

#ifndef ENEMY_SHOT_INLINE
#define ENEMY_SHOT_INLINE inline
#endif

class ENEMY_SHOT : public TObject, public OBJ_MoveOnGround, public C_COLLI
{
public:
	ENEMY_SHOT(TObject* parent);
	virtual ~ENEMY_SHOT();

	static int Create(u16& id, int kind, RwV3d* vel, RwV3d* pos);
	void SetFlagToCheckGround() { flags |= 1; }
	void ClearFlagToCheckGround() { flags &= ~1; }
	void Init(const RwV3d* pos, const RwV3d* vel);

	// OBJ_MoveOnGround at 0x028, C_COLLI at 0x060
	s32 done;   // 0x0E8
	s16 hits;   // 0x0EC
	RwV3d pos;  // 0x0F0
	RwV3d vel;  // 0x0FC
	s32 angX;   // 0x108
	s32 angY;   // 0x10C
	s32 timer;  // 0x110
	f32 size;   // 0x114
	f32 scaleX; // 0x118
	f32 scaleY; // 0x11C
	f32 scaleZ; // 0x120
	u16 flags;  // 0x124
};

extern "C" TObject* lbl_8042C2A0;
extern "C" TObject* lbl_8042C114;
extern "C" TObject* lbl_8042C10C;
extern "C" u16 enemyShotCount;
extern "C" void* lbl_8042C388;
extern "C" char* CL_EnemyShot;
extern "C" CCL_INFO enemyShotCclInfo[];
extern "C" const f32 enemyShotSize[1];
extern "C" const f32 enemyShotOne[1];
extern "C" const f32 enemyShotRangePad[1];
extern "C" const f32 enemyShotRadToAngle[1];

extern "C" f32 fn_801991B4(RwV3d* v);
extern "C" void fn_800B4A38(
    void* sound, u16 id, RwV3d* pos, void* object, s32 kind, s32 arg5, s32 range);
extern "C" double asin(double x);
extern "C" double atan2(double y, double x);

ENEMY_SHOT_INLINE ENEMY_SHOT::ENEMY_SHOT(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_EnemyShot;
	DispTime  = sizeof(ENEMY_SHOT);
	hits      = 0;
	done      = 0;
	C_COLLI::Init(enemyShotCclInfo, 1, 3);
	flag &= ~0x40;
	size      = enemyShotSize[0];
	scaleX    = enemyShotOne[0];
	scaleY    = enemyShotOne[0];
	scaleZ    = enemyShotOne[0];
	radObject = enemyShotOne[0];
}

ENEMY_SHOT_INLINE void ENEMY_SHOT::Init(const RwV3d* pos, const RwV3d* vel)
{
	this->pos.x = pos->x;
	this->pos.y = pos->y;
	this->pos.z = pos->z;
	this->vel.x = vel->x;
	this->vel.y = vel->y;
	this->vel.z = vel->z;
	this->SetRange(enemyShotRangePad[0] + fn_801991B4((RwV3d*)vel));
	this->angX        = enemyShotRadToAngle[0] * (f32)asin(-this->vel.y / fn_801991B4(&this->vel));
	this->angY        = enemyShotRadToAngle[0] * (f32)atan2(this->vel.x, this->vel.z);
	this->timer       = 0;
	this->posCenter.x = this->pos.x;
	this->posCenter.y = this->pos.y;
	this->posCenter.z = this->pos.z;
}
