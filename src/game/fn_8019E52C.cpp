// Runs fn_80198E04 on the list lbl_802905F8 with the node; if its linked bits (3) are set, relinks the neighbours (+8 / +0xC) to each other.

extern "C" {
struct Link8019E52C {
	void* f0;
	void* f4;
};
struct Node8019E52C {
	unsigned char pad[3];
	unsigned char c3;
	Link8019E52C* f4;
	Link8019E52C* f8;
	Link8019E52C* fc;
};
extern unsigned char lbl_802905F8[];
void fn_80198E04(void*, void*);

void fn_8019E52C(Node8019E52C* o)
{
	fn_80198E04(lbl_802905F8, o);
	if (o->c3 & 3) {
		((Link8019E52C*)o->fc)->f0 = o->f8;
		((Link8019E52C*)o->f8)->f4 = o->fc;
	}
}
}
