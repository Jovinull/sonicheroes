// Returns 1 when the common check passes and the player's measured value is below lbl_8042D228 while the sampled value exceeds the stored limit.
struct Sub8004583C {
	unsigned char pad0[0x60];
	unsigned char f60[0x50];
	float fB0;
	unsigned char padB4[0x34];
	float fE8;
};
struct Pl8004583C {
	unsigned char pad0[0x6F0];
	unsigned char f6F0[0x70];
	Sub8004583C sub;
};

extern "C" {
extern float lbl_8042D228;
int fn_800E27D8(void* a, void* b, int c, int d);
float fn_801991B4(void* p);

int fn_8004583C(Pl8004583C* p)
{
	Sub8004583C* s = &p->sub;
	if (fn_800E27D8(p->f6F0, s, 0, 0) != 0) {
		return 0;
	}
	if (s->fB0 < lbl_8042D228 && fn_801991B4(s->f60) > s->fE8) {
		return 1;
	}
	return 0;
}
}
