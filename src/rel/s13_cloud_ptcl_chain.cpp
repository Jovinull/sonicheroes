#include "types.h"

// TObjS13CloudPtcl's UnlinkChain and LinkChain (the PS2 build's names): each
// cloud keeps its particles in a chain from its top particle; UnlinkChain takes
// the particle out of its cloud's chain and LinkChain puts it at the end.

struct TObjS13CloudPtcl;

struct TObjS13Cloud {
	TObjS13CloudPtcl* top; // 0x00

	TObjS13CloudPtcl* GetTopPtcl() { return top; }
	void SetTopPtcl(TObjS13CloudPtcl* ptcl) { top = ptcl; }
};

struct TObjS13CloudPtcl {
	u8 unk00[0xB8];
	TObjS13CloudPtcl* next; // 0xB8
	TObjS13Cloud* cloud;    // 0xBC

	TObjS13CloudPtcl* GetNext() { return next; }
	void SetNext(TObjS13CloudPtcl* ptcl) { next = ptcl; }
};

extern "C" void UnlinkChain__16TObjS13CloudPtclFv(TObjS13CloudPtcl* self)
{
	TObjS13CloudPtcl* ptcl;

	if (self->cloud == NULL) {
		return;
	}
	if (self->cloud->GetTopPtcl() == self) {
		self->cloud->SetTopPtcl(self->GetNext());
	} else {
		for (ptcl = self->cloud->GetTopPtcl(); ptcl->GetNext() != self; ptcl = ptcl->GetNext()) {
		}
		ptcl->SetNext(self->GetNext());
	}
	self->SetNext(NULL);
}

extern "C" void LinkChain__16TObjS13CloudPtclFv(TObjS13CloudPtcl* self)
{
	TObjS13CloudPtcl* ptcl;

	if (self->cloud == NULL) {
		return;
	}
	if (self->cloud->GetTopPtcl() == NULL) {
		self->cloud->SetTopPtcl(self);
	} else {
		for (ptcl = self->cloud->GetTopPtcl(); ptcl->GetNext() != NULL; ptcl = ptcl->GetNext()) {
		}
		ptcl->SetNext(self);
	}
	self->SetNext(NULL);
}
