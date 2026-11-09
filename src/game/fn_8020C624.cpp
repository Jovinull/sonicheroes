// Counts the list nodes between the head and the node that points back to it.
struct Vt8020C624 {
	unsigned char pad0[8];
	int f8;
};
struct Obj8020C624 {
	Vt8020C624* f0;
	unsigned char pad4[0xC];
	unsigned int* f10;
};

extern "C" {
int fn_8020C624(Obj8020C624* o)
{
	unsigned int* head;
	unsigned int* p;
	int n = 0;
	int stride;
	stride = o->f0->f8;
	head   = o->f10;
	p      = head;
	while (*p != (unsigned int)head) {
		p = (unsigned int*)((char*)p + stride);
		n++;
	}
	return n;
}
}
