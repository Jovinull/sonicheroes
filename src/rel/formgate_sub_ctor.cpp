#include "game/effect/eff_bomb.h"

// TObjFormGateSub's constructor (the PS2 build's TObjFormGateSub::__ct, with the
// same arguments): one of the formation gate's three gate parts. It puts its
// collision at the position and angles it is given, keeps the kind and
// offset, gives the collision its shape and grows the shape by the offset.

class TObjFormGateSub : public TObject, public C_COLLI
{
public:
	s8 kind; // 0xB0
	u8 padB1[0x3];
	s32 unkB4;  // 0xB4
	f32 offset; // 0xB8

	TObjFormGateSub(TObject* parent, RwV3d* place, sAngle* turn, s8 kind, f32 offset);
	// Exec comes first so that it is the key function: no unit of ours emits
	// the vtable, which stays in each module's data.
	virtual void Exec();
	virtual ~TObjFormGateSub();
}; // 0xBC

extern "C" char* CL_TObjFormGateSub;
extern "C" CCL_INFO formgateSubCclInfo;

TObjFormGateSub::TObjFormGateSub(TObject* parent, RwV3d* place, sAngle* turn, s8 kind, f32 offset)
    : TObject(parent)
{
	ClassName    = CL_TObjFormGateSub;
	DispTime     = 0xBC;
	pos          = *place;
	ang          = *turn;
	this->kind   = kind;
	this->offset = offset;
	unkB4        = 0;
	Init(&formgateSubCclInfo, 1, 4);
	info->a += this->offset;
}
