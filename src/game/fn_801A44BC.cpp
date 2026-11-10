// Searches the manager's list for the first entry the lookup accepts.
struct Node801A44BC {
	Node801A44BC* next;
	Node801A44BC* prev;
	unsigned char pad8[8];
	unsigned int f10;
};

extern "C" {
extern char* lbl_8042C9A4;
extern int lbl_8042C9C4;
unsigned int fn_801A4BBC(void* a, int b);

unsigned int fn_801A44BC(int a)
{
	Node801A44BC* head;
	Node801A44BC* p;
	unsigned int r;
	head = (Node801A44BC*)(lbl_8042C9A4 + lbl_8042C9C4);
	if (head->f10 != 0) {
		return fn_801A4BBC((void*)head->f10, a);
	}
	p = head->next;
	while (p != head) {
		r = fn_801A4BBC((char*)p - 0x10, a);
		if (r != 0) {
			return r;
		}
		p = p->next;
	}
	return 0;
}
}
