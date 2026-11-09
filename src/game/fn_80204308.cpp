// Reads the entry count and the data block from the stream and attaches the decoded handle.
struct Obj80204308 {
	unsigned char pad0[0x24];
	unsigned int f24;
};

extern "C" {
unsigned int fn_80174308(int a);
int fn_80192F38(int a, int b, int* c, int* d);
unsigned int fn_80193884(int a, int* b, int c);

Obj80204308* fn_80204308(Obj80204308* o, int a)
{
	int sp10;
	int spC;
	int sp8;
	if (fn_80193884(a, &sp10, 4) == 0) {
		return 0;
	}
	if (sp10 > 0) {
		if (fn_80192F38(a, 0x1A5, &spC, &sp8) == 0) {
			return 0;
		}
		unsigned int r = fn_80174308(a);
		o->f24         = r;
		if (r == 0) {
			return 0;
		}
	}
	return o;
}
}
