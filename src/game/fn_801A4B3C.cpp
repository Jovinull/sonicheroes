// Moves a node to the front of a list: unlinks it from its current owner, if any, records the
// new owner and links it right after the list head. Returns the node.
struct Link801A4B3C {
	Link801A4B3C* next;
	Link801A4B3C* prev;
};
struct List801A4B3C {
	unsigned char pad0[0x8];
	Link801A4B3C link;
};
struct Node801A4B3C {
	unsigned char pad0[0x4];
	List801A4B3C* owner;
	Link801A4B3C link;
};
extern "C" {
Node801A4B3C* fn_801A4B3C(List801A4B3C* list, Node801A4B3C* node)
{
	if (node->owner != 0) {
		node->link.prev->next = node->link.next;
		node->link.next->prev = node->link.prev;
	}
	node->owner           = list;
	node->link.next       = list->link.next;
	node->link.prev       = &list->link;
	list->link.next->prev = &node->link;
	list->link.next       = &node->link;
	return node;
}
}
