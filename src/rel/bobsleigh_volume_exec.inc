// The Exec that TObjBobsleighVacuum and TObjBobsleighAttack share (the PS2
// build has one of each, with the same body): once told to go (unkB0) the
// volume ends itself; while the game runs (not stopped, stage mode not 1 to 5)
// and its bobsleigh is alive it follows the bobsleigh (position and angles,
// keeping the last position) and enters its collision, otherwise it clears it.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct BobsleighAngle {
	s32 x, y, z;
} BobsleighAngle;

typedef struct Bobsleigh {
	u8 unk000[0x4];
	u16 signal;          // 0x004
	u8 unk006[0xFE];
	RwV3d pos;           // 0x104
	u8 unk110[0x18];
	BobsleighAngle ang;  // 0x128
} Bobsleigh;

typedef struct BobsleighVolume {
	u8 unk00[0x4];
	u16 signal;          // 0x04
	u8 unk06[0xA];
	Bobsleigh* parent;   // 0x10
	u8 unk14[0x14];
	u8 colli[0x60];      // 0x28, C_COLLI
	RwV3d pos;           // 0x88 (the collision's)
	BobsleighAngle ang;  // 0x94
	u8 unkA0[0x4];
	RwV3d prePos;        // 0xA4
	s32 done;            // 0xB0
} BobsleighVolume;

struct BobsleighStage {
	u8 unk00[0x18];
	s32 mode; // 0x18
};

extern "C" u8* lbl_8042C180;
extern "C" BobsleighStage lbl_8029C310;

extern "C" void Entry__7C_COLLIFv(void* colli);
extern "C" void ClearInfo__7C_COLLIFv(void* colli);

static inline void bobsleighVolumeExec(BobsleighVolume* object)
{
	if (object->done != 0) {
		object->signal |= 1;
		return;
	}
	if ((s8)lbl_8042C180[0x22] == 0 && lbl_8029C310.mode != 1 && lbl_8029C310.mode != 2
	    && lbl_8029C310.mode != 3 && lbl_8029C310.mode != 4 && lbl_8029C310.mode != 5
	    && (object->parent->signal & 1) == 0) {
		Bobsleigh* parent = object->parent;

		object->prePos = object->pos;
		object->pos    = parent->pos;
		object->ang    = parent->ang;
		Entry__7C_COLLIFv(object->colli);
	} else {
		ClearInfo__7C_COLLIFv(object->colli);
	}
}
