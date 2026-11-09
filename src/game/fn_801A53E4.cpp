// Unlinks the node from its doubly linked list when it is linked: stores the next pointer through the previous link and points the next node back.

extern "C" {
struct Node801A53E4 {
	int f0;
	unsigned f4;
	Node801A53E4* f8;
	int** fc;
};

void fn_801A53E4(Node801A53E4* o)
{
	if (o->f4 != 0) {
		*o->fc    = (int*)o->f8;
		o->f8->f4 = (int)o->fc;
	}
}
}
