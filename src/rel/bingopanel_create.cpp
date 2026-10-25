#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// bingopanelCreate, the factory rel/bingopanel_register.cpp puts in the editor
// record: a new TObjBingoPanel (the class name its constructor stores) that
// copies the set data's position and angle, clones each of its 19 models, adds
// the first two (the panel and its frame) to the world slots their files name,
// and then sets itself up from its communication id and second parameter
// (fn_5_80B30, whose result it keeps) and fn_5_81188. The allocation is a real
// new-expression of the class (rel/sample1_create.cpp).

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

struct ModelPart {
	RpClump* clump; // 0x00
	s32 added;      // 0x04
};

// the set data's parameters
struct BingopanelParam {
	u8 unk00[0x4];
	s32 unk04; // 0x04
};

class TObjBingoPanel;

extern "C" char* CL_TObjBingoPanel;
extern "C" ModelFile bingopanelModelFiles[19];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" s32 fn_5_80B30(TObjBingoPanel* panel, u8 id, s32 value);
extern "C" void fn_5_81188(TObjBingoPanel* panel);

class TObjBingoPanel : public TObject, public TObjSetObj
{
public:
	RwV3d pos;           // 0x30
	sAngle ang;          // 0x3C
	s32 unk48;           // 0x48
	ModelPart parts[19]; // 0x4C

	TObjBingoPanel(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjBingoPanel;
		DispTime  = 0xE4;

		BingopanelParam* param = (BingopanelParam*)ObjParam->setData.setBuffer;

		pos = ObjParam->setData.pos;
		ang = ObjParam->setData.ang;
		for (int i = 0; i < 19; i++) {
			parts[i].clump = fn_80150588(bingopanelModelFiles[i].model);
			parts[i].added = 0;
		}
		if (parts[0].added == 0) {
			fn_8015BB08(
			    ((void**)(lbl_8042C1D0 + 0x7250))[bingopanelModelFiles[0].world], parts[0].clump);
			parts[0].added = 1;
		}
		if (parts[1].added == 0) {
			fn_8015BB08(
			    ((void**)(lbl_8042C1D0 + 0x7250))[bingopanelModelFiles[1].world], parts[1].clump);
			parts[1].added = 1;
		}
		unk48 = fn_5_80B30(this, ObjParam->setData.communicateId, param->unk04);
		fn_5_81188(this);
	}
	virtual ~TObjBingoPanel();
};

extern "C" void bingopanelCreate(void)
{
	new TObjBingoPanel(lbl_8042C110);
}
