// Releases every node of the manager's list and resets the list head.
struct Node801A2EF4 {
	Node801A2EF4* next;
	Node801A2EF4* prev;
};
struct G801A2EF4 {
	unsigned char pad0[0xBC];
	Node801A2EF4* fBC;
	Node801A2EF4* fC0;
};

extern "C" {
extern G801A2EF4* lbl_8042C9A4;
void fn_801A2DA8(void* p);

int fn_801A2EF4()
{
	Node801A2EF4* head;
	Node801A2EF4* p;
	p    = lbl_8042C9A4->fBC;
	head = (Node801A2EF4*)((char*)lbl_8042C9A4 + 0xBC);
	while (p != head) {
		fn_801A2DA8((char*)p - 8);
		p = p->next;
	}
	Node801A2EF4* h   = (Node801A2EF4*)((char*)lbl_8042C9A4 + 0xBC);
	h->next           = h;
	lbl_8042C9A4->fC0 = (Node801A2EF4*)((char*)lbl_8042C9A4 + 0xBC);
	return 1;
}
}
