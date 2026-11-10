// Fades the two sound-stream slots at a state change: when the mode is not 1, moves slot 0 from state 6 to 5 and slot 1 from 2/3/5/6 to 4; in mode 1 stops, un-pauses and resets slot 1 and clears its state.
struct Rec800CB5D8 {
	signed char c0;
	unsigned char pad1[7];
	int f8;
};
struct Entry800CB5D8 {
	unsigned char pad0[0x29];
	signed char c29;
	unsigned char pad2A[1];
	unsigned char f2B;
	unsigned char pad2C[0x18];
	int f44;
	unsigned char pad48[4];
	Rec800CB5D8* f4C;
};

extern "C" {
extern signed char lbl_8042C470;
extern Entry800CB5D8* lbl_8042B624[2];
void ADXT_Stop(int h);
void ADXT_Pause(int h, int on);
void ADXT_ResetEntry(int h);
void fn_800CA85C();

void fn_800CB5D8()
{
	Entry800CB5D8* e;
	Rec800CB5D8* r;
	if (lbl_8042C470 != 1) {
		if (lbl_8042B624[0] != 0 && lbl_8042B624[1] != 0) {
			switch (lbl_8042B624[0]->c29) {
				case 6:
					lbl_8042B624[0]->c29 = 5;
					break;
			}
			switch (lbl_8042B624[1]->c29) {
				case 2:
				case 3:
				case 5:
				case 6:
					lbl_8042B624[1]->c29 = 4;
					break;
			}
		}
	} else if (lbl_8042B624[0] != 0) {
		e = lbl_8042B624[1];
		if (e != 0) {
			ADXT_Stop(e->f44);
			ADXT_Pause(e->f44, 0);
			r = e->f4C;
			if (r != 0) {
				ADXT_ResetEntry(r->f8);
				r->c0 = -1;
			}
			e->c29 = 0;
			e->f2B = e->f2B & 0xFFFFFFFE;
			fn_800CA85C();
		}
	}
}
}
