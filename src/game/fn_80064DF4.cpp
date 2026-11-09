// Walks the linked list starting at 0x4C and calls fn_80064078(node, 1) on each node.

extern "C" {
struct Node80064DF4 {
	Node80064DF4* next;
};
struct Obj80064DF4 {
	unsigned char pad[0x4c];
	Node80064DF4* head;
};
void fn_80064078(Node80064DF4*, int);

void fn_80064DF4(Obj80064DF4* o)
{
	Node80064DF4* n = o->head;
	while (n != 0) {
		Node80064DF4* next = n->next;
		fn_80064078(n, 1);
		n = next;
	}
}
}
