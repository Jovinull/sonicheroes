// Walks the owner's node list and, for every node whose key equals the given key, clears the key and releases the node's target: with flag 0x10000 resets the part (its chain handle and slot) and the target's field +0xC, with flag 0x20000 clears the target's field +0x2C.
struct Dep80065A74 {
	unsigned char pad0[0x20];
	int* f20;
};
struct Chain80065A74 {
	unsigned char pad0[0x18];
	Dep80065A74* f18;
};
struct Slot80065A74 {
	unsigned char pad0[0xC];
	unsigned int fC;
};
struct Part80065A74 {
	unsigned char pad0[0xC];
	Chain80065A74* fC;
	Slot80065A74* f10;
};
struct Tgt80065A74 {
	unsigned char pad0[0xC];
	int fC;
	unsigned char pad10[0x1C];
	int f2C;
};
struct Node80065A74 {
	unsigned char pad0[4];
	int f4;
	unsigned char pad8[0x24];
	Tgt80065A74* f2C;
	unsigned char pad30[4];
	Part80065A74* f34;
	unsigned int f38;
	unsigned char pad3C[0xC];
	Node80065A74* f48;
};
struct Owner80065A74 {
	unsigned char pad0[0x28];
	Node80065A74* f28;
};

extern "C" {
void fn_8015498C(int a, int b);

void fn_80065A74(Owner80065A74* o, unsigned int key)
{
	Tgt80065A74* t;
	Part80065A74* p;
	Node80065A74* n;
	Chain80065A74* c;
	Slot80065A74* s;
	int flags;
	for (n = o->f28; n != 0; n = n->f48) {
		if (key != 0 && key == n->f38) {
			n->f38 = 0;
			t      = n->f2C;
			if (t != 0) {
				flags = n->f4;
				if ((flags & 0x10000) != 0) {
					p = n->f34;
					if (p != 0) {
						c = p->fC;
						if (c != 0) {
							fn_8015498C(*c->f18->f20, 0);
						}
						s = p->f10;
						if (s != 0 && s->fC != 0) {
							s->fC = 0;
						}
					}
					t->fC = 0;
				} else if ((flags & 0x20000) != 0) {
					t->f2C = 0;
				}
			}
		}
	}
}
}
