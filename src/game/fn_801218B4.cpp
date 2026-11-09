// Sets word 0x28, calls fn_8005FD8C(node, a) on every node of the list at 0x50 (next at 0xD0) and sets bit 0 of the halfword at 4.

extern "C" {
struct Node801218B4 {
	unsigned char pad[0xd0];
	Node801218B4* fd0;
};
struct Obj801218B4 {
	unsigned char pad[4];
	unsigned short f4;
	unsigned char pad1[0x28 - 6];
	int f28;
	unsigned char pad2[0x50 - 0x2c];
	Node801218B4* f50;
};
void fn_8005FD8C(void*, int);

void fn_801218B4(Obj801218B4* o, int a)
{
	Node801218B4* n;
	o->f28 = 1;
	n      = o->f50;
	while (n != 0) {
		fn_8005FD8C(n, a);
		n = n->fd0;
	}
	o->f4 |= 1;
}
}
