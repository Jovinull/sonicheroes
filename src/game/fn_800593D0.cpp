// Unlinks node arg2 from the doubly linked list whose head/tail are held at 0x30/0x430 of arg0 (indexed by arg1), fixing the head, tail and both neighbours.

extern "C" {
struct Node800593D0 {
	unsigned char pad[0x34];
	Node800593D0* n34;
	Node800593D0* n38;
};
struct Lists800593D0 {
	unsigned char pad[0x30];
	Node800593D0* h30[1];
	unsigned char pad1[0x430 - 0x34];
	Node800593D0* h430[1];
};

void fn_800593D0(Lists800593D0* h, unsigned char k, Node800593D0* n)
{
	if (h->h30[k] == n) {
		h->h30[k]->n38 = n->n38;
	}
	if (h->h430[k] == n) {
		h->h430[k]->n34 = n->n34;
	}
	if (n->n38 != 0) {
		n->n38->n34 = n->n34;
	}
	if (n->n34 != 0) {
		n->n34->n38 = n->n38;
	}
}
}
