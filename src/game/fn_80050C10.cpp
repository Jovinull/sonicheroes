// Resets a camera/effect config record to its default floats and counters.
struct Cfg80050C10 {
	float f0;
	float f4;
	float f8;
	float fC;
	float f10;
	float f14;
	int f18;
	int f1C;
	float f20;
	float f24;
};

extern "C" {
extern float lbl_8042D330;
extern float lbl_8042D350;
extern float lbl_8042D354;
extern float lbl_8042D358;

void fn_80050C10(Cfg80050C10* c)
{
	float z = lbl_8042D350;
	c->f0   = z;
	c->f4   = z;
	c->f8   = z;
	c->fC   = z;
	c->f10  = z;
	c->f14  = lbl_8042D330;
	c->f18  = 0;
	c->f1C  = 0x31C7;
	c->f20  = lbl_8042D354;
	c->f24  = lbl_8042D358;
}
}
