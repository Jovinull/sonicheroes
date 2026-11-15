#include "game/object.h"

extern "C" {
int fn_8013F494(RwFrame* frame);
RwFrame* fn_8019E880(RwFrame* frame);
void fn_8019EB10(RwFrame* frame, void* callback, void* data);
int fn_8013E504(int, void*);

static inline void AssignFrames(RpHAnimHierarchy* h)
{
	int off;
	RwFrame* frame = h->parentFrame;
	int i;
	i   = 0;
	off = 0;
	while (i < h->numNodes) {
		int t              = fn_8013F494(frame);
		RpHAnimNodeInfo* e = (RpHAnimNodeInfo*)((u8*)h->pNodeInfo + off);
		if (e->nodeID == t) {
			e->pFrame = frame;
		}
		off += 0x10;
		i++;
	}
	fn_8019E880(frame);
	fn_8019EB10(frame, (void*)fn_8013E504, h);
}

RpHAnimHierarchy* fn_8013F3A4(RpHAnimHierarchy* h)
{
	AssignFrames(h);
	return h;
}
}
