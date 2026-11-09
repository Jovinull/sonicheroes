// Updates the ADX stream state of the music slot: reads the stream status into word 0x34 and, when a playing slot (state 1) has stopped or ended, resets it.

extern "C" {
struct Slot800C9AEC {
	unsigned char pad[0x29];
	signed char c29;
	signed char b2a;
	unsigned char b2b;
	int f2c;
	int f30;
	int f34;
	unsigned char pad1[0x3c - 0x38];
	int f3c;
};
int ADXT_GetStat(int);

void fn_800C9AEC(Slot800C9AEC* o)
{
	switch (o->c29) {
		case 0:
			o->f34 = ADXT_GetStat(o->f3c);
			return;
		case 1:
			o->f34 = ADXT_GetStat(o->f3c);
			if (o->f34 == 0 || o->f34 == 5) {
				o->f2c = -1;
				o->f30 = -1;
				o->b2a = -1;
				o->c29 = 0;
			}
			return;
	}
}
}
