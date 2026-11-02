#include "types.h"

// The constructor of the special stages' second sled link class (BobLinkPoint
// here; the classes have no PS2 names), in stage01D and stage07D. The base
// constructor (rel/bob_link_base.cpp has it as bobLinkCtor) is inlined: it
// lets go of the current link and becomes the current one, unlinked. Then the
// point, direction, timer and slots come from the caller's parameters, and the
// object attaches at once (as bobLinkAttachPoint does).

#include "src/rel/bob_link_classes.inc"

typedef struct BobLinkPointParams {
	s16 timer; // 0x00
	u8 pad02[0x2];
	RwV3d* dir;  // 0x04
	RwV3d* at;   // 0x08
	s32 slotIn;  // 0x0C
	s32 slotOut; // 0x10
	s32 unk14;   // 0x14
} BobLinkPointParams;

extern "C" const char* bobLinkPointClassName;

class BobLinkPoint : public BobLink
{
public:
	BobLinkPoint(BobLinkPointParams* params);
	virtual ~BobLinkPoint();

	u8 active; // 0x34
	u8 pad35;
	s16 timer; // 0x36
	RwV3d* at; // 0x38
	RwV3d dir; // 0x3C
	s32 unk48; // 0x48
}; // 0x4C

// bobLinkAttachPoint (rel/bob_link_attach_point.cpp), inlined.
static inline void bobLinkPointAttach(BobLinkPoint* object)
{
	lbl_803EA4E8.mode     = 0;
	lbl_803EA4E8.unk04[0] = 0;
	lbl_803EA4E8.unk04[1] = 0;
	lbl_803EA4E8.unk04[2] = 0;
	{
		RwV3d* at = object->at;

		lbl_803EA4E8.at.x = at->x;
		lbl_803EA4E8.at.y = at->y;
		lbl_803EA4E8.at.z = at->z;
	}
	lbl_803EA4E8.dir.x = object->dir.x;
	lbl_803EA4E8.dir.y = object->dir.y;
	lbl_803EA4E8.dir.z = object->dir.z;
	lbl_803EA4E8.ang.x = lbl_803EA4E8.ang.y = lbl_803EA4E8.ang.z = 0;
	fn_80131088(0xE, object);
	fn_8004D9B8(lbl_8042C1F8);
	fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), object->slotIn);
	object->linked = 1;
	object->active = 1;
}

BobLinkPoint::BobLinkPoint(BobLinkPointParams* params)
{
	className = bobLinkPointClassName;
	dispTime  = 0x4C;
	at        = params->at;
	{
		RwV3d* from = params->dir;

		dir.x = from->x;
		dir.y = from->y;
		dir.z = from->z;
	}
	timer = params->timer;
	unk48 = params->unk14;
	{
		s32 out = params->slotOut;

		slotIn  = params->slotIn;
		slotOut = out;
	}
	bobLinkPointAttach(this);
}
