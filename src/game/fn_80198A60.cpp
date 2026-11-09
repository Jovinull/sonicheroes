// Walks the list at +0x10 (next at +0x30) for a node whose key at +8 equals arg1 and returns that node's id at 0; -1 when not found.

extern "C" {
struct Node80198A60 {
	int f0;
	unsigned char pad[4];
	unsigned f8;
	unsigned char pad1[0x30 - 0xc];
	Node80198A60* f30;
};
struct List80198A60 {
	unsigned char pad[0x10];
	Node80198A60* f10;
};

int fn_80198A60(List80198A60* h, unsigned k)
{
	Node80198A60* n;
	for (n = h->f10; n != 0; n = n->f30) {
		if (n->f8 == k) {
			return n->f0;
		}
	}
	return -1;
}
}
