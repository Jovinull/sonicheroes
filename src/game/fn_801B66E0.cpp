// Allocates a list node (fn_801B3B40, 8 bytes), makes it the head if the list is empty, and stores arg0 and arg0's field at +8 in it.

extern "C" {
struct Node801B66E0 {
	void* f0;
	int f4;
};
struct Src801B66E0 {
	unsigned char pad[8];
	int f8;
};
Node801B66E0* fn_801B3B40(int);

void fn_801B66E0(Src801B66E0* a, int unused, Node801B66E0** pp)
{
	Node801B66E0* t = fn_801B3B40(8);
	if (*pp == 0) {
		*pp = t;
	}
	t->f0 = a;
	t->f4 = a->f8;
}
}
