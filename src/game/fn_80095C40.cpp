// Saves the three current match flags at 0x122 to 0x125 and clears them, then sets flag j again
// when any of the three words at 0x134 equals word j at 0x114.
struct Obj80095C40 {
	unsigned char pad0[0x114];
	unsigned int f114[3];
	unsigned char pad120[0x2];
	unsigned char f122[3];
	unsigned char f125[3];
	unsigned char pad128[0xC];
	unsigned int f134[3];
};
extern "C" {
void fn_80095C40(Obj80095C40* o)
{
	int i;
	int j;
	for (j = 0; j < 3; j++) {
		o->f125[j] = o->f122[j];
		o->f122[j] = 0;
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (o->f134[i] == o->f114[j]) {
				o->f122[j] = 1;
			}
		}
	}
}
}
