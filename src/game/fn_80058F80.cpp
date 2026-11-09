// Walks the 0x1C-byte records starting at p (until one whose first word is 0) and calls fn_80058FDC(a, first word, record + 4, record + 0x10, 0) on each.

extern "C" {
void fn_80058FDC(int, unsigned, void*, void*, int);

void fn_80058F80(int a, unsigned char* p)
{
	while (*(unsigned*)p != 0) {
		fn_80058FDC(a, *(unsigned*)p, p + 4, p + 0x10, 0);
		p += 0x1c;
	}
}
}
