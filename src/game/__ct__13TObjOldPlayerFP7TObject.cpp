// TObjOldPlayer::TObjOldPlayer(TObject*), the player object's constructor (the mangled name is
// CORROBORATED by the PS2 build: it references TObject's and C_COLLI's constructors, the
// TObjOldPlayer vtable, PLAYERWK's constructor and memset, as this one does). Builds the TObject
// base, the C_COLLI base at +0x28 and the PLAYERWK member at +0x760, clears the task and motion
// work (+0x6F0, +0x720) and initialises the state fields; the scale (+0x714..+0x71C) is set to
// 1.0f.
// It is written as a real constructor because the retail exception table destroys the TObject and
// C_COLLI bases and the PLAYERWK member on unwind. The class has virtual bases: the compiler passes
// the hidden flag in r4 and fills their pointer slots (+0xB0/+0xB4/+0xBC) when it is set (the
// constructors of derived classes call it with 0). The two virtual base classes and the two
// classes that hold them are placeholders: their real names and contents are UNKNOWN; only their
// layout is fixed by the code.
// Field names are HYPOTHESIS.
#include "game/player/player_barrier.h"

extern "C" {
extern const f32 lbl_8042D0E8;
void* memset(void*, int, unsigned long);
}

class C_COLLI
{
public:
	C_COLLI();
	~C_COLLI();
	u8 pad[0x88]; /* 0x28..0xB0 in TObjOldPlayer */
};
struct PLAYERWK {
	PLAYERWK();
	~PLAYERWK();
	u8 raw[0x288]; /* 0x760..0x9E8 */
};
struct TASKWK {
	u8 pad0[0x24];
	RwV3d scl; /* +0x24 */
};
struct MOTIONWK {
	u8 raw[0x40];
};
class UnknownVirtualBaseA
{
};
class UnknownVirtualBaseB
{
};
class UnknownBaseA : public virtual UnknownVirtualBaseA, public virtual UnknownVirtualBaseB
{
public:
	u32 x; /* +8 */
};
class UnknownBaseB : public virtual UnknownVirtualBaseB
{
};

class TObjOldPlayer : public TObject, public C_COLLI, public UnknownBaseA, public UnknownBaseB
{
public:
	TObjOldPlayer(TObject* parent);
	virtual ~TObjOldPlayer();
	u8 padC0[0x5D4 - 0xC0];
	s32 f5d4, f5d8, f5dc; /* 0x5D4 */
	u8 pad5e0[0x634 - 0x5E0];
	u8 b634, b635, b636, b637, b638; /* 0x634 */
	u8 pad639[0x640 - 0x639];
	s32 f640;
	u8 pad644[0x668 - 0x644];
	s16 h668;
	u8 pad66a[0x678 - 0x66A];
	s32 f678, f67c, f680, f684; /* 0x678 */
	u8 pad688[0x69C - 0x688];
	f32 f69c;
	u8 b6a0;
	s32 f6a4;
	s32 f6a8, f6ac;
	u8 pad6b0[0x6F0 - 0x6B0];
	TASKWK twk;   /* 0x6F0 */
	MOTIONWK mwk; /* 0x720 */
	PLAYERWK pwk; /* 0x760 */
	u8 b9e8;
	u8 b9e9;
};

TObjOldPlayer::TObjOldPlayer(TObject* parent)
    : TObject(parent)
{
	memset(&twk, 0, sizeof(TASKWK));
	memset(&mwk, 0, sizeof(MOTIONWK));
	f5d8      = 0;
	f5d4      = 0;
	f5dc      = 0;
	f640      = 0;
	f680      = 0;
	f678      = 0;
	f684      = 0;
	f67c      = 0;
	b6a0      = 0;
	f69c      = lbl_8042D0E8;
	f6a8      = 0;
	b634      = 0;
	b635      = 0;
	b636      = 0;
	b637      = 0;
	b638      = 0;
	h668      = 0;
	f6ac      = 0;
	twk.scl.x = lbl_8042D0E8;
	twk.scl.y = lbl_8042D0E8;
	twk.scl.z = lbl_8042D0E8;
	b9e8      = 0;
}
