#include "MSL_C/string.h"
#include "game/enemy/e_gadget.h"

// TEnemyGadgetLaser's constructor (the PS2 build's name): the laser takes its
// searcher as owner, puts its collision on the searcher's position and clears
// its six parts and three beams, then clones them from the nine static models
// (pClumpStatic). The collision block is a second base of the gadget, built
// right after TEnemyGadget and before the vtable is set, and written as a real
// constructor: as a C function the clearing loops of DestroyClump (inline here)
// come out with an advancing pointer instead of the retail's induced offset.
// The destructor stays a C function (rel/gadget_laser_dtor.cpp).

class TObjEnemySearcher;
struct CCL_INFO;

class C_COLLI
{
public:
	C_COLLI();
	~C_COLLI();
	void Init(CCL_INFO*, int, u8);
	u8 pad00[0x10];
	struct {
		u8 pad[4];
		u32 flags;
	}* info; // 0x10
	u8 pad14[0x4C];
	f32 pos[3]; // 0x60
	u8 pad6C[0x1C];
};

extern "C" char* gadgetLaserClassName;
extern "C" u8 gadgetLaserColliInfo[];
extern "C" const f32 gadgetBombScaleXZ;
extern "C" RpClump* pClumpStatic__17TEnemyGadgetLaser[9];
extern "C" void fn_80150958(RpClump* clump);
extern "C" RpClump* fn_80150588(RpClump* clump);

class TEnemyGadgetLaser : public TEnemyGadget, public C_COLLI
{
public:
	TEnemyGadgetLaser(TObjEnemySearcher* owner);

	// Declared first and defined elsewhere: no vtable is emitted here.
	virtual void Update();

	TObjEnemy* enemy;  // 0xC0
	f32 scaleA[3];     // 0xC4
	f32 scaleB[3];     // 0xD0
	s32 zeroDC;        // 0xDC
	s32 zeroE0;        // 0xE0
	s32 zeroE4;        // 0xE4
	s32 colour;        // 0xE8
	f32 scaleC;        // 0xEC
	s32 ready;         // 0xF0
	s32 readyF4;       // 0xF4
	RpClump* parts[6]; // 0xF8
	RpClump* beams[3]; // 0x110
	s32 zero11C;       // 0x11C
	s32 zero120;       // 0x120
	s32 zero124;       // 0x124
	s32 zero128;       // 0x128
	s32 count;         // 0x12C
	s32 zero130;       // 0x130
	u8 tail[0x140];    // 0x134

	void DestroyClump();
};

inline void TEnemyGadgetLaser::DestroyClump()
{
	int i;

	for (i = 2; i >= 0; i--) {
		if (beams[i] != NULL) {
			fn_80150958(beams[i]);
			beams[i] = NULL;
		}
	}
	for (i = 5; i >= 0; i--) {
		if (parts[i] != NULL) {
			fn_80150958(parts[i]);
			parts[i] = NULL;
		}
	}
}

TEnemyGadgetLaser::TEnemyGadgetLaser(TObjEnemySearcher* owner)
    : TEnemyGadget((TObjEnemy*)owner)
{
	ClassName = gadgetLaserClassName;
	DispTime  = 0x274;
	enemy     = (TObjEnemy*)owner;
	scaleA[0] = scaleA[1] = scaleA[2] = gadgetBombScaleXZ;
	scaleB[0] = scaleB[1] = scaleB[2] = gadgetBombScaleXZ;
	colour                            = 0xFFFF0000;
	scaleC                            = gadgetBombScaleXZ;
	zeroDC = zeroE0 = zeroE4 = 0;
	Init((CCL_INFO*)gadgetLaserColliInfo, 1, 3);
	{
		f32* src = (f32*)((u8*)pOwner + 0x140);
		pos[0]   = src[0];
		pos[1]   = src[1];
		pos[2]   = src[2];
	}
	info->flags |= 0x10;
	parts[0] = NULL;
	parts[1] = NULL;
	parts[2] = NULL;
	parts[3] = NULL;
	parts[4] = NULL;
	parts[5] = NULL;
	beams[0] = NULL;
	beams[1] = NULL;
	beams[2] = NULL;
	DestroyClump();
	parts[0] = fn_80150588(pClumpStatic__17TEnemyGadgetLaser[3]);
	parts[1] = fn_80150588(pClumpStatic__17TEnemyGadgetLaser[4]);
	parts[2] = fn_80150588(pClumpStatic__17TEnemyGadgetLaser[5]);
	parts[3] = fn_80150588(pClumpStatic__17TEnemyGadgetLaser[6]);
	parts[4] = fn_80150588(pClumpStatic__17TEnemyGadgetLaser[7]);
	parts[5] = fn_80150588(pClumpStatic__17TEnemyGadgetLaser[8]);
	beams[0] = fn_80150588(pClumpStatic__17TEnemyGadgetLaser[0]);
	beams[1] = fn_80150588(pClumpStatic__17TEnemyGadgetLaser[1]);
	beams[2] = fn_80150588(pClumpStatic__17TEnemyGadgetLaser[2]);
	ready    = 1;
	zero11C  = 0;
	zero120  = 0;
	zero128  = 0;
	zero124  = 0;
	count    = 4;
	zero130  = 0;
	memset(tail, 0, 0x140);
	readyF4 = 1;
}
