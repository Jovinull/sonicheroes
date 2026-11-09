// TObjS13CloudPtcl's destructor and constructor (the PS2 build's names),
// written out as the functions MWCC makes of them. The destructor takes the
// particle out of its cloud's chain before the particle base's destructor
// (fn_80062384) and frees it when asked to. The constructor builds the
// particle base (fn_80062A48) for the kind; without a particle instance it is
// killed at once, else it takes the kind's most alpha (kinds 0x32-0x35), clears
// its colour block, its life and its cloud, and joins the cloud's chain. The
// class is shared through s13_cloud_ptcl.inc.

#include "src/rel/s13_cloud_ptcl.inc"

class THeapCtrl
{
public:
	void Free(void* p);
};

extern "C" THeapCtrl* lbl_8042C148;
extern "C" char* CL_TObjS13CloudPtcl;
extern "C" u8 __vt__16TObjS13CloudPtcl[];
extern "C" const u8 s13CloudPtclAlphas[4];

extern "C" void fn_80062384(TObjS13CloudPtcl* self, s16 flag);
extern "C" void fn_80062A48(TObjS13CloudPtcl* self, u32 kind, RwV3d* pos, sAngle* ang);
extern "C" void fn_80064390(void* block, s32 size);

extern "C" TObjS13CloudPtcl* __dt__16TObjS13CloudPtclFv(TObjS13CloudPtcl* self, s16 flag)
{
	if (self != NULL) {
		self->vtable  = __vt__16TObjS13CloudPtcl;
		self->vtable2 = __vt__16TObjS13CloudPtcl + 0x2C;
		self->UnlinkChain();
		fn_80062384(self, 0);
		if (flag > 0) {
			lbl_8042C148->Free(self);
		}
	}
	return self;
}

extern "C" TObjS13CloudPtcl* __ct__16TObjS13CloudPtclFP12TObjS13CloudUisP5RwV3dP6sAngle(
    TObjS13CloudPtcl* self, TObjS13Cloud* cloud, u32 kind, s16 life, RwV3d* pos, sAngle* ang)
{
	s8 index;

	fn_80062A48(self, kind, pos, ang);
	self->vtable  = __vt__16TObjS13CloudPtcl;
	self->vtable2 = __vt__16TObjS13CloudPtcl + 0x2C;
	self->name    = CL_TObjS13CloudPtcl;
	self->unk1E   = 0xC0;
	index         = kind - 0x32;
	if (self->instance == NULL) {
		self->cloud = NULL;
		self->next  = NULL;
		self->signal |= 1;
		return self;
	}
	self->maxAlpha = s13CloudPtclAlphas[index];
	fn_80064390(self->unk28, 0x10);
	self->life  = life;
	self->cloud = cloud;
	self->LinkChain();
	return self;
}
