// Resets the state fields according to the linked object type and runs the follow-up check.
struct In {
	unsigned char pad[0x154];
	int f154;
};
struct F {
	unsigned char pad[0x63a];
	short s63a;
	short s63c;
	unsigned char pad1[2];
	int s640;
	unsigned char pad2[0x9b8 - 0x644];
	In* in;
};

extern "C" {
int fn_800ECB48(F*, int);

int fn_800EE04C(F* o, int x)
{
	if (o->in->f154 != 9) {
		o->s63a = 0;
	} else {
		o->s63a = -10;
	}
	o->s63c = -1;
	o->s640 = 0;
	if (fn_800ECB48(o, x) == 0) {
		return 0;
	}
	return 1;
}
}
