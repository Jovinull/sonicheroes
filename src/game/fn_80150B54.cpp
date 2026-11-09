// Takes the entry at the given offset of the list block at lbl_8042C8C8 out of
// its doubly linked list and clears its three words. Returns its first argument.

extern "C" {
extern unsigned char* lbl_8042C8C8;
struct Link80150B54 {
	int unk0;
	Link80150B54* prev; // 0x04
	Link80150B54* next; // 0x08
};

int fn_80150B54(int self, int index)
{
	Link80150B54* e = (Link80150B54*)(index + (int)lbl_8042C8C8);

	e->next->unk0 = (int)e->prev;
	e->prev->prev = e->next;
	e->next       = 0;
	e->prev       = 0;
	e->unk0       = 0;
	return self;
}
}
