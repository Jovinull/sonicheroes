// TObjEFLens and TObjEFLensSet with their constructors, shared by
// rel/lens_flare_create.cpp (both inline, so the factory inlines them) and
// rel/lens_flare_ctor.cpp (TObjEFLensSet's out of line, with TObjEFLens's
// inlined into it). TObjEFLens's own out-of-line copy is not matched yet: its
// chain walk comes out in another shape when compiled on its own.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

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

	TObjEFLens(TObject* parent);

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

LENS_FLARE_CTOR TObjEFLens::TObjEFLens(TObject* parent)
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


struct EFLensSetParam {
	s8 kind; // 0x00
};

class TObjEFLensSet : public TObjEFLens, public TObjSetObj
{
public:
	TObjEFLensSet(TObject* parent);
	virtual ~TObjEFLensSet();
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

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
