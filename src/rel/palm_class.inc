// TObjPalm, stage09D's palm, shared by rel/palm_create.cpp, which inlines the
// constructor into its factory, and rel/palm_dtor.cpp. It is laid out as
// TObjYajirusi (rel/yajirusi_class.inc) is, but the set data's first
// parameter picks which of its 2 models goes into the world, and its second
// scales the collision shape.

#include "game/effect/eff_bomb.h"
#include "game/setObj.h"

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
struct PalmParam {
	s32 kind;  // 0x00: the model put in the world
	f32 scale; // 0x04: scales the collision shape
};

extern "C" char* CL_TObjPalm;
extern "C" ModelFile palmModelFiles[2];
extern "C" CCL_INFO palmCclInfo;
extern "C" f32 palmCclScale;
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);
extern "C" void fn_8015BBF8(void* world, RpClump* clump);

class TObjPalm : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;          // 0xB8
	sAngle ang;         // 0xC4
	ModelPart parts[2]; // 0xD0

	TObjPalm(TObject* parent);
	virtual void Exec();
	virtual ~TObjPalm();
	virtual void EditOnChange(SETDATA_PARAM*);
};

inline TObjPalm::TObjPalm(TObject* parent)
    : TObject(parent)
{
	PalmParam* param = (PalmParam*)ObjParam->setData.setBuffer;

	ClassName = CL_TObjPalm;
	DispTime  = 0xE0;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	for (int i = 0; i < 2; i++) {
		ModelFile* file = &palmModelFiles[i];
		parts[i].clump  = fn_80150588(file->model);
		parts[i].added  = 0;
		if (i == param->kind) {
			if (parts[i].added == 0) {
				fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
				parts[i].added = 1;
			}
		} else if (parts[i].added == 1) {
			fn_8015BBF8(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
			parts[i].added = 0;
		}
	}
	palmCclInfo.a = palmCclScale * param->scale;
	Init(&palmCclInfo, 1, 4);
}
