#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// torchCreate, the factory rel/torch_register.cpp puts in the editor record: a
// new TObjTorch (the class name its constructor stores) that copies the set
// data's position and angle, clones the torch's model into the world slot its
// file names and takes the module's shape for its collision block (its third
// base). The allocation is a real new-expression of the class
// (rel/sample1_create.cpp). The clone is a loop over the one model file, as in
// rel/bingopanel_create.cpp: that is what keeps the zero for `added` in a saved
// register across the clone call.

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

extern "C" char* CL_TObjTorch;
extern "C" ModelFile torchModelFile[1];
extern "C" CCL_INFO torchCclInfo;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8003BF04(C_COLLI* colli, CCL_INFO* info, int count, u8 kind);

// C_COLLI::InitShare (fn_8003BF04), as rel/yajirusi_class.inc has it
inline void InitShare(C_COLLI& colli, CCL_INFO* info, int count, u8 kind)
{
	fn_8003BF04(&colli, info, count, kind);
}

class TObjTorch : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;          // 0xB8
	sAngle ang;         // 0xC4
	ModelPart parts[1]; // 0xD0

	TObjTorch(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjTorch;
		DispTime  = 0xD8;
		pos       = ObjParam->setData.pos;
		ang       = ObjParam->setData.ang;
		for (int i = 0; i < 1; i++) {
			parts[i].clump = fn_80150588(torchModelFile[i].model);
			parts[i].added = 0;
		}
		if (parts[0].added == 0) {
			fn_8015BB08(((void**)(lbl_8042C1D0 + 0x7250))[torchModelFile[0].world], parts[0].clump);
			parts[0].added = 1;
		}
		InitShare(*this, &torchCclInfo, 1, 4);
	}
	virtual void Exec();
	virtual ~TObjTorch();
	virtual void EditOnChange(SETDATA_PARAM*);
};

extern "C" void torchCreate(void)
{
	new TObjTorch(lbl_8042C110);
}
