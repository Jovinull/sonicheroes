// TObjS23WarpPos, shared by rel/s23_warppos_create.cpp, which defines S23_WARPPOS_CTOR
// as inline so its factory inlines the constructor, and rel/s23_warppos_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

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

	TObjS23WarpPos(TObject* parent);

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

	virtual void Exec();
	virtual ~TObjS23WarpPos();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

S23_WARPPOS_CTOR TObjS23WarpPos::TObjS23WarpPos(TObject* parent)
    : TObject(parent)
{
	S23WarpPosParam* param = (S23WarpPosParam*)ObjParam->setData.setBuffer;

	ClassName = CL_TObjS23WarpPos;
	DispTime  = 0x40;

	pos = ObjParam->setData.pos;
	pos.y += param->height;

	LinkChain();
}
