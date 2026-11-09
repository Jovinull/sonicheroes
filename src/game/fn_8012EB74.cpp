// Re-links node a into list b unless fn_801A4BBC already finds it (key at +0x10); returns a.

extern "C" {
void fn_801A4B3C(void*, void*);
void fn_801A4B8C(void*);
unsigned fn_801A4BBC(void*, void*);

void* fn_8012EB74(void* a, void* b)
{
	if (fn_801A4BBC(b, (unsigned char*)a + 0x10) == 0) {
		fn_801A4B8C(a);
		fn_801A4B3C(b, a);
	}
	return a;
}
}
