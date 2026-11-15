// Clump callback (see fn_800BE118, which it installs): looks up the kind-6 object of a
// (fn_80146BC8) and, when the name (fn_80147910) of its fn_80146918 entry is one of the three names
// of lbl_80253CC0, finds the first of the eight entries of lbl_80304268 whose name (0x10 of the
// object at 0x34) matches the name of a's object index 1 (fn_80146990) and runs fn_80145EF8 on the
// kind-6 object with fn_800BE118 and that entry. Returns a. HYPOTHESIS: RenderWare frame/atomic
// iteration helpers; the roles are UNKNOWN.

struct Named800BDFC8 {
	unsigned char pad0[0x10];
	char name[1];
};

struct Entry800BDFC8 {
	unsigned char pad0[0x34];
	Named800BDFC8* f34;
};

extern "C" {
extern Entry800BDFC8* lbl_80304268[8];
extern void* lbl_80253CC0[3];
int strcmp(const char* a, const char* b);
void* fn_80146BC8(int a, int kind);
void* fn_80146918(void* p);
char* fn_80147910(void* p);
Named800BDFC8* fn_80146990(void* p, int index);
void fn_80145EF8(void* p, int unknown, int (*callback)(int), Entry800BDFC8* entry);
int fn_800BE118(int a);

static inline Entry800BDFC8* GetEntry800BDFC8(unsigned char i)
{
	if (i < 8) {
		return lbl_80304268[i];
	}
	return 0;
}

int fn_800BDFC8(int a)
{
	unsigned char i;
	void* p = fn_80146BC8(a, 6);
	if (p == 0) {
		return a;
	}
	char* name = fn_80147910(fn_80146918(p));
	for (i = 0; i <= 3; i++) {
		if (i == 3) {
			return a;
		}
		if (lbl_80253CC0[i] != 0 && strcmp(name, fn_80147910(lbl_80253CC0[i])) == 0) {
			break;
		}
	}
	Named800BDFC8* o = fn_80146990(p, 1);
	if (o != 0) {
		for (i = 0; i < 8; i++) {
			Entry800BDFC8* e = GetEntry800BDFC8(i);
			if (e != 0 && e->f34 != 0 && strcmp(o->name, e->f34->name) == 0) {
				fn_80145EF8(p, 0, fn_800BE118, e);
				break;
			}
		}
	}
	return a;
}
}
