// Advances the volume envelope of a voice record by one update unless bit 0 of its flags is set.
// State 0 (attack) raises the level (0xAC) by 0xC8 up to 1; state 1 (decay) lowers it by 0xCC
// until the decibel value (0xB0) reaches the sustain value at 0xC4; states 2-3 release by 0xD0
// and states 4-5 by 0xD4, both down to 0. The decibel value tracks -(96 - 96 * level), and the
// time at 0xA8 advances every call. The record layout is inferred from this code.
// NonMatching: same 124 instructions and control flow, 40 word diffs in floating-point register
// numbering only (retail keeps the clamp constant in f0 and the reloaded level in f1; MWCC swaps
// them). Constant locals, operand orders and inline-helper spellings did not change it.
struct Envelope8020709C {
	unsigned int flags; // 0x00
	unsigned char pad4[0xA8 - 0x4];
	float time;  // 0xA8
	float level; // 0xAC
	float db;    // 0xB0
	unsigned char padB4[0xC4 - 0xB4];
	float sustain;  // 0xC4
	float attack;   // 0xC8
	float decay;    // 0xCC
	float release;  // 0xD0
	float release2; // 0xD4
	int state;      // 0xD8
};

extern "C" {
extern const float lbl_8042FFD8; // 96.0f
extern const float lbl_8042FFDC; // 1.0f
extern const float lbl_8042FFE0; // 0.0f
extern const float lbl_8042FFE4; // 5.0f

static inline void UpdateDb(Envelope8020709C* e)
{
	e->db = -(lbl_8042FFD8 - lbl_8042FFD8 * e->level);
}

void fn_8020709C(Envelope8020709C* e)
{
	if (e->flags & 1) {
		return;
	}
	switch (e->state) {
		case 0:
			e->level += e->attack;
			UpdateDb(e);
			if (e->level >= lbl_8042FFDC) {
				e->level = lbl_8042FFDC;
				UpdateDb(e);
				e->state++;
			}
			break;
		case 1:
			if (e->db <= e->sustain) {
				e->state++;
			} else {
				e->level -= e->decay;
				UpdateDb(e);
				if (e->level <= lbl_8042FFE0) {
					e->level = lbl_8042FFE0;
					UpdateDb(e);
				}
				if (!(e->db <= e->sustain)) {
					break;
				}
				e->state++;
			}
		case 2:
			e->state++;
		case 3:
			e->level -= e->release;
			UpdateDb(e);
			if (e->level <= lbl_8042FFE0) {
				e->level = lbl_8042FFE0;
				UpdateDb(e);
			}
			break;
		case 4:
			e->state++;
		case 5:
			e->level -= e->release2;
			UpdateDb(e);
			if (e->level <= lbl_8042FFE0) {
				e->level = lbl_8042FFE0;
				UpdateDb(e);
			}
			break;
	}
	e->time += lbl_8042FFE4;
}
}
