extern "C" {

struct Obj_ADXB_SetAhxInSj {
	unsigned char pad[0xb0];
	void* fB0;
};

extern void (*ahxsetsjifunc[])(void*, void*);

void ADXB_SetAhxInSj(Obj_ADXB_SetAhxInSj* o, void* arg)
{
	if (o->fB0 != 0) {
		(*ahxsetsjifunc)(o->fB0, arg);
	}
}
}
