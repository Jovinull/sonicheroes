// Returns the node of a list whose name (0x10) equals name, ignoring ASCII letter case, or null.
// The node link sits at 0x08 (see fn_801A4B3C).
struct Link801A4BBC {
	Link801A4BBC* next;
	Link801A4BBC* prev;
};
struct Node801A4BBC {
	unsigned char pad0[0x8];
	Link801A4BBC link;
	char name[1];
};
struct List801A4BBC {
	unsigned char pad0[0x8];
	Link801A4BBC link;
};
extern "C" {
static inline int NameEqual(const char* a, const char* b)
{
	for (; *a != 0 && *b != 0; a++, b++) {
		char ca = *a;
		char cb = *b;
		if (ca >= 'a' && ca <= 'z') {
			ca -= 0x20;
		}
		if (cb >= 'a' && cb <= 'z') {
			cb -= 0x20;
		}
		if (ca != cb) {
			return 0;
		}
	}
	if (*a == *b) {
		return 1;
	}
	return 0;
}

Node801A4BBC* fn_801A4BBC(List801A4BBC* l, const char* name)
{
	Link801A4BBC* k;
	Link801A4BBC* h = &l->link;
	for (k = h->next; k != h; k = k->next) {
		Node801A4BBC* n = (Node801A4BBC*)((unsigned char*)k - 8);
		if (n->name != 0 && NameEqual(n->name, name)) {
			return n;
		}
	}
	return 0;
}
}
