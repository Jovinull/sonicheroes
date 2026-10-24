// TObjScatteredRing (the PS2 build's class), the rings a hurt player drops,
// and its base TObjRing as their constructors see them; the constructor, which
// ObjRingScatteringNonSE and ObjRingScattering inline, has its out-of-line
// copy in rel/scattered_ring_ctor.cpp (SCATTERED_RING_CTOR_INLINE empty).

#ifndef SCATTERED_RING_INC
#define SCATTERED_RING_INC

extern "C" void* lbl_8042C148;
extern "C" void* Malloc__9THeapCtrlFUi(void* heap, u32 size);

#ifndef SCATTERED_RING_CTOR_INLINE
#define SCATTERED_RING_CTOR_INLINE inline
#endif

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sRealAngle3 {
	f32 x, y, z;
} sRealAngle3;

struct RingSubstanceData {
	u8 unk00[0xD8];
};

struct RingSubstance : public RingSubstanceData {
	virtual void vslot0();
	virtual void Init(void* group, s8 number);
	u8 unkDC[0xC]; // 0xDC
}; // 0xE8

// TObject's layout as these constructors see it; its vtable pointer is a
// plain field here, so that no vtable of ours is written (the vtables stay in
// each module's data), while the constructor is TObject's own; the declared
// destructors give the constructor its cleanup region, as the retail's has
struct TObject {
	TObject(TObject* parent);
	~TObject();

	static void* operator new(unsigned long size)
	{
		return Malloc__9THeapCtrlFUi(lbl_8042C148, size);
	}

	const char* className; // 0x00
	u8 unk04[0x14];        // 0x04
	void** vtable;         // 0x18
	u8 unk1C[0x2];         // 0x1C
	s16 objectSize;        // 0x1E
	u8 unk20[0x8];         // 0x20
};

// TObjRing (rel/ring_cdtor.cpp), its constructor inlined here
struct TObjRing : public TObject {
	TObjRing(TObject* parent);
	~TObjRing();

	s8 numRings;          // 0x28
	s8 kind;              // 0x29
	s8 active;            // 0x2A
	s8 unk2B;             // 0x2B
	RwV3d pos;            // 0x2C
	sRealAngle3 ang;      // 0x38
	f32 spread;           // 0x44
	f32 speed;            // 0x48
	RingSubstance* rings; // 0x4C
};

struct TObjScatteredRing : public TObjRing {
	TObjScatteredRing(TObject* parent, unsigned int count, RwV3d* pos, sRealAngle3* ang,
	    float speed, float spread, int sound);
};

extern "C" void* lbl_8042C388;
extern "C" const char* ringClassName;
extern "C" const char* scatteredRingClassName;
extern "C" void* scrollRingVtableC[];
extern "C" void* scatteredRingVtable[];
extern "C" const f32 scrollRingStopped[1];

extern "C" void* __nwa__FUl(u32 size);
extern "C" void* __construct_new_array(void* block, void* ctor, void* dtor, u32 size, u32 count);
extern "C" void* scrollRingFieldCtor(void* object, s16 most);
extern "C" void scrollRingFieldDtor(void*, int);
extern "C" void fn_800B52E8(void* sound, s32 id, s32 a, s32 b);

inline TObjRing::TObjRing(TObject* parent)
    : TObject(parent)
{
	vtable     = scrollRingVtableC;
	className  = ringClassName;
	objectSize = 0x50;
	unk2B      = 0;
	active     = 1;
	rings      = NULL;
}

SCATTERED_RING_CTOR_INLINE TObjScatteredRing::TObjScatteredRing(TObject* parent, unsigned int count,
    RwV3d* pos, sRealAngle3* ang, float speed, float spread, int sound)
    : TObjRing(parent)
{
	vtable     = scatteredRingVtable;
	className  = scatteredRingClassName;
	objectSize = 0x50;
	this->pos  = *pos;
	if (ang != NULL) {
		this->ang = *ang;
	} else {
		this->ang.x = this->ang.y = this->ang.z = scrollRingStopped[0];
	}
	this->spread = spread;
	this->speed  = speed;
	if (count < 1) {
		count = 1;
	}
	if (count > 20) {
		count = 20;
	}
	numRings = count;
	kind     = 4;
	s32 n    = numRings;
	rings    = (RingSubstance*)__construct_new_array(__nwa__FUl(n * sizeof(RingSubstance) + 0x10),
	    scrollRingFieldCtor, scrollRingFieldDtor, sizeof(RingSubstance), n);
	for (s8 i = 0; i < numRings; i++) {
		rings[i].Init(this, i);
	}
	if (sound == 1 && lbl_8042C388 != NULL) {
		fn_800B52E8(lbl_8042C388, 0x1005, 0, 0);
	}
}

#endif
