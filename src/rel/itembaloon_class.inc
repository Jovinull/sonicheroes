// TObjItembaloon, shared by rel/itembaloon_create.cpp, which defines ITEMBALOON_CTOR
// as inline so its factory inlines the constructor, and rel/itembaloon_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

struct ItembaloonParam {
	u8 item;  // 0x00
	f32 size; // 0x04
};

extern "C" char* CL_TObjItembaloon;
extern "C" CCL_INFO itembaloonCclInfo;
extern "C" void* itembaloonResource;
extern "C" const f32 itembaloonOne[1];
extern "C" const f32 itembaloonZero[1];
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
void objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(RpClump*, u32);

class TObjItembaloon : public TObject, public TObjSetObj, public C_COLLI
{
public:
	u8 item;        // 0xB8
	s32 unkBC;      // 0xBC
	RwV3d pos;      // 0xC0
	sAngle ang;     // 0xCC
	f32 size;       // 0xD8
	f32 unkDC;      // 0xDC
	RwV3d scale;    // 0xE0
	s32 unkEC;      // 0xEC
	RpClump* clump; // 0xF0

	TObjItembaloon(TObject* parent);
	virtual ~TObjItembaloon();
	virtual void Exec();
	virtual void Disp();
	virtual void TDisp();
	virtual void EditOnChange(SETDATA_PARAM*);
};

ITEMBALOON_CTOR TObjItembaloon::TObjItembaloon(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjItembaloon;
	DispTime  = 0xF4;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	ItembaloonParam* param = (ItembaloonParam*)ObjParam->setData.setBuffer;

	item    = param->item;
	size    = itembaloonOne[0] + param->size;
	unkEC   = 0;
	unkDC   = itembaloonZero[0];
	scale.x = itembaloonOne[0];
	scale.y = itembaloonOne[0];
	scale.z = itembaloonOne[0];
	unkBC   = 1;

	clump    = fn_80150588(itembaloonResource);
	u32 flag = *(volatile u32*)&ObjParam->setData.condition.Flag;
	objRpClumpForAllAtomicsToSetRenderCallbackToUseLight(clump, ((flag & 0x1C0000) >> 18) + 4);

	Init(&itembaloonCclInfo, 1, 4);
	info->a = itembaloonCclInfo.a * size;
	CalcRange();
}
