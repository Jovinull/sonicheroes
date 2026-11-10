// Moves the pending list into the active list and clears the slot fields.
struct N80197434 {
	N80197434* next;
	N80197434* prev;
};

extern "C" {
extern int lbl_8042C970;
extern char* lbl_8042C9A4;

void fn_80197434()
{
	N80197434* h     = *(N80197434**)(lbl_8042C9A4 + lbl_8042C970 + 0x24);
	N80197434* t     = *(N80197434**)(lbl_8042C9A4 + lbl_8042C970 + 0x20);
	N80197434* first = t->next;
	if (first != t) {
		if (h->next == h) {
			h->next       = first;
			h->next->prev = h;
			h->prev       = t->prev;
			h->prev->next = h;
			t->next       = t;
			t->prev       = t;
		} else {
			N80197434* q = h->prev;
			q->next      = first;
			first->prev  = q;
			N80197434* r = t->prev;
			r->next      = h;
			h->prev      = r;
			t->next      = t;
			t->prev      = t;
		}
	}
	((N80197434**)(lbl_8042C9A4 + lbl_8042C970))[0x24 / 4] = t;
	((N80197434**)(lbl_8042C9A4 + lbl_8042C970))[0x20 / 4] = h;
	((int*)(lbl_8042C9A4 + lbl_8042C970))[8 / 4]           = 0;
}
}
