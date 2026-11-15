#include "types.h"

extern "C" {
extern void* lbl_8042C2E0;

class Node80065E20;
class NodeHeader80065E20
{
public:
	u8 pad0[0x48];
	Node80065E20* f48;
	u8 pad4C[8];
};
class Node80065E20 : public NodeHeader80065E20
{
public:
	virtual void MoveManager();
};
struct Owner80065E20 {
	u8 pad0[0x28];
	Node80065E20* f28;
};

void fn_80065E20(Owner80065E20* o)
{
	Node80065E20* n;

	if (lbl_8042C2E0 != 0 && o->f28 != 0) {
		for (n = o->f28; n != 0; n = n->f48) {
			n->MoveManager();
		}
	}
}
}
