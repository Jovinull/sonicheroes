// TObjCannonSmoke (the PS2 build's class): the smoke the cannon leaves at the
// barrel's mouth. The constructor is inline here and also has an out-of-line
// copy (rel/cannon_smoke_ctor.cpp, which defines CANNON_SMOKE_CTOR_INLINE empty).
//
// The cannon units use C-style structs, so TObject is declared here with just
// what the smoke needs (its ctor/dtor names and the heap's new and delete).

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

struct RpClump;
struct RpAtomic;

struct TObjectBase {
	char* ClassName; // 0x00
	u8 unk04[0x14];
};

extern "C" void* lbl_8042C148;
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);
extern "C" void Free__9THeapCtrlFPv(void* heap, void* p);

class TObject : public TObjectBase
{
public:
	TObject(TObject* parent);
	virtual ~TObject();
	u8 unk1C[0x2];
	u16 DispTime; // 0x1E
	u8 unk20[0x8];

	static void* operator new(unsigned long size) { return Malloc__9THeapCtrlFUi(lbl_8042C148, size); }
	static void operator delete(void* p) { Free__9THeapCtrlFPv(lbl_8042C148, p); }
}; // 0x28

class TObjCannonSmoke : public TObject
{
public:
	s32 timer;          // 0x28
	RwV3d pos;          // 0x2C
	sAngle ang;    // 0x38
	u8 unk44[0x48];
	f32 scale[3];       // 0x8C
	f32 colorA[3];      // 0x98
	f32 colorB[3];      // 0xA4
	f32 alpha[3];       // 0xB0
	RpClump* clump;     // 0xBC
	RpAtomic* atoms[3]; // 0xC0

	TObjCannonSmoke(TObject* parent, RwV3d* place, sAngle* turn);
	// Exec comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data.
	virtual void Exec();
	virtual void TDisp();
	virtual ~TObjCannonSmoke();
}; // 0xCC

extern "C" char* CL_TObjCannonSmoke;
extern "C" void* cannonEffect;
extern "C" const f32 cannonOne[1];
extern "C" const f32 cannonSmokeAlphaB[1];
extern "C" const f32 cannonSmokeColor[1];
extern "C" const f32 cannonSmokeColorG[1];

extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8006298C(s32 kind, RwV3d* pos, sAngle* angle);
RpAtomic* objRpClumpGetAtomic(RpClump* clump, RpAtomic* after);

#ifndef CANNON_SMOKE_CTOR_INLINE
#define CANNON_SMOKE_CTOR_INLINE inline
#endif

// Full size, full alpha, the module's grey, the effect model and its three
// atomics, and the smoke's sound at its place.
CANNON_SMOKE_CTOR_INLINE TObjCannonSmoke::TObjCannonSmoke(
    TObject* parent, RwV3d* place, sAngle* turn)
    : TObject(parent)
{
	ClassName = CL_TObjCannonSmoke;
	DispTime  = 0xCC;
	pos       = *place;
	ang       = *turn;
	timer     = 0;
	alpha[0] = scale[0] = scale[1] = scale[2] = cannonOne[0];
	alpha[1]  = cannonSmokeAlphaB[0];
	alpha[2]  = cannonOne[0];
	colorA[0] = colorB[2] = colorB[1] = colorB[0] = cannonSmokeColor[0];
	colorA[1] = cannonSmokeColorG[0];
	colorA[2] = cannonSmokeColor[0];
	clump     = fn_80150588(cannonEffect);
	if (clump != NULL) {
		atoms[0] = objRpClumpGetAtomic(clump, NULL);
		atoms[1] = objRpClumpGetAtomic(clump, atoms[0]);
		atoms[2] = objRpClumpGetAtomic(clump, atoms[1]);
	}
	fn_8006298C(5, &pos, &ang);
}
