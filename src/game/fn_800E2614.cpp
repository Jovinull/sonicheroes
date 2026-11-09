// Returns bit mask 4 of the signed byte 0xa of the 16-byte entry lbl_802B0310[i].

extern "C" {
struct Entry800E2614 {
	unsigned char pad[9];
	signed char b9;
	signed char ba;
	unsigned char pad1[5];
};
extern Entry800E2614 lbl_802B0310[];

int fn_800E2614(int i)
{
	return lbl_802B0310[i].ba & 4;
}
}
