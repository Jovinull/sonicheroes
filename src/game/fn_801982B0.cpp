// Finds the entry with the given key in the list at 0x10 and stores a, b and c in its words 0xC, 0x10 and 0x14; returns its id, or -1.

extern "C" {
struct Node801982B0 {
	int f0;
	int f4;
	unsigned f8;
	int fc;
	int f10;
	int f14;
	int f18;
	int f1c;
	unsigned char pad[0x10];
	Node801982B0* next;
};
struct List801982B0 {
	unsigned char pad[0x10];
	Node801982B0* head;
};

int fn_801982B0(List801982B0* h, unsigned key, int a, int b, int c)
{
	Node801982B0* n = h->head;
	while (n != 0) {
		if (n->f8 == key) {
			break;
		}
		n = n->next;
	}
	if (n != 0) {
		n->fc  = a;
		n->f10 = b;
		n->f14 = c;
		return n->f0;
	}
	return -1;
}
}
