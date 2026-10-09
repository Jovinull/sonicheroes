// TObjTrainRollTunnel, shared by rel/train_roll_tunnel_create.cpp, which defines TRAIN_ROLL_TUNNEL_CTOR
// as inline so its factory inlines the constructor, and rel/train_roll_tunnel_ctor.cpp,
// which defines it empty to emit the out-of-line copy the module also keeps.

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

extern "C" char* CL_TObjTrainRollTunnel;
extern "C" ModelFile trainRollTunnelModelFiles[6];
extern "C" u8* lbl_8042C1D0;
extern "C" TObject* lbl_8042C110;
extern "C" RpClump* fn_80150588(void* model);
extern "C" void fn_8015BB08(void* world, RpClump* clump);

class TObjTrainRollTunnel : public TObject, public TObjSetObj, public C_COLLI
{
public:
	RwV3d pos;          // 0xB8
	sAngle ang;         // 0xC4
	ModelPart parts[6]; // 0xD0

	TObjTrainRollTunnel(TObject* parent);
	virtual void Exec();
	virtual ~TObjTrainRollTunnel();
	virtual void EditOnChange(SETDATA_PARAM*);
};

TRAIN_ROLL_TUNNEL_CTOR TObjTrainRollTunnel::TObjTrainRollTunnel(TObject* parent)
    : TObject(parent)
{
	ClassName = CL_TObjTrainRollTunnel;
	DispTime  = 0x100;

	pos = ObjParam->setData.pos;
	ang = ObjParam->setData.ang;

	for (int i = 0; i < 6; i++) {
		ModelFile* file = &trainRollTunnelModelFiles[i];
		parts[i].clump  = fn_80150588(file->model);
		parts[i].added  = 0;
		if (parts[i].added == 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + file->world * 4), parts[i].clump);
			parts[i].added = 1;
		}
	}
}
