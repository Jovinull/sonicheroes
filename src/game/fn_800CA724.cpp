// If mode byte lbl_8042C470 is 2 and the pointer at 4C of lbl_8042B624's object is set, stores the (0-8) value in byte 1 of its record and in byte 0 when that is still negative.

extern "C" {
struct Rec800CA724 {
	signed char b0;
	signed char b1;
};
struct Holder800CA724 {
	unsigned char pad[4];
	Rec800CA724* n;
};
extern Holder800CA724* lbl_8042B624;
extern unsigned char lbl_8042C470;

void fn_800CA724(signed char v)
{
	Rec800CA724* t;
	if ((signed char)lbl_8042C470 == 2 && lbl_8042B624 != 0) {
		t = (Rec800CA724*)*(void**)((unsigned char*)lbl_8042B624 + 0x4c);
		if (t != 0 && v >= 0 && v <= 8) {
			if (t->b0 < 0) {
				t->b0 = v;
			}
			t->b1 = v;
		}
	}
}
}
