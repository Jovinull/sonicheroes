// Returns the int field at +0x0.

extern "C" {
struct ObjRpDMorphAnimationGetNumDMorphTargets {
	int f;
};

int RpDMorphAnimationGetNumDMorphTargets(ObjRpDMorphAnimationGetNumDMorphTargets* o)
{
	return o->f;
}
}
