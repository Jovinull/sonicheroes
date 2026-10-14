// TEnemyGadgetBomber (the PS2 build's name), as the C units for its clump
// handling and its constructor and destructor use it, and its DestroyClump and
// CloneClump: the bomber destroys its motion manager, body and bomb, and
// clones them again from its two static models, with a motion manager on the
// body using the bomber's motions (not playing). The destructor and the
// constructor inline them; rel/gadget_bomber_clump.cpp has the out-of-line
// copies (GADGET_BOMBER_CLUMP_INLINE empty).

typedef struct RpClump RpClump;
struct ENEMY_MOTION;

class ENEMYMTNMAN
{
public:
	ENEMYMTNMAN();
	~ENEMYMTNMAN();

	u8 unk00[0x1C];
	s32 active; // 0x1C
	u8 unk20[0xC];
	ENEMY_MOTION* motions; // 0x2C
	RpClump* clump;        // 0x30
	u8 unk34[0x18];
};

typedef struct GadgetBomber {
	char* name; // 0x00
	u8 unk04[0x14];
	void** vtable; // 0x18
	u8 unk1C[0x2];
	u16 size; // 0x1E
	u8 unk20[0xC];
	RpClump* pClump; // 0x2C
	u8 unk30[0x8];
	void* enemy;         // 0x38
	s32 field3C;         // 0x3C
	ENEMYMTNMAN* motion; // 0x40
	RpClump* bomb;       // 0x44
	f32 bombScale;       // 0x48
	s32 field4C;         // 0x4C
	f32 dropHeight;      // 0x50
	u8 unk54[0xC];
} GadgetBomber;

class TEnemyGadgetBomber
{
public:
	static RpClump* pClumpStatic[2];
};

extern "C" ENEMY_MOTION bomberMotions[];

extern "C" void fn_80150958(RpClump* clump);
extern "C" RpClump* fn_80150588(RpClump* clump);

#ifndef GADGET_BOMBER_CLUMP_INLINE
#define GADGET_BOMBER_CLUMP_INLINE inline
#endif

extern "C" GADGET_BOMBER_CLUMP_INLINE void DestroyClump__18TEnemyGadgetBomberFv(
    GadgetBomber* gadget)
{
	if (gadget->motion != NULL) {
		delete gadget->motion;
		gadget->motion = NULL;
	}
	if (gadget->pClump != NULL) {
		fn_80150958(gadget->pClump);
		gadget->pClump = NULL;
	}
	if (gadget->bomb != NULL) {
		fn_80150958(gadget->bomb);
		gadget->bomb = NULL;
	}
}

extern "C" GADGET_BOMBER_CLUMP_INLINE void CloneClump__18TEnemyGadgetBomberFv(GadgetBomber* gadget)
{
	DestroyClump__18TEnemyGadgetBomberFv(gadget);
	gadget->pClump          = fn_80150588(TEnemyGadgetBomber::pClumpStatic[0]);
	gadget->bomb            = fn_80150588(TEnemyGadgetBomber::pClumpStatic[1]);
	gadget->motion          = new ENEMYMTNMAN;
	gadget->motion->clump   = gadget->pClump;
	gadget->motion->motions = bomberMotions;
	gadget->motion->active  = 0;
}
