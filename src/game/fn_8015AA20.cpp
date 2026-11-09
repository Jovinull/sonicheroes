// Calls fn_8015BB08 with the pointer stored at the given offset of the table lbl_8042C920 holds, and the object; returns the object.

extern "C" {
extern int lbl_8042C920;
void fn_8015BB08(void*, void*);

void* fn_8015AA20(void* o, int idx)
{
	void* p = *(void**)(idx + lbl_8042C920);
	if (p != 0) {
		fn_8015BB08(p, o);
	}
	return o;
}
}
