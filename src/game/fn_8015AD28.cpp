// Calls fn_8015BD84 with the pointer stored at the given offset of the table lbl_8042C924 holds, and the object; returns the object.

extern "C" {
extern int lbl_8042C924;
void fn_8015BD84(void*, void*);

void* fn_8015AD28(void* o, int idx)
{
	void* p = *(void**)(idx + lbl_8042C924);
	if (p != 0) {
		fn_8015BD84(p, o);
	}
	return o;
}
}
