// Returns 1 and releases the entry when the stored key matches the given one.
extern "C" {
extern int lbl_8042C1F8;
unsigned int* fn_8004DCF4(int a, int b);
void fn_8004DE10(int a, int b);
int fn_8004E588(int a, int b);
int fn_8004E608(int a);

int fn_80130F78(int a, unsigned int b)
{
	if (fn_8004E608(lbl_8042C1F8) < a) {
		return 0;
	}
	if (fn_8004E588(lbl_8042C1F8, a) != 0x11) {
		return 0;
	}
	unsigned int* p = fn_8004DCF4(lbl_8042C1F8, a);
	if (p == 0) {
		return 0;
	}
	if (*p == b) {
		fn_8004DE10(lbl_8042C1F8, a);
		return 1;
	}
	return 0;
}
}
