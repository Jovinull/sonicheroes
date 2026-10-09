// TObjEFLens, TObjEFLensSet and TObjEFLensTmp, their constructors and
// TObjEFLens's destructor, shared by rel/lens_flare_create.cpp (all inline, so
// the factory inlines the constructors), rel/lens_flare_ctor.cpp
// (TObjEFLensSet's constructor out of line, with TObjEFLens's inlined into it),
// rel/lens_flare_lens_ctor.cpp (TObjEFLens's constructor out of line),
// rel/lens_flare_dtor.cpp (TObjEFLens's destructor out of line) and
// rel/lens_flare_set_dtor.cpp and rel/lens_flare_tmp_dtor.cpp (TObjEFLensSet's
// and TObjEFLensTmp's, with TObjEFLens's inlined).
//
// TObjEFLens's constructor links the lens at the end of the efLensTop chain and
// its destructor deletes its particles, each of which unlinks itself from the
// lens's list (EFLensPtcl's inline destructor), and then takes the lens out of
// the chain. Both chain walks are written in the constructor and the destructor
// themselves, not in inline helpers: out of line, the original tests the head
// through the global and copies it into the walk's pointer (`mr r3, r0`), which
// only the direct form gives; inlined, as in the factory and TObjEFLensSet's
// constructor and destructor, both forms load the head straight into it.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

class TObjEFLens;

struct EFLensTableEntry {
	u8 unk00[0x28];
};

extern "C" char* CL_TObjEFLens;
extern "C" char* CL_TObjEFLensSet;
extern "C" char* CL_TObjEFLensTmp;
extern "C" const f32 lensFlareZero[1];
extern "C" const f32 lensFlareOne[1];
extern "C" RwV3d* lbl_8042C208;
f32 DistanceP2P(const RwV3d* a, const RwV3d* b);
extern "C" TObjEFLens* efLensTop;
extern "C" EFLensTableEntry efLensTable[12];
extern "C" TObject* lbl_8042C110;

class EFLensPtcl
{
public:
	s16 id;                        // 0x00
	u8 unk02[0x16];                // 0x02
	const EFLensTableEntry* entry; // 0x18
	TObjEFLens* owner;             // 0x1C
	EFLensPtcl* next;              // 0x20

	EFLensPtcl(s16 index, TObjEFLens* lens);
	~EFLensPtcl();
};

class TObjEFLens : public TObject
{
public:
	TObjEFLens* next;    // 0x28
	EFLensPtcl* ptclTop; // 0x2C
	f32 unk30;           // 0x30
	f32 unk34;           // 0x34

	TObjEFLens(TObject* parent);

	void DispPtcl();


	EFLensPtcl* GetPtclTop() { return ptclTop; }
	void SetPtclTop(EFLensPtcl* ptcl) { ptclTop = ptcl; }

	virtual void Exec();
	virtual ~TObjEFLens();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
	virtual RwV3d* GetPosition();
	virtual s32 SetPosition(RwV3d*);
};

#ifndef LENS_FLARE_PTCL
#define LENS_FLARE_PTCL inline
#endif

LENS_FLARE_PTCL EFLensPtcl::~EFLensPtcl()
{
	if (this == owner->GetPtclTop()) {
		owner->SetPtclTop(next);
	} else {
		EFLensPtcl* prev = owner->GetPtclTop();
		while (this != prev->next) {
			prev = prev->next;
		}
		prev->next = next;
	}
}

LENS_FLARE_PTCL EFLensPtcl::EFLensPtcl(s16 index, TObjEFLens* lens)
{
	id    = index;
	owner = lens;
	entry = &efLensTable[id];
	if (owner->GetPtclTop() == NULL) {
		owner->SetPtclTop(this);
	} else {
		EFLensPtcl* last = owner->GetPtclTop();
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = this;
	}
	next = NULL;
}

LENS_FLARE_DTOR TObjEFLens::~TObjEFLens()
{
	while (ptclTop != NULL) {
		delete ptclTop;
	}

	if (this == efLensTop) {
		efLensTop = next;
	} else {
		TObjEFLens* prev = efLensTop;
		while (this != prev->next) {
			prev = prev->next;
		}
		prev->next = next;
	}
}

LENS_FLARE_CTOR TObjEFLens::TObjEFLens(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjEFLens;
	DispTime  = 0x38;
	if (efLensTop == NULL) {
		efLensTop = this;
	} else {
		TObjEFLens* last = efLensTop;
		while (last->next != NULL) {
			last = last->next;
		}
		last->next = this;
	}
	next    = NULL;
	ptclTop = NULL;
	for (u32 i = 0; i < 12; i++) {
		new EFLensPtcl(i, this);
	}
}


struct EFLensSetParam {
	s8 kind; // 0x00
};

class TObjEFLensSet : public TObjEFLens, public TObjSetObj
{
public:
	TObjEFLensSet(TObject* parent);
	// EditOnChange first: it is the key function, and rel/lens_flare_edit.cpp
	// defines it under its C name, so no C++ unit here emits the vtable.
	virtual void EditOnChange(SETDATA_PARAM*);
	virtual void Exec();
	virtual ~TObjEFLensSet();
	virtual void TDisp();
	virtual RwV3d* GetPosition();
	virtual s32 SetPosition(RwV3d*);
};

// The other lens of the module, TObjEFLensTmp in the PS2 symbols: no placement
// base, only its own virtuals over TObjEFLens's.
class TObjEFLensTmp : public TObjEFLens
{
public:
	RwV3d pos; // 0x38

	TObjEFLensTmp(TObject* parent);
	// EditOnChange first: it is the key function and no unit defines it yet
	// (see rel/lens_flare_accessors.cpp), so no C++ unit here emits the vtable.
	virtual void EditOnChange(SETDATA_PARAM*);
	virtual void Exec();
	virtual ~TObjEFLensTmp();
	virtual void TDisp();
	virtual RwV3d* GetPosition();
	virtual s32 SetPosition(RwV3d*);
};

// The lens nearest the camera focus (the position lbl_8042C208 points at),
// GetNearestLens in the PS2 symbols, a file-local function there. Inline here
// by default; rel/lens_flare_nearest.cpp emits the module's copy.
#ifndef LENS_FLARE_NEAREST
#define LENS_FLARE_NEAREST static inline
#endif

LENS_FLARE_NEAREST TObjEFLens* GetNearestLens()
{
	if (efLensTop == NULL) {
		return NULL;
	}

	TObjEFLens* nearest = efLensTop;
	TObjEFLens* lens    = nearest->next;
	f32 best         = DistanceP2P(lbl_8042C208, nearest->GetPosition());

	while (lens != NULL) {
		f32 distance = DistanceP2P(lbl_8042C208, lens->GetPosition());
		if (distance < best) {
			best    = distance;
			nearest = lens;
		}
		lens = lens->next;
	}
	return nearest;
}

#ifndef LENS_FLARE_TMP_CTOR
#define LENS_FLARE_TMP_CTOR inline
#endif

LENS_FLARE_TMP_CTOR TObjEFLensTmp::TObjEFLensTmp(TObject* parent)
    : TObjEFLens(parent)
{
	ClassName = CL_TObjEFLensTmp;
	DispTime  = 0x44;

	pos.x = pos.y = pos.z = lensFlareZero[0];
}

LENS_FLARE_SET_CTOR TObjEFLensSet::TObjEFLensSet(TObject* parent)
    : TObjEFLens(parent)
{
	EFLensSetParam* param = (EFLensSetParam*)ObjParam->setData.setBuffer;

	ClassName = CL_TObjEFLensSet;
	DispTime  = 0x40;

	if (param != NULL) {
		if (param->kind < 0 || param->kind >= 2) {
			param->kind = 0;
		}
		switch (param->kind) {
			case 0:
				ObjParam->setData.condition.Flag |= 0x400;
				break;
			case 1:
				ObjParam->setData.condition.Flag &= ~0x400;
				break;
		}
	}
}
