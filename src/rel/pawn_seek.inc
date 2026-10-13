// The pawn's player search shared by its seeking modes (HideComeOut, Turn and
// WanderTurn): pawnSeek (the name is ours) returns the mode to ask for, the
// given one when the pawn is not active (0x378). Close to the player
// (fn_800A59C4 under 0x80) the gait picks the attack (2: mode 0x16, 3 to 6:
// mode 0x18, others: turn to it, mode 3), otherwise the pawn keeps turning
// (fn_800A4668); then the enemy base steps (fn_800A5C6C), a landed pawn stops
// falling slower than its fall speed and a finished turn (fn_800A5888) is
// closed (fn_800A5B50). The early return is what leaves the retail's
// `bne; b` around the body.

typedef struct Pawn {
	u8 unk000[0xD4];
	s32 motion;     // 0x0D4
	u8 unk0D8[0x2E];
	u16 status;     // 0x106
	u8 unk108[0x54];
	f32 riseSpeed;  // 0x15C
	u8 unk160[0x3C];
	s32 state;      // 0x19C
	u8 unk1A0[0x8];
	f32 fallSpeed;  // 0x1A8
	u8 unk1AC[0x9C];
	s32 nextMode;   // 0x248
	u8 unk24C[0x2];
	s8 gait;        // 0x24E
	u8 unk24F[0xB1];
	s32 wanderTimer; // 0x300
	u8 unk304[0x74];
	s32 active;     // 0x378
} Pawn;

extern "C" const f32 pawnZero[1];
extern "C" const f32 pawnMinusOne[1];
extern "C" const f32 pawnLandScale[1];

extern "C" int fn_800A59C4(Pawn* pawn);
extern "C" void fn_800A4A8C(Pawn* pawn, f32 value);
extern "C" void fn_800A4668(Pawn* pawn);
extern "C" void fn_800A5C6C(Pawn* pawn, u32 flags);
extern "C" int fn_800A5888(Pawn* pawn, f32 value);
extern "C" void fn_800A5B50(Pawn* pawn, u32 flags);

static inline int pawnSeek(Pawn* pawn, int mode)
{
	if (pawn->active == 0) {
		return mode;
	}
	if (fn_800A59C4(pawn) < 0x80) {
		switch (pawn->gait) {
		case 2:
			mode = 0x16;
			break;
		case 3:
		case 4:
		case 5:
		case 6:
			mode = 0x18;
			break;
		default:
			fn_800A4A8C(pawn, pawnMinusOne[0]);
			mode = 3;
			break;
		}
	} else {
		fn_800A4668(pawn);
	}
	fn_800A5C6C(pawn, 0xF00);
	if ((pawn->status & 2) && pawn->riseSpeed < pawnLandScale[0] * pawn->fallSpeed) {
		pawn->riseSpeed = pawnZero[0];
	}
	if (fn_800A5888(pawn, pawnMinusOne[0])) {
		fn_800A5B50(pawn, 0xF00);
	}
	return mode;
}

