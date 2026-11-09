// Returns 1 when the owner's linked record is in mode 3, or in mode 2 with its
// level byte (0x121) above 1; otherwise 0.

extern "C" {
struct In45D88 {
	unsigned char pad[0x140];
	int mode;
};
struct Out45D88 {
	unsigned char pad[0x9b8];
	In45D88* in;
};
struct Mid45D88 {
	unsigned char pad[0x121];
	signed char level;
};
int fn_80045D88(Out45D88* o)
{
	In45D88* in = o->in;
	if (in->mode == 3 || (in->mode == 2 && ((Mid45D88*)in)->level > 1)) {
		return 1;
	}
	return 0;
}
}
