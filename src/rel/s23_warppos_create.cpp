#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// s23WarpposCreate, the factory rel/s23_warppos_register.cpp puts in the editor
// record for TObjS23WarpPos, in stage07D.
//
// The allocation is a real new-expression of the C++ class, which is what
// gives the original's `mr r0, r3` and then `mr r31, r0`; rel/sample1_create.cpp
// has the long form.
//
// Each warp position raises its placement by the height in its parameter block
// and joins the end of the chain the class keeps in pTopWarp, the static
// member the PS2 build names; LinkChain is inlined into the constructor here.

struct S23WarpPosParam {
	f32 height; // 0x00
};

extern "C" char* CL_TObjS23WarpPos;
extern "C" TObject* lbl_8042C110;

class TObjS23WarpPos : public TObject, public TObjSetObj
{
public:
	RwV3d pos;            // 0x30
	TObjS23WarpPos* next; // 0x3C

	static TObjS23WarpPos* pTopWarp;

	TObjS23WarpPos(TObject* parent)
	    : TObject(parent)
	{
		S23WarpPosParam* param = (S23WarpPosParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjS23WarpPos;
		DispTime  = 0x40;

		pos = ObjParam->setData.pos;
		pos.y += param->height;

		LinkChain();
	}

	void LinkChain()
	{
		if (pTopWarp == NULL) {
			pTopWarp = this;
		} else {
			TObjS23WarpPos* last = pTopWarp;
			while (last->next != NULL) {
				last = last->next;
			}
			last->next = this;
		}
		next = NULL;
	}

	virtual ~TObjS23WarpPos();
	virtual void Exec();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void s23WarpposCreate(void)
{
	new TObjS23WarpPos(lbl_8042C110);
}
