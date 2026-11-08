// TObjS13CloudPtcl (the PS2 build's name), one particle of a stage 13 cloud,
// and TObjS13Cloud, the cloud whose chain of particles starts at its top
// particle. UnlinkChain and LinkChain are inline here, where the particle's
// constructor and destructor inline them: the top particle is read once into
// the walking pointer (`if ((ptcl = owner->GetTopPtcl()) == this)`), which is
// what gives the retail the cloud in r4 and the walking pointer in r3. The
// out-of-line copies are written separately in rel/s13_cloud_ptcl_chain.cpp.

#include "types.h"

#ifndef S13_CLOUD_PTCL_CHAIN
#define S13_CLOUD_PTCL_CHAIN inline
#endif

struct RwV3d;
struct sAngle;
struct TObjS13CloudPtcl;

struct PARTICLE_INSTANCE {
	u8 unk00[0xA];
	s16 frame; // 0x0A
	u8 unk0C[0x4];
	u32 color; // 0x10, alpha in the top byte
};

struct TObjS13Cloud {
	TObjS13CloudPtcl* top; // 0x00

	TObjS13CloudPtcl* GetTopPtcl() { return top; }
	void SetTopPtcl(TObjS13CloudPtcl* ptcl) { top = ptcl; }
};

struct TObjS13CloudPtcl {
	char* name; // 0x00
	u16 signal; // 0x04, 1: kill
	u8 unk06[0x12];
	void* vtable; // 0x18
	u8 unk1C[0x2];
	s16 unk1E; // 0x1E
	u8 unk20[0x8];
	u8 unk28[0x54]; // 0x28
	void* vtable2;  // 0x7C
	u8 unk80[0x30];
	void* instance;         // 0xB0
	u8 maxAlpha;            // 0xB4
	u8 unkB5;               // 0xB5
	s16 life;               // 0xB6
	TObjS13CloudPtcl* next; // 0xB8
	TObjS13Cloud* cloud;    // 0xBC

	TObjS13CloudPtcl* GetNext() { return next; }
	void SetNext(TObjS13CloudPtcl* ptcl) { next = ptcl; }
	void UnlinkChain();
	void LinkChain();
};

S13_CLOUD_PTCL_CHAIN void TObjS13CloudPtcl::UnlinkChain()
{
	TObjS13CloudPtcl* ptcl;

	if (cloud == NULL) {
		return;
	}
	if ((ptcl = cloud->GetTopPtcl()) == this) {
		cloud->SetTopPtcl(GetNext());
	} else {
		while (ptcl->GetNext() != this) {
			ptcl = ptcl->GetNext();
		}
		ptcl->SetNext(GetNext());
	}
	SetNext(NULL);
}

S13_CLOUD_PTCL_CHAIN void TObjS13CloudPtcl::LinkChain()
{
	TObjS13CloudPtcl* ptcl;

	if (cloud == NULL) {
		return;
	}
	if ((ptcl = cloud->GetTopPtcl()) == NULL) {
		cloud->SetTopPtcl(this);
	} else {
		while (ptcl->GetNext() != NULL) {
			ptcl = ptcl->GetNext();
		}
		ptcl->SetNext(this);
	}
	SetNext(NULL);
}
