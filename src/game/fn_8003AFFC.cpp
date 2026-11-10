// Looks up the 0x30-byte entry by index and forwards it to the handler.
struct S3AFFC {
	unsigned char pad[0xA];
	unsigned short s0a;
	unsigned char pad1[4];
	unsigned char* p10;
};

extern "C" {
int fn_8003B04C(S3AFFC* o, unsigned char* p, int c);

int fn_8003AFFC(S3AFFC* o, int i, int c)
{
	if (o->s0a <= i || i < 0 || o->p10 == 0) {
		return 0;
	}
	return fn_8003B04C(o, o->p10 + i * 0x30, c);
}
}
