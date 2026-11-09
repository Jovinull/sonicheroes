// Destructor (C_COLLI): for each of the 0x30-byte headers at +0x10 (count at +0xA) drops one reference on the shared reactor at +0x20 (destroying it at zero, or just forgetting it when the flag 0x8000 at +8 is set), frees the header array with operator delete[] when that flag is set, and frees the object when flags > 0; returns the object.

extern "C" {
void Destruct_CCL_REACTOR__FP8CCL_INFO(void*);
void __dl__FPv(void*);
void __dla__FPv(void*);
struct Head7C_COLLI_dt {
	unsigned char pad[0x20];
	int* f20;
	unsigned char pad1[0xc];
};
struct Obj7C_COLLI_dt {
	unsigned char pad[8];
	unsigned short s8;
	unsigned short sa;
	unsigned char pad2[4];
	Head7C_COLLI_dt* f10;
};

Obj7C_COLLI_dt* __dt__7C_COLLIFv(Obj7C_COLLI_dt* o, short flags)
{
	Head7C_COLLI_dt* h;
	int n;
	int z;
	if (o != 0) {
		if (o->f10 != 0) {
			h = o->f10;
			n = o->sa;
			z = 0;
			while (n > 0) {
				int* t = h->f20;
				if (t != 0) {
					int v = *t - 1;
					*t    = v;
					if (v <= 0) {
						Destruct_CCL_REACTOR__FP8CCL_INFO(h);
						h->f20 = (int*)z;
					} else if ((o->s8 & 0x8000) != 0) {
						h->f20 = (int*)z;
					}
				}
				h++;
				n--;
			}
		}
		if ((o->s8 & 0x8000) != 0 && o->f10 != 0) {
			__dla__FPv(o->f10);
			o->f10 = 0;
		}
		if (flags > 0) {
			__dl__FPv(o);
		}
	}
	return o;
}
}
