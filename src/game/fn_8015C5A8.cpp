// Calls fn_8015C834 on the pointer stored at the given offset of the object, if any; returns the object.

extern "C" {
void fn_8015C834(void*);

void* fn_8015C5A8(unsigned char* o, int idx)
{
	void* p = *(void**)(o + idx);
	if (p != 0) {
		fn_8015C834(p);
	}
	return o;
}
}
