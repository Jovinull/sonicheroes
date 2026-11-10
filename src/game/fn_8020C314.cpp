// Opens a handle, queries the service and returns the result.
extern "C" {
int fn_80198000(int a, int b, int c);
int fn_80192F38(int a, int b, int c, int d);
int fn_8020C398(int a);
void fn_80197ED8(int a, int b);

int fn_8020C314(int a)
{
	int h = fn_80198000(2, 1, a);
	if (h == 0) {
		return 0;
	}
	if (fn_80192F38(h, 0x1B, 0, 0) == 0) {
		return 0;
	}
	int r = fn_8020C398(h);
	fn_80197ED8(h, 0);
	return r;
}
}
