// Pushes a value into the ring buffer with interrupts disabled.
struct Obj802099B0 {
	unsigned char pad0[0x524];
	int buf[0x400];
	int pad1524;
	int f1528;
	int f152C;
};

extern "C" {
int OSDisableInterrupts();
void OSRestoreInterrupts(int e);

void fn_802099B0(Obj802099B0* o, int v)
{
	int e = OSDisableInterrupts();
	if (o->f152C < 0x400) {
		o->buf[o->f1528] = v;
		o->f152C++;
		o->f1528++;
		o->f1528 = o->f1528 % 0x400;
	}
	OSRestoreInterrupts(e);
}
}
