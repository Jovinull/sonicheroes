// Finds the entry with the given key in the list at 0x10 and stores v in its word 0x18; returns its id, or -1.

extern "C" {
struct Node801982F4 {
	int f0;
	int f4;
	unsigned f8;
	int fc;
	int f10;
	int f14;
	int f18;
	int f1c;
	unsigned char pad[0x10];
	Node801982F4* next;
};
struct List801982F4 {
	unsigned char pad[0x10];
	Node801982F4* head;
};

int fn_801982F4(List801982F4* h, unsigned key, int v)
{
	Node801982F4* n = h->head;
	while (n != 0) {
		if (n->f8 == key) {
			break;
		}
		n = n->next;
	}
	if (n != 0) {
		n->f18 = v;
		return n->f0;
	}
	return -1;
}
}
