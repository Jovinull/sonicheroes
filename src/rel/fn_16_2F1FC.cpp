typedef unsigned int u32;
typedef int s32;
struct N {
	char pad[0x3C];
	N* next;
};
extern "C" N* fn_16_2FDAC(N*);
extern "C" s32 fn_16_2F1FC(register N* self)
{
	N* p;
	s32 n;
	for (p = self->next, n = 0; p != 0; p = fn_16_2FDAC(p)) {
		n++;
	}
	return n;
}
