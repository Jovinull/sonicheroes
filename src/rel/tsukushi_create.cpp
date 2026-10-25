#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// tsukushiCreate, the factory rel/tsukushi_register.cpp puts in the editor
// record: a new TObjTsukushi (the class name its constructor stores). The set
// data's first parameter picks which of its 4 models it shows: each model is
// cloned and only the picked one goes into the world slot its file names. The
// allocation is a real new-expression of the class (rel/sample1_create.cpp);
// the part helper takes a u32 index, as rel/kazariobj_create.cpp's does.

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
struct TsukushiParam {
	s32 kind; // 0x00: the model shown
};

extern "C" char* CL_TObjTsukushi;
extern "C" ModelFile tsukushiModelFiles[4];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

class TObjTsukushi : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;          // 0xB8
	sAngle ang;         // 0xC4
	ModelPart parts[4]; // 0xD0

	// puts part `no` into its file's world slot or takes it out
	inline void SetShow(u32 no, int show)
	{
		if (show) {
			if (parts[no].added == 0) {
				fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + tsukushiModelFiles[no].world * 4),
				    parts[no].clump);
				parts[no].added = 1;
			}
		} else if (parts[no].added == 1) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7250 + tsukushiModelFiles[no].world * 4),
			    parts[no].clump);
			parts[no].added = 0;
		}
	}

	TObjTsukushi(TObject* parent)
	    : TObject(parent)
	{
		TsukushiParam* param = (TsukushiParam*)ObjParam->setData.setBuffer;

		ClassName = CL_TObjTsukushi;
		DispTime  = 0xF0;
		pos       = ObjParam->setData.pos;
		ang       = ObjParam->setData.ang;
		for (int i = 0; i < 4; i++) {
			ModelFile* file = &tsukushiModelFiles[i];
			parts[i].clump  = fn_80150588(file->model);
			parts[i].added  = 0;
			SetShow(i, i == param->kind);
		}
	}
	virtual ~TObjTsukushi();
};

extern "C" void tsukushiCreate(void)
{
	new TObjTsukushi(lbl_8042C110);
}
