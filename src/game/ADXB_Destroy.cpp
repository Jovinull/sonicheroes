// Destroys the ADXPD decoder (handle at +8), clears the 0xD8-byte object and its state halfword; no-op for null.

extern "C" {
struct Obj_ADXB_Destroy {
	short s0;
	unsigned char pad[6];
	int f8;
};
void ADXPD_Destroy(int);
void* memset(void*, int, unsigned);

void ADXB_Destroy(Obj_ADXB_Destroy* o)
{
	int t;
	if (o != 0) {
		t     = o->f8;
		o->f8 = 0;
		ADXPD_Destroy(t);
		memset(o, 0, 0xd8);
		o->s0 = 0;
	}
}
}
