// Starts the fighter's state 0x51: sets the mode, a field at 0x8AE of its sub-record, flag bits 0x500, and calls fn_800E12FC on the two sub-records.

extern "C" {
struct Fighter80044110 {
	unsigned char pad[0x6f0];
	short mode;
	unsigned char pad1[4];
	short flags;
};
void fn_800EF23C();
void fn_800E12FC(void*, void*);

void fn_80044110(Fighter80044110* f)
{
	fn_800EF23C();
	f->mode              = 0x51;
	unsigned char* t     = (unsigned char*)f + 0x760;
	*(short*)(t + 0x14e) = 9;
	f->flags |= 0x500;
	fn_800E12FC((unsigned char*)f + 0x720, t);
}
}
