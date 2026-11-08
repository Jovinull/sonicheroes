// Takes a node out of its doubly linked list (the links at 0x08 and 0x0C) and
// clears its linked flag; a node that is not linked is left alone. Returns the
// node.

extern "C" {
struct Node801A4B8C {
	int unk0;
	unsigned int linked; // 0x04
	Node801A4B8C* next;  // 0x08
	Node801A4B8C* prev;  // 0x0C
};

Node801A4B8C* fn_801A4B8C(Node801A4B8C* node)
{
	if (node->linked == 0) {
		return node;
	}
	node->linked       = 0;
	node->prev->unk0   = (int)node->next;
	node->next->linked = (int)node->prev;
	return node;
}
}
