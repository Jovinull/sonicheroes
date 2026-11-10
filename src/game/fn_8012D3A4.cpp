// Formats the entry's template with the current language string and passes the result to the layout helpers.
struct G8012D3A4 {
	unsigned char pad0[0x13];
	signed char f13;
};

extern "C" {
extern G8012D3A4* lbl_8042C180;
extern int lbl_8028A2A0[];
int sprintf(char* s, const char* f, ...);
int fn_800426E0(char* s, int* out);
void fn_8012D080(int* a, void* out);
void fn_800426B4(int v);

void fn_8012D3A4(int* a)
{
	struct {
		int s8;
		char sC[8];
		int s14;
		int s18;
	} f;
	char buf[0x100];
	if (a != 0) {
		int fmt = *a;
		int v   = lbl_8042C180->f13;
		if (v < 0 || v >= 7) {
			v = 1;
		}
		sprintf(buf, (const char*)fmt, lbl_8028A2A0[v]);
		f.s14 = fn_800426E0(buf, &f.s8);
		f.s18 = f.s8;
		fn_8012D080(a, f.sC);
		fn_800426B4(f.s14);
	}
}
}
