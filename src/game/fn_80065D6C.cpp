#include "types.h"

// TObjPtclCore::Disp() (HYPOTHESIS, medium confidence from PS2 metadata): same references, order and size
// pattern as the PS2 PDisp, TDisp and Disp trio.
// Names are from PS2; the symbol keeps its address-based name.

extern "C" {
class Node80065D6C;
class NodeHeader80065D6C
{
public:
	u8 pad0[4];
	s32 f4;
	u8 pad8[0x40];
	Node80065D6C* f48;
	u8 pad4C[8];
};
class Node80065D6C : public NodeHeader80065D6C
{
public:
	virtual void MoveManager();
	virtual void DispManager();
};
struct Owner80065D6C {
	u8 pad0[0x28];
	Node80065D6C* f28;
};
struct MutekiGameMode80065D6C {
	u8 pad[0x20];
	s8 hidden;
};

extern void* lbl_8042C2E0;
extern MutekiGameMode80065D6C* lbl_8042C180;
s32 fn_80194234(s32, void*);

void fn_80065D6C(Owner80065D6C* o)
{
	Node80065D6C* n;
	s32 flags;

	if (lbl_8042C2E0 != 0 && o->f28 != 0) {
		n = o->f28;
		fn_80194234(0xE, (void*)0);
		while (n != 0) {
			flags = n->f4;
			if (lbl_8042C180->hidden != 0 && (flags & 0x10000000) == 0) {
				n = n->f48;
				continue;
			}
			if ((flags & 0x1E) == 0) {
				n->DispManager();
			}
			n = n->f48;
		}
		fn_80194234(0xE, (void*)1);
	}
}
}
