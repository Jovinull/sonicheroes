// Moves node n to the front of the list after head: unlinks it first (then notifies
// fn_80147288) when it is linked, relinks it after head and notifies fn_80147918. Returns head.
struct Link801470F4 {
	Link801470F4* next;
	Link801470F4* prev;
};
struct Node801470F4 {
	unsigned char pad0[0x28];
	Link801470F4 link;
};
extern "C" {
void fn_80147288(Node801470F4* n);
void fn_80147918(Node801470F4* n);
Link801470F4* fn_801470F4(Link801470F4* head, Node801470F4* n)
{
	if (n->link.next != 0) {
		n->link.prev->next = n->link.next;
		n->link.next->prev = n->link.prev;
		fn_80147288(n);
	}
	n->link.next     = head->next;
	n->link.prev     = head;
	head->next->prev = &n->link;
	head->next       = &n->link;
	fn_80147918(n);
	return head;
}
}
