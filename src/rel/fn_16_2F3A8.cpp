struct Node {
	char pad0[0x2C];
	int f2C;
	char pad30[8];
	int cnt;
	Node* head;
};
extern "C" {
void fn_16_2FDC4(Node*, Node*);
void fn_16_2FDCC(Node*, Node*);
Node* fn_16_2FDD4(Node*);
void fn_16_2F3A8(Node* a, Node* b)
{
	Node* h;
	Node* t;
	if (a->head == 0) {
		a->head = b;
		fn_16_2FDC4(b, 0);
		fn_16_2FDCC(b, b);
	} else {
		h = a->head;
		t = fn_16_2FDD4(a->head);
		fn_16_2FDC4(t, b);
		fn_16_2FDCC(h, b);
		fn_16_2FDC4(b, 0);
		fn_16_2FDCC(b, t);
	}
	if (b->f2C == 1) {
		a->cnt++;
	}
}
}
