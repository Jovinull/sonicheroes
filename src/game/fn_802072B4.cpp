// Stops the voice of the attached sound and clears its state flags.
struct Inner802072B4 {
	unsigned int f0;
	unsigned char pad4[4];
	int f8;
	unsigned char padC[0x28];
	unsigned int f34;
	unsigned char pad38[0xCC];
	int f104;
};
struct Obj802072B4 {
	unsigned char pad0[4];
	Inner802072B4* f4;
};

extern "C" {
void AXSetVoiceState(unsigned int v, int s);
void MIXReleaseChannel(unsigned int v);

void fn_802072B4(Obj802072B4* o)
{
	if (o != 0) {
		Inner802072B4* i = o->f4;
		if (i != 0) {
			i->f104 = 0;
			if (i->f34 != 0) {
				AXSetVoiceState(i->f34, 0);
				MIXReleaseChannel(i->f34);
			}
			i->f0 = i->f0 & 0x7FFFFFFF;
			i->f0 = i->f0 & 0xFFFFFFFE;
			i->f0 = i->f0 & 0xFFFFFFFD;
			i->f8 = 0;
		}
	}
}
}
