// Finds the entry with the given key in the list at 0x10 and stores v in its word 0x1C; returns its id, or -1.

extern "C" {
struct Node80198330 {
	int f0;
	int f4;
	unsigned f8;
	int fc;
	int f10;
	int f14;
	int f18;
	int f1c;
	unsigned char pad[0x10];
	Node80198330* next;
};
struct List80198330 {
	unsigned char pad[0x10];
	Node80198330* head;
};

int fn_80198330(List80198330* h, unsigned key, int v)
{
	Node80198330* n = h->head;
	while (n != 0) {
		if (n->f8 == key) {
			break;
		}
		n = n->next;
	}
	if (n != 0) {
		n->f1c = v;
		return n->f0;
	}
	return -1;
}
}
