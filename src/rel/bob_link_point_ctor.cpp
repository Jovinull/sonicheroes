#include "types.h"

// The constructor of the special stages' second sled link class (BobLinkPoint
// here; the classes have no PS2 names), in stage01D and stage07D. The base
// constructor (rel/bob_link_base.cpp has it as bobLinkCtor) is inlined: it
// lets go of the current link and becomes the current one, unlinked. Then the
// point, direction, timer and slots come from the caller's parameters, and the
// object attaches at once (as bobLinkAttachPoint does). Written as C++
// classes, as the inlined base constructor's copy of this needs.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct sAngle {
	s32 x, y, z;
} sAngle;

struct TObjectBase {
	const char* className; // 0x00
	u16 signal;            // 0x04
	u8 unk06[0x12];
};

class TObject : public TObjectBase
{
public:
	TObject(TObject* parent);
	virtual ~TObject();
	u8 unk1C[0x2];
	u16 dispTime; // 0x1E
	u8 unk20[0x8];
}; // 0x28

class BobLink;

extern "C" BobLink* bobLinkCurrent;
extern "C" const char* bobLinkClassName;
extern "C" void* lbl_8042C1F8;
extern "C" TObject* lbl_8042C110;
extern "C" void fn_80130F78(s32 kind, void* object);
extern "C" void fn_80131088(s32 kind, void* object);
extern "C" void fn_8004D99C(void* world);
extern "C" void fn_8004D9B8(void* world);
extern "C" void* fn_8004E608(void* world);
extern "C" void fn_8004DEC0(void* world, void* list, s32 slot);

class BobLink : public TObject
{
public:
	BobLink();
	virtual ~BobLink();

	s32 linked;  // 0x28
	s32 slotIn;  // 0x2C
	s32 slotOut; // 0x30
}; // 0x34

// Takes a linked object's slot out of the world's list and tells the sound
// side.
static inline void bobLinkSlotOut(BobLink* object)
{
	if (object->linked != 0) {
		fn_8004D99C(lbl_8042C1F8);
		fn_8004DEC0(lbl_8042C1F8, fn_8004E608(lbl_8042C1F8), object->slotOut);
		fn_80130F78(0xE, object);
		object->linked = 0;
	}
}

inline BobLink::BobLink()
    : TObject(lbl_8042C110)
{
	className = bobLinkClassName;
	dispTime  = 0x34;

	if (bobLinkCurrent != NULL) {
		BobLink* current = bobLinkCurrent;

		bobLinkSlotOut(current);
		if (current == bobLinkCurrent) {
			bobLinkCurrent = NULL;
		}
		current->signal |= 1;
	}

	linked         = 0;
	slotIn         = 0;
	slotOut        = 0;
	bobLinkCurrent = this;
}

typedef struct BobLinkTarget {
	s32 mode;     // 0x00
	s32 unk04[3]; // 0x04
	RwV3d dir;    // 0x10
	sAngle ang;   // 0x1C
	u8 unk28[0xC];
	RwV3d at; // 0x34
} BobLinkTarget;

typedef struct BobLinkPointParams {
	s16 timer; // 0x00
	u8 pad02[0x2];
	RwV3d* dir;  // 0x04
	RwV3d* at;   // 0x08
	s32 slotIn;  // 0x0C
	s32 slotOut; // 0x10
	s32 unk14;   // 0x14
} BobLinkPointParams;

extern "C" BobLinkTarget lbl_803EA4E8;
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
