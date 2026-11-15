#include "types.h"

// TObjPtclCore::PDisp() (HYPOTHESIS, medium confidence from PS2 metadata): same references, order and size
// pattern as the PS2 PDisp, TDisp and Disp trio.
// Names are from PS2; the symbol keeps its address-based name.

class Node80065BF8
{
public:
	u8 pad0[4];
	s32 f4;
	u8 pad1[0x40];
	Node80065BF8* f48;
	u8 pad2[8];
	virtual void v0();
	virtual void v1();
};
struct Obj80065BF8 {
	u8 pad[0x28];
	Node80065BF8* f28;
};
struct Mode80065BF8 {
	u8 pad[0x20];
	s8 f20;
};

extern "C" {
extern u32 lbl_8042C2E0;
extern Mode80065BF8* lbl_8042C180;
void fn_80194234(s32, s32);

void fn_80065BF8(Obj80065BF8* o)
{
	s32 flags;
	Node80065BF8* n;
	Node80065BF8* p;

	if (lbl_8042C2E0 != 0) {
		p = o->f28;
		if (p != 0) {
			n = p;
			fn_80194234(0xe, 0);
			while (n != 0) {
				flags = n->f4;
				if (lbl_8042C180->f20 != 0 && (flags & 0x10000000) == 0) {
					n = n->f48;
				} else {
					if ((flags & 2) != 0) {
						n->v1();
					}
					n = n->f48;
				}
			}
			fn_80194234(0xe, 1);
		}
	}
}
}
