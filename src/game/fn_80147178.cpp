// Unlinks node n from its list when it is linked (then notifies fn_80147288); returns n. The
// unlink half of fn_801470F4.
struct Link80147178 {
	Link80147178* next;
	Link80147178* prev;
};

struct Node80147178 {
	unsigned char pad0[0x28];
	Link80147178 link;
};

extern "C" {
void fn_80147288(Node80147178* n);

Node80147178* fn_80147178(Node80147178* n)
{
	if (n->link.next != 0) {
		n->link.prev->next = n->link.next;
		n->link.next->prev = n->link.prev;
		fn_80147288(n);
	}
	return n;
}
}
