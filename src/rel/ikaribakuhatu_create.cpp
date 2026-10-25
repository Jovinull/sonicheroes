#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

// ikaribakuhatuCreate, the factory rel/ikaribakuhatu_register.cpp puts in the
// editor record: a new TObjIkariBakuhatu (the class name its constructor
// stores) that copies the set data's position and angle, clears its 32 pieces
// and gives as many of them as the set data asks for a clone of the module's
// 3 models in turn. Its collision block (its third base) takes the module's
// shape sized by the set data's first parameter. The allocation is a real
// new-expression of the class (rel/sample1_create.cpp).

// One of the module's model files: its name, the archive it is read from, the
// world slot its clones go into, and the model once loaded.
struct ModelFile {
	const char* name; // 0x00
	void* archive;    // 0x04
	s32 world;        // 0x08
	void* model;      // 0x0C
};

// one of the pieces
struct IkariBakuhatuPiece {
	RpClump* clump; // 0x00
	u8 unk04[0x34];
}; // 0x38

// the set data's parameters
struct IkariBakuhatuParam {
	f32 size; // 0x00: the collision shape's size
	u8 unk04[0xC];
	s8 count; // 0x10: the pieces used
};

extern "C" char* CL_TObjIkariBakuhatu;
extern "C" ModelFile ikaribakuhatuModelFiles[3];
extern "C" CCL_INFO ikaribakuhatuCclInfo;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void* memset(void* dst, s32 value, u32 size);

class TObjIkariBakuhatu : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;                     // 0xB8
	sAngle ang;                    // 0xC4
	s32 unkD0;                     // 0xD0
	s32 count;                     // 0xD4
	s32 unkD8;                     // 0xD8
	IkariBakuhatuPiece pieces[32]; // 0xDC

	TObjIkariBakuhatu(TObject* parent)
	    : TObject(parent)
	{
		ClassName = CL_TObjIkariBakuhatu;
		DispTime  = 0x7DC;

		IkariBakuhatuParam* param = (IkariBakuhatuParam*)ObjParam->setData.setBuffer;

		pos   = ObjParam->setData.pos;
		ang   = ObjParam->setData.ang;
		count = param->count;
		memset(pieces, 0, sizeof(pieces));
		for (int i = 0; i < count; i++) {
			pieces[i].clump = fn_80150588(ikaribakuhatuModelFiles[i % 3].model);
		}
		unkD0                  = 0;
		unkD8                  = 0;
		ikaribakuhatuCclInfo.a = param->size;
		Init(&ikaribakuhatuCclInfo, 1, 4);
	}
	virtual ~TObjIkariBakuhatu();
};

extern "C" void ikaribakuhatuCreate(void)
{
	new TObjIkariBakuhatu(lbl_8042C110);
}
