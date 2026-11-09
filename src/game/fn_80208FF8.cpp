// Re-acquires the voice for the object after a voice-stolen callback.
struct Mgr80208FF8 {
	unsigned char pad0[0x3C];
	int f3C;
};
struct Obj80208FF8 {
	unsigned int f0;
	unsigned char pad4[0x30];
	unsigned int f34;
};
struct Voice80208FF8 {
	unsigned char pad0[0x14];
	Obj80208FF8* f14;
};

extern "C" {
extern Mgr80208FF8* lbl_8042CF6C;
extern char lbl_8023D5A8[];
unsigned int AXAcquireVoice(
    int a, void (*cb)(Voice80208FF8*), Obj80208FF8* o, int c, Mgr80208FF8* m);
void AXSetVoiceState(void* v, int s);
void MIXReleaseChannel(void* v);
int OSReport(const char* f, ...);

void fn_80208FF8(Voice80208FF8* v)
{
	Obj80208FF8* o = v->f14;
	AXSetVoiceState(v, 0);
	MIXReleaseChannel(v);
	o->f0          = o->f0 | 0x40000000;
	Mgr80208FF8* m = lbl_8042CF6C;
	int c          = m->f3C;
	m->f3C         = c - 1;
	o->f34         = AXAcquireVoice(0x1B, fn_80208FF8, o, c, m);
	if (o->f34 != 0) {
		o->f0 = o->f0 & 0xBFFFFFFF;
		AXSetVoiceState((void*)o->f34, 0);
		lbl_8042CF6C->f3C = lbl_8042CF6C->f3C + 1;
	} else {
		OSReport(lbl_8023D5A8);
	}
}
}
