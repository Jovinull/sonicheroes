typedef unsigned char u8;
typedef signed char s8;
typedef int s32;

struct Fn16Table {
	s32 count;
	void** clumps;
	s8* out;
};

extern "C" {
void fn_8015BB08(void* world, void* clump);
extern u8* lbl_8042C1D0;

void fn_16_4DFE8(Fn16Table* arg0, s32* arg1)
{
	s32 i;

	for (i = 0; i < arg0->count; i++) {
		if (arg1[i] >= 0) {
			fn_8015BB08(*(void**)(lbl_8042C1D0 + 0x7250 + arg1[i] * 4), arg0->clumps[i]);
		}
		arg0->out[i] = (s8)arg1[i];
	}
}
}
