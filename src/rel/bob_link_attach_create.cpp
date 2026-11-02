#include "types.h"

// Makes the special stages' first sled link object (BobLinkAttach here; the
// classes have no PS2 names), in stage01D and stage07D: a new object whose
// constructor, inlined with the base one, takes the timer, point, direction,
// flags and slots from the caller's parameters and attaches at once (as
// bobLinkAttach does).

#include "src/rel/bob_link_classes.inc"

typedef struct BobLinkAttachParams {
	s16 timer; // 0x00
	u8 pad02[0x2];
	RwV3d* dir;  // 0x04
	RwV3d* at;   // 0x08
	s32 slotIn;  // 0x0C
	s32 slotOut; // 0x10
	u32 flags;   // 0x14
} BobLinkAttachParams;

extern "C" const char* bobLinkAttachClassName;

class BobLinkAttach : public BobLink
{
public:
	BobLinkAttach(BobLinkAttachParams* params);
	virtual ~BobLinkAttach();

	s8 mode; // 0x34
	u8 pad35;
	s16 timer; // 0x36
	RwV3d at;  // 0x38
	RwV3d dir; // 0x44
	u32 flags; // 0x50
}; // 0x54

// bobLinkAttach (rel/bob_link_attach.cpp), inlined.
static inline void bobLinkAttachTo(BobLinkAttach* object)
{
	lbl_803EA4E8.mode     = 0;
	lbl_803EA4E8.unk04[0] = 0;
	lbl_803EA4E8.unk04[1] = 0;
	lbl_803EA4E8.unk04[2] = 0;
	lbl_803EA4E8.at.x     = object->at.x;
	lbl_803EA4E8.at.y     = object->at.y;
	lbl_803EA4E8.at.z     = object->at.z;
	lbl_803EA4E8.dir.x    = object->dir.x;
	lbl_803EA4E8.dir.y    = object->dir.y;
	lbl_803EA4E8.dir.z    = object->dir.z;
	fn_80131088(0xE, object);
	fn_8004D9B8(lbl_8042C1F8);
	fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), object->slotIn);
	object->linked = 1;
	object->mode   = 1;
}

inline BobLinkAttach::BobLinkAttach(BobLinkAttachParams* params)
{
	className = bobLinkAttachClassName;
	dispTime  = 0x54;
	timer     = params->timer;
	{
		RwV3d* from = params->at;

		at.x = from->x;
		at.y = from->y;
		at.z = from->z;
	}
	{
		RwV3d* from = params->dir;

		dir.x = from->x;
		dir.y = from->y;
		dir.z = from->z;
	}
	flags = params->flags;
	{
		s32 out = params->slotOut;

		slotIn  = params->slotIn;
		slotOut = out;
	}
	bobLinkAttachTo(this);
}

extern "C" void bobLinkAttachCreate(BobLinkAttachParams* params)
{
	new BobLinkAttach(params);
}
