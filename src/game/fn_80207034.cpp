// Releases the mixer channel of a voice that is active and not locked.
struct Obj80207034 {
	unsigned int f0;
	unsigned char pad4[0x30];
	unsigned int f34;
};

extern "C" {
void AXSetVoiceState(unsigned int v, int s);
void MIXReleaseChannel(unsigned int v);

void fn_80207034(Obj80207034* o)
{
	if (o != 0 && o->f34 != 0) {
		unsigned int t = o->f0;
		if ((t & 0x80000000) && !(t & 0x40000000)) {
			o->f0 = t | 1;
			AXSetVoiceState(o->f34, 0);
			MIXReleaseChannel(o->f34);
		}
	}
}
}
