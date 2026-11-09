// Stores the buffer and its size in the object, then zeroes the buffer.

extern "C" {
void* memset(void*, int, unsigned);
struct Obj80164A08 {
	void* a;
	int b;
};

void fn_80164A08(Obj80164A08* s, int unused, int size, void* buf)
{
	s->a = buf;
	s->b = size;
	memset(buf, 0, size);
}
}
