// Drops one reference of the shared pool lbl_8028D1E8: at zero tears down via fn_80142DB8; destroys the free list at +8 if present; returns arg0.

extern "C" {
struct Pool80147928 {
	int f0;
	int f4;
	void* f8;
};
extern Pool80147928 lbl_8028D1E8;
void RwFreeListDestroy(void*);
void fn_80142DB8(void);

void* fn_80147928(void* a)
{
	lbl_8028D1E8.f4 = lbl_8028D1E8.f4 - 1;
	if (lbl_8028D1E8.f4 == 0) {
		fn_80142DB8();
	}
	if (lbl_8028D1E8.f8 != 0) {
		RwFreeListDestroy(lbl_8028D1E8.f8);
		lbl_8028D1E8.f8 = 0;
	}
	return a;
}
}
