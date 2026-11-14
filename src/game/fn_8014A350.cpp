// Pops the node at base + lbl_8042C868 (its successor at 0x10 replaces it) and returns t minus
// the node's time at 0x08, clamped to at least lbl_8042F2B0 (0).
// NonMatching: 5 word diffs, FP register numbering only. Written with the literal 0.0f it matches
// exactly, so the original used a literal pooled in its TU's .sdata2; this per-function unit does
// not own that constant and has to reference it.
struct Node8014A350 {
	unsigned char pad0[0x8];
	float time; // 0x08
	unsigned char padC[0x4];
	Node8014A350* next; // 0x10
};

extern "C" {
extern int lbl_8042C868;
extern const float lbl_8042F2B0;

float fn_8014A350(unsigned char* base, float t)
{
	Node8014A350* n = *(Node8014A350**)(base + lbl_8042C868);
	float d         = t - n->time;
	if (d < lbl_8042F2B0) {
		d = lbl_8042F2B0;
	}
	*(Node8014A350**)(base + lbl_8042C868) = n->next;
	return d;
}
}
