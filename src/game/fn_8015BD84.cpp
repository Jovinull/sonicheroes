// Attaches node n to owner o: records o at n + lbl_8042C924, then links n's link (0x34) at the
// front of o's list at 0x3C when n's byte 1 is below 0x80; otherwise releases n's handle at 0x04
// (fn_8019E880) when set and links it at the front of o's list at 0x34. Returns o.
struct Link8015BD84 {
	Link8015BD84* next;
	Link8015BD84* prev;
};

struct Node8015BD84 {
	unsigned char f0;
	unsigned char f1;
	unsigned char pad2[0x2];
	void* f4;
	unsigned char pad8[0x34 - 0x8];
	Link8015BD84 link; // 0x34
};

extern "C" {
extern int lbl_8042C924;
void fn_8019E880(void* h);

static inline void LinkFront8015BD84(Link8015BD84* head, Link8015BD84* l)
{
	l->next          = head->next;
	l->prev          = head;
	head->next->prev = l;
	head->next       = l;
}

unsigned char* fn_8015BD84(unsigned char* o, Node8015BD84* n)
{
	*(unsigned char**)((unsigned char*)n + lbl_8042C924) = o;
	if (n->f1 < 0x80) {
		LinkFront8015BD84((Link8015BD84*)(o + 0x3C), &n->link);
	} else {
		if (n->f4 != 0) {
			fn_8019E880(n->f4);
		}
		LinkFront8015BD84((Link8015BD84*)(o + 0x34), &n->link);
	}
	return o;
}
}
