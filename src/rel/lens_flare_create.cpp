#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// lensFlareCreate, the factory the editor record for TObjEFLensSet points at,
// in the thirteen stage modules that share the engine core.
//
// The allocation is a real new-expression of the C++ class with every
// constructor on the way inlined. TObjEFLensSet derives from TObjEFLens, the
// lens flare itself, and from the placement base; the PS2 build names all
// three classes, EFLensPtcl included. TObjEFLens adds three virtuals of its
// own (EditOnChange, GetPosition and SetPosition), which is why the placement
// base's vtable starts 0x38 into the set's.
//
// TObjEFLens joins the module's chain of lens flares (LinkChain, as in
// rel/s23_warppos_create.cpp) and builds its twelve particles, each a real
// new-expression through the global operator new: a particle takes its index,
// its owner and its entry of the module's table, and joins the end of the
// owner's particle list. The set then folds the placement's kind into 0 or 1
// and sets or clears bit 0x400 of the placement's flags to match.

class TObjEFLens;

struct EFLensTableEntry {
	u8 unk00[0x28];
};

extern "C" char* CL_TObjEFLens;
extern "C" char* CL_TObjEFLensSet;
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

	inline EFLensPtcl(s16 index, TObjEFLens* lens);
};

class TObjEFLens : public TObject
{
public:
	TObjEFLens* next;    // 0x28
	EFLensPtcl* ptclTop; // 0x2C
	f32 unk30;           // 0x30
	f32 unk34;           // 0x34

	TObjEFLens(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjEFLens;
		DispTime  = 0x38;
		LinkChain();
		next    = NULL;
		ptclTop = NULL;
		for (u32 i = 0; i < 12; i++) {
			new EFLensPtcl(i, this);
		}
	}

	void LinkChain()
	{
		if (efLensTop == NULL) {
			efLensTop = this;
		} else {
			TObjEFLens* last = efLensTop;
			while (last->next != NULL) {
				last = last->next;
			}
			last->next = this;
		}
	}

	EFLensPtcl* GetPtclTop() { return ptclTop; }
	void SetPtclTop(EFLensPtcl* ptcl) { ptclTop = ptcl; }

	virtual ~TObjEFLens();
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
	virtual RwV3d* GetPosition();
	virtual void SetPosition(RwV3d*);
};

inline EFLensPtcl::EFLensPtcl(s16 index, TObjEFLens* lens)
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

struct EFLensSetParam {
	s8 kind; // 0x00
};

class TObjEFLensSet : public TObjEFLens, public TObjSetObj
{
public:
	TObjEFLensSet(TObject* parent)
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
	virtual ~TObjEFLensSet();
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void lensFlareCreate(void)
{
	new TObjEFLensSet(lbl_8042C110);
}
