// Sums the result of the per-entry handler over all entries, last to first.
extern "C" {
int fn_801AD620(int a, unsigned char b);
void fn_801AD880(int* p, int a, int b);

int fn_801AD750(int a)
{
	int sp8;
	int n = 0;
	fn_801AD880(&sp8, a, 0);
	while (sp8-- != 0) {
		n += fn_801AD620(a, (unsigned char)sp8);
	}
	return n;
}
}
