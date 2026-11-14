// Looks up the kind-6 object of a (fn_80146BC8, then fn_80146990 index 1) and marks the first
// of the eight entries of lbl_80304268 whose name (0x10 of the object at 0x34) matches the
// object's own name (0x10) and that is not yet marked (word 0x3C set to 1). Returns a.
struct Named800BE118 {
	unsigned char pad0[0x10];
	char name[1];
};

struct Entry800BE118 {
	unsigned char pad0[0x34];
	Named800BE118* f34;
	unsigned char pad38[0x4];
	int f3C;
};

extern "C" {
extern Entry800BE118* lbl_80304268[8];
int strcmp(const char* a, const char* b);
void* fn_80146BC8(int a, int kind);
Named800BE118* fn_80146990(void* p, int index);

static inline Entry800BE118* GetEntry800BE118(unsigned char i)
{
	if (i < 8) {
		return lbl_80304268[i];
	}
	return 0;
}

int fn_800BE118(int a)
{
	Named800BE118* o = fn_80146990(fn_80146BC8(a, 6), 1);
	if (o != 0) {
		unsigned char i;
		for (i = 0; i < 8; i++) {
			Entry800BE118* e = GetEntry800BE118(i);
			if (e != 0 && e->f34 != 0 && e->f3C != 1 && strcmp(o->name, e->f34->name) == 0) {
				e->f3C = 1;
				break;
			}
		}
	}
	return a;
}
}
