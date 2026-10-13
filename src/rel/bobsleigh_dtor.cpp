#include "types.h"
#include "game/effect/eff_bomb.h"

// TObjBobsleigh's destructor (the PS2 build's TObjBobsleigh::__dt). It
// deletes the course manager's helper, frees the sled's work arrays, material
// and both models (the shadow forgets the sled's), kills its volumes and
// signals (attack, boarding, extra, start and goal signals, and the last one
// without a collision), unloads the module's bobsleigh models (the object
// list's Unload, inlined) and leaves its slot in the sled table.

class DealMaterial
{
public:
	~DealMaterial();
};

class EffShadow
{
public:
	~EffShadow();
	void SetShadowClumpPointer(RpClump* clump) { shadowClump = clump; }

	u8 unk00[0x30];
	RpClump* shadowClump; // 0x30
	u8 unk34[0xC];
}; // 0x40

class TObjBobsleighPart : public TObject
{
public:
	u8 colli[0x88]; // 0x28 (C_COLLI)
};

class TObjBobsleigh : public TObject, public EffShadow, public C_COLLI
{
public:
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual ~TObjBobsleigh();

	u8 unkF0[0xC];
	s32 slot; // 0x0FC
	u8 unk100[0x210];
	RpClump* clump;    // 0x310
	RpClump* launcher; // 0x314
	u8* work;          // 0x318
	u8 unk31C[0x2C];
	TObjBobsleighPart* attack;      // 0x348
	TObjBobsleighPart* boarding;    // 0x34C
	TObjBobsleighPart* extra;       // 0x350
	TObjBobsleighPart* startSignal; // 0x354
	TObjBobsleighPart* goalSignal;  // 0x358
	TObject* last;                  // 0x35C
	u8 unk360[0x24];
	u8* table; // 0x384
	u8 unk388[0x4];
	DealMaterial* material; // 0x38C
};

extern "C" TObject* lbl_8042C690;
extern "C" TObjBobsleigh* lbl_80288E0C[];
extern "C" void* bobsleighModel;
extern "C" void* bobsleighLauncherModel;
extern "C" void* bobsleighLauncherMaterial;
extern "C" void* bobsleighLauncherUvAnim;

extern "C" void fn_80150958(RpClump* clump);
extern "C" void fn_80021824(void* colli);
void endObjBobsleigh_Sub();

static inline void bobsleighKill(TObjBobsleighPart*& part)
{
	if (part != NULL) {
		fn_80021824(part->colli);
		part->Signal |= 1;
		part = NULL;
	}
}

static inline void bobsleighUnload()
{
	bobsleighModel            = NULL;
	bobsleighLauncherModel    = NULL;
	bobsleighLauncherMaterial = NULL;
	bobsleighLauncherUvAnim   = NULL;
	endObjBobsleigh_Sub();
}

TObjBobsleigh::~TObjBobsleigh()
{
	if (lbl_8042C690 != NULL) {
		delete lbl_8042C690;
	}
	if (table != NULL) {
		delete[] table;
	}
	if (material != NULL) {
		delete material;
	}
	if (clump != NULL) {
		SetShadowClumpPointer(NULL);
		fn_80150958(clump);
		clump = NULL;
	}
	if (launcher != NULL) {
		fn_80150958(launcher);
		launcher = NULL;
	}
	if (work != NULL) {
		delete work;
		work = NULL;
	}
	bobsleighKill(attack);
	bobsleighKill(boarding);
	bobsleighKill(extra);
	bobsleighKill(startSignal);
	bobsleighKill(goalSignal);
	if (last != NULL) {
		last->Signal |= 1;
		last = NULL;
	}
	bobsleighUnload();
	lbl_80288E0C[slot] = NULL;
}
