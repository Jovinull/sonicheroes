// Returns the frame count of entry k (8-byte entries) of the morph table at +4.

extern "C" {
struct Anim {
	unsigned char pad[4];
	int* f4;
};

int RpDMorphAnimationGetNumFrames(Anim* a, int k)
{
	return *(int*)((unsigned char*)a->f4 + k * 8);
}
}
