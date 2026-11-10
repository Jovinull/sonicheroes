// Releases an active voice's resources with interrupts disabled and clears its state.
struct Obj8020B810 {
	unsigned int f0;
	unsigned int f4;
	unsigned char pad8[0x98];
	unsigned int fA0;
};

extern "C" {
int OSDisableInterrupts();
void OSRestoreInterrupts(int e);
void fn_80206834(void* p);
void* memset(void* d, int c, unsigned int n);

int fn_8020B810(Obj8020B810* o)
{
	int e;
	if (!(o->f0 & 0x80000000)) {
		return -1;
	}
	e     = OSDisableInterrupts();
	o->f4 = o->f4 & 0xFFFFFFFD;
	if (o->fA0 != 0) {
		fn_80206834(&o->fA0);
		o->fA0 = 0;
	}
	memset((char*)o + 0x48, 0, 0x58);
	OSRestoreInterrupts(e);
	return 0;
}
}
