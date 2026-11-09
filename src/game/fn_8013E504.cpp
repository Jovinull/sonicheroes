// For each 16-byte entry of the list arg1 (count at +4, entries at +0x10) whose key equals fn_8013F494(arg0), stores arg0 at +0xC; then runs fn_8019E880 and re-registers itself with fn_8019EB10; returns arg0.

extern "C" {
struct Entry8013E504 {
	int f0;
	int f4;
	int f8;
	int fc;
};
struct List8013E504 {
	int f0;
	int f4;
	int f8;
	int fc;
	Entry8013E504* f10;
};
int fn_8013F494(int);
void fn_8019E880(int);
void fn_8019EB10(int, void*, void*);

int fn_8013E504(int a, List8013E504* l)
{
	int off = 0;
	int i   = 0;
	while (i < l->f4) {
		int t            = fn_8013F494(a);
		Entry8013E504* e = (Entry8013E504*)((unsigned char*)l->f10 + off);
		if (e->f0 == t) {
			e->fc = a;
		}
		off += 0x10;
		i++;
	}
	fn_8019E880(a);
	fn_8019EB10(a, (void*)fn_8013E504, l);
	return a;
}
}
