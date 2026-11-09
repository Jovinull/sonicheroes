// Destroys the decoder handle at +4 (if any) and zeroes the 0x9C-byte object under the ADXCRS lock; no-op for null.

extern "C" {
struct Obj_ADXSJD_Destroy {
	unsigned char pad[4];
	unsigned f4;
};
void ADXB_Destroy(unsigned);
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
void* memset(void*, int, unsigned);

void ADXSJD_Destroy(Obj_ADXSJD_Destroy* o)
{
	if (o != 0) {
		if (o->f4 != 0) {
			unsigned t = o->f4;
			o->f4      = 0;
			ADXB_Destroy(t);
		}
		ADXCRS_Lock();
		memset(o, 0, 0x9c);
		ADXCRS_Unlock();
	}
}
}
