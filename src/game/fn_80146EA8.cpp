// Reads an entry count from the stream and loads that many entries (fn_80147528) into the list built by fn_80146FAC, releasing the list and returning 0 on any failure; returns the list.
extern "C" {
int fn_80192F38(int h, int a, int* b, int* c);
unsigned int fn_801979AC(int h, unsigned int* out, int n);
void fn_80193270(unsigned int* p, int n);
int fn_80146FAC();
void fn_8014705C(int a);
void fn_801470F4(int a, int b);
void fn_80147288(int a);
int fn_80147528(int h);

int fn_80146EA8(int h)
{
	int sp10;
	int spC;
	unsigned int sp8;
	int a;
	int b;
	if (fn_80192F38(h, 1, &sp10, &spC) == 0) {
		return 0;
	}
	if (fn_801979AC(h, &sp8, sp10) == 0) {
		return 0;
	}
	fn_80193270(&sp8, 4);
	a = fn_80146FAC();
	if (a == 0) {
		return 0;
	}
	while (sp8-- != 0) {
		if (fn_80192F38(h, 0x20, &sp10, &spC) == 0 || (b = fn_80147528(h)) == 0) {
			fn_8014705C(a);
			return 0;
		}
		fn_801470F4(a, b);
		fn_80147288(b);
	}
	return a;
}
}
