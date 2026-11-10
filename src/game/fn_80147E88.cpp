// Reads a presence flag from the stream and, when set, opens the stream and stores the resolved object into *out (0 when absent); reports errors other than 0x16 through fn_80193FE8 and returns 0, otherwise returns the stream.
struct Err80147E88 {
	int a;
	int b;
};

extern "C" {
int fn_80192F38(int h, int a, int b, int c);
unsigned int fn_80193884(int h, int* out, int n);
void fn_80193FE8(Err80147E88* e);
void fn_80194048(Err80147E88* e);
unsigned int fn_8019ADB4(int h);

int fn_80147E88(int h, unsigned int* out)
{
	Err80147E88 e;
	int sp8;
	if (fn_80193884(h, &sp8, 4) == 0) {
		return 0;
	}
	if (sp8 != 0) {
		if (fn_80192F38(h, 6, 0, 0) == 0) {
			return 0;
		}
		fn_80194048(&e);
		*out = fn_8019ADB4(h);
		if (*out == 0) {
			fn_80194048(&e);
			if ((unsigned int)(e.b + 0x80000000) != 0 && e.b != 0x16) {
				fn_80193FE8(&e);
				return 0;
			}
		}
	} else {
		*out = 0;
	}
	return h;
}
}
