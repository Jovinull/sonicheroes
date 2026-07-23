#include "types.h"

// The game's entry point, and the first of Sonic Heroes' own code to be
// written. Everything under src/game is the game rather than the SDK linked
// into it.
//
// The translation unit boundary here is provisional and covers main alone.
// That is almost certainly too narrow: main is 0x188 bytes at 0x80012C9C with
// unnamed functions immediately on both sides, and nothing yet establishes
// where its file starts or ends. The disc ships no map, so the boundary has to
// come from cross references, and none have been worked out for this range.
// Widen the split once neighbours are shown to share data with this file.
//
// Almost everything main does goes through one dispatcher at 0x80011FA8, which
// takes a small integer and a pointer. The codes it is called with here are
// 0x10, 0x1C, 0x0D, 0x11, 0x01, 0x00, 0x12 and 0x0E, in that order. What they
// select is not established, so they are left as the numbers the original
// passes rather than guessed at with names.
//
// The unit is built with -opt noschedule, which is worth 30 points here on its
// own: without it every instruction is right and the order is not. The same
// setting is what matched EXIBios, so it is worth trying first on the next
// game unit rather than last.
//
// main stands at 98.7%. Everything still different is one cause: the original
// reserves a 0x50 frame where ours is 0x40, and the sixteen bytes it carries
// beyond what it uses push each local up by eight. Its three blocks sit at
// 0x08, 0x18 and 0x24; ours land at 0x08, 0x10 and 0x18 and are otherwise
// identical. Registers, instruction order and instruction count already agree.
//
// Measured and rejected against that: GC/1.2.5n and GC/1.3 for the unit (1.3.2
// and 1.3 tie at the top, 1.2.5n is twelve points worse), building it as C++
// rather than C, and every ordering of the four locals. The gap is locals the
// original declared and did not use, which leave no trace to recover them
// from. The same wall stands in dbcomm, and it is the one thing worth solving
// for both.

// The dispatcher. Returns zero on failure for the two codes main checks.
extern int fn_80011FA8(int code, void* arg);

extern void PADInit(void);

// Called as a pair on the way in. The first hands back a value the second
// turns into the two words main copies into lbl_8029BB80 and passes on.
extern u32 fn_8019D4D4(void);
extern void fn_8019D448(u32* out, u32 arg);

// Passed to the dispatcher under code 0x0D as the first word of a three word
// block. In another unit's .data.
extern u8 lbl_80298720[0x3C];

// The block main runs its loop against. Only three words are touched here: two
// written before the loop and one polled by it.
typedef struct Unk8029BB80 {
	u8 unk_0x0[0x4];
	u32 unk_0x4;
	u32 unk_0x8;
	u8 unk_0xC[0x4];
	u32 unk_0x10;
	u8 unk_0x14[0x2C];
} Unk8029BB80; // 0x40

extern Unk8029BB80 lbl_8029BB80;

// One byte of a pair in another unit's .sbss, set once on the way in.
extern u8 lbl_8042C0C0;

int main(int argc, char** argv)
{
	u32 args[4];
	void* cfg[3];
	u32 tick[2];
	int i;

	cfg[0] = lbl_80298720;
	cfg[1] = 0;
	cfg[2] = (void*)0x40000;

	lbl_8042C0C0 = 1;

	if (!fn_80011FA8(0x10, NULL)) {
		return 0;
	}

	for (i = 1; i < argc; i++) {
		fn_80011FA8(0x1C, argv[i]);
	}

	if (!fn_80011FA8(0x0D, cfg)) {
		fn_80011FA8(0x11, NULL);
		return 0;
	}

	PADInit();

	for (i = 1; i < argc; i++) {
		fn_80011FA8(0x1, argv[i]);
	}

	fn_8019D448(tick, fn_8019D4D4());

	lbl_8029BB80.unk_0x4 = tick[0];
	lbl_8029BB80.unk_0x8 = tick[1];

	args[0] = 0;
	args[1] = 0;
	args[2] = tick[0];
	args[3] = tick[1];
	fn_80011FA8(0x0, args);

	while (lbl_8029BB80.unk_0x10 == 0) {
		fn_80011FA8(0x12, NULL);
	}

	fn_80011FA8(0x0E, NULL);
	fn_80011FA8(0x11, NULL);

	return 0;
}
