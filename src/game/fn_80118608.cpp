// Returns the seconds part (0-59) of the frame counter at 0x14 (60 frames per second).

extern "C" {
struct Obj80118608 {
	unsigned char pad[0x14];
	int f14;
};

int fn_80118608(Obj80118608* o)
{
	return o->f14 % 60;
}
}
