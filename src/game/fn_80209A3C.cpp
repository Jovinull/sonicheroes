// Frees the owned handle with interrupts disabled and clears the busy bit.
struct Obj80209A3C {
	unsigned int f0;
	unsigned char pad4[0x9C];
	unsigned int fA0;
};

extern "C" {
int OSDisableInterrupts();
void OSRestoreInterrupts(int s);
void fn_80206834(void* p);

void fn_80209A3C(Obj80209A3C* o)
{
	int s = OSDisableInterrupts();
	if (o->fA0 != 0) {
		fn_80206834(&o->fA0);
		o->fA0 = 0;
	}
	o->f0 = o->f0 & 0x7FFFFFFF;
	OSRestoreInterrupts(s);
}
}
