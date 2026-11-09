// Returns the seconds part (0-59) of a frame counter running at 60 frames per
// second.

extern "C" {
struct Timer80118634 {
	unsigned char pad[0x14];
	int frames; // 0x14
};

int fn_80118634(Timer80118634* t)
{
	return (t->frames / 60) % 60;
}
}
