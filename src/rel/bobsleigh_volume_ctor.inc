// What TObjBobsleighVacuum's and TObjBobsleighAttack's constructors (the PS2
// build's names) share: the object and collision bases, the class's vtable
// and name, the display order and a cleared done flag.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct CCL_INFO {
	u8 unk00[0x14];
	f32 a; // 0x14
} CCL_INFO;

typedef struct BobsleighParent {
	u8 unk000[0xF8];
	s32 kind;       // 0x0F8
	u8 unk0FC[0xA0];
	s32 team;       // 0x19C
} BobsleighParent;

typedef struct BobsleighVolume {
	char* className;         // 0x00
	u8 unk04[0xC];
	BobsleighParent* parent; // 0x10
	u8 unk14[0x4];
	void** vtable;           // 0x18
	u8 unk1C[0x2];
	u16 dispTime;            // 0x1E
	u8 unk20[0x8];
	u8 colli[0x10];          // 0x28, C_COLLI
	CCL_INFO* info;          // 0x38
	u8 unk3C[0x64];
	s32 characterId;         // 0xA0
	u8 unkA4[0xC];
	s32 done;                // 0xB0
} BobsleighVolume;

extern "C" void __ct__7TObjectFP7TObject(void* object, void* parent);
extern "C" void __ct__7C_COLLIFv(void* colli);
extern "C" void Init__7C_COLLIFP8CCL_INFOiUc(void* colli, CCL_INFO* info, s32 count, u8 kind);
extern "C" void CalcRange__7C_COLLIFv(void* colli);
