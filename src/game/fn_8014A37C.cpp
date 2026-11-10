// Initializes the table entry at the given offset with the default callback and returns the offset.
struct S8014A37C {
	int f0;
	void* f4;
	int f8;
};

extern "C" {
extern int lbl_8042C86C;
void fn_8014A350();

int fn_8014A37C(int a)
{
	S8014A37C* s = (S8014A37C*)(a + lbl_8042C86C);
	s->f0        = 0;
	s->f8        = 0;
	s->f4        = (void*)fn_8014A350;
	return a;
}
}
