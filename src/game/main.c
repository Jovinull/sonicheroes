#include "types.h"

// System startup and shutdown, and the game's entry point. The first of Sonic
// Heroes' own code to be written: everything under src/game is the game rather
// than the SDK linked into it.
//
// The translation unit runs from fn_80012C08 at 0x80012C08 to the end of
// fn_80012E50 at 0x80012E5C, and owns the sixteen bytes of .bss at 0x8029BBC0.
// The disc ships no map, so that boundary is argued rather than read:
//
//   lbl_8029BBC0 is touched by exactly two functions in the whole binary,
//   fn_80012C50 and fn_80012E50, which sit on opposite sides of main. A
//   translation unit owns a contiguous run of .text, so everything between
//   them is in this file too. fn_80012E50 does nothing but hand back that
//   block's address, which is what a file's accessor for its own state looks
//   like. The .bss neighbours settle the data bound: lbl_8029BB80 before it
//   has seventeen referencing units and lbl_8029BBD0 after it has thirty nine,
//   so the private block is exactly these sixteen bytes.
//
//   The unit before ends at 0x80012C08. Its members are tied together by
//   lbl_8042C0A8, lbl_8042C0AC and lbl_8042C0B0, shared by the run from
//   fn_8001234C through fn_80012A94, and fn_80012BE0 closes it: the only
//   function in the binary that names fn_80012BE0 is fn_8001234C, which is
//   itself one of that run.
//
//   The unit after starts at 0x80012E5C. fn_80012E5C and fn_80012EA0 are the
//   only two functions that call fn_801971A4, and neither shares data with
//   anything here.
//
// Names are still the dtk ones. Nothing in the binary spells them, and the
// evidence above fixes where the file is, not what it was called.
//
// Almost everything main does goes through one dispatcher at 0x80011FA8, which
// takes a small integer and a pointer. The codes it is called with here are
// 0x10, 0x1C, 0x0D, 0x11, 0x01, 0x00, 0x12 and 0x0E, in that order. What they
// select is not established, so they are left as the numbers the original
// passes rather than guessed at with names.
//
// The unit is built with -opt noschedule, which is worth thirty points on main
// on its own: without it every instruction is right and the order is not. The
// same setting is what matched EXIBios, so it is worth trying first on the
// next game unit rather than last.
//
// Two matching-sensitive details are that unk_0x10 is signed, which makes the
// poll at the bottom cmpwi rather than cmplwi, and the two tick words copied
// into args form a single eight-byte structure assignment. Two independent
// assignments are semantically equivalent but change volatile register
// allocation in GC/1.3.2.
//
// tick is declared wider than the two words main reads: the original's locals
// run to 0x40 where three tightly sized blocks reach only 0x34, and widening
// the topmost one reserves the original 0x50-byte frame. u32[4] is the smallest
// width that does so.
//
// The locals are declared tick, cfg, args because the compiler lays them out
// in the reverse of that, which is the order the original uses: args at 0x08,
// cfg at 0x18, tick at 0x24.
//
// Unused locals do not reach it here, which is worth recording because they do
// elsewhere: in dbcomm an unused u32 pad[4] moves the frame to the original's
// size exactly, while here every width from pad[1] to pad[6] leaves main byte
// for byte where it was, at either end of the block and with or without
// volatile. Whatever this unit is built with discards them, so the frame had
// to come from a local that is actually read. Also rejected: GC/1.2.5n and
// GC/1.3 for the unit (1.3.2 and 1.3 tie at the top, 1.2.5n is twelve points
// worse), and building the file as C++ rather than C.

// Video, disc and graphics entry points this file calls. None of them are in
// include/ yet because no other unit written so far needs them; move them
// there when a second one does.
extern void OSInit(void);
extern void OSResetSystem(u32 reset, u32 resetCode, BOOL forceMenu);
extern void DVDInit(void);
extern void VIInit(void);
extern void VIFlush(void);
extern void VISetBlack(BOOL black);
extern void VIWaitForRetrace(void);
extern void GXSetMisc(u32 token, u32 value);
extern void PADInit(void);

// The dispatcher. Returns zero on failure for the two codes main checks.
extern int fn_80011FA8(int code, void* arg);

// Handed this file's own block on the way up, and reports whether it took.
extern int fn_8001234C(void* state);

// Called as a pair on the way in. The first hands back a value the second
// turns into the two words main copies into lbl_8029BB80 and passes on.
extern u32 fn_8019D4D4(void);
extern void fn_8019D448(u32* out, u32 arg);

// Run before the machine is reset, and by fn_80012E2C on the way down.
extern void GXDrawDone(void);
extern void fn_80013130(void);

// Passed to the dispatcher under code 0x0D as the first word of a three word
// block. In another unit's .data.
extern u8 GXNtsc480IntDf[0x3C];

// The block main runs its loop against. Widely shared: seventeen units name
// it, so it belongs to none of them in particular. Only three words are
// touched here, two written before the loop and one polled by it.
typedef struct Unk8029BB80 {
	u8 unk_0x0[0x4];
	u32 unk_0x4;
	u32 unk_0x8;
	u8 unk_0xC[0x4];
	// Signed: main polls this with cmpwi, not cmplwi.
	s32 unk_0x10;
	u8 unk_0x14[0x2C];
} Unk8029BB80; // 0x40

typedef struct Pair {
	u32 first;
	u32 second;
} Pair;

extern Unk8029BB80 lbl_8029BB80;

// One byte of a pair in another unit's .sbss, set once on the way in.
extern u8 lbl_8042C0C0;

// This file's own state, and the only data it owns. Handed to fn_8001234C at
// startup and to anyone who asks through fn_80012E50. Nothing here reads its
// contents, so it stays opaque.
u8 lbl_8029BBC0[0x10];

int fn_80012C08(void)
{
	return 1;
}

// Blanks the screen, waits for the field to finish and resets the machine.
void fn_80012C10(void)
{
	GXDrawDone();
	VISetBlack(TRUE);
	VIFlush();
	VIWaitForRetrace();
	OSResetSystem(0, 0, FALSE);
}

// Brings up the console: graphics, OS, disc and video, then hands this file's
// block to fn_8001234C and reports whether that took.
int fn_80012C50(void)
{
	GXSetMisc(1, 8);
	OSInit();
	DVDInit();
	VIInit();

	return fn_8001234C(lbl_8029BBC0) != 0;
}

int main(int argc, char** argv)
{
	// Laid out in reverse of declaration order, which puts args at 0x08, cfg at
	// 0x18 and tick at 0x24. tick is wider than the two words read below; see
	// the note at the top of the file.
	u32 tick[4];
	void* cfg[3];
	u32 args[4];
	int i;

	cfg[0] = GXNtsc480IntDf;
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

	args[0]          = 0;
	args[1]          = 0;
	*(Pair*)&args[2] = *(Pair*)tick;
	fn_80011FA8(0x0, args);

	while (lbl_8029BB80.unk_0x10 == 0) {
		fn_80011FA8(0x12, NULL);
	}

	fn_80011FA8(0x0E, NULL);
	fn_80011FA8(0x11, NULL);

	return 0;
}

int fn_80012E24(void)
{
	return 1;
}

int fn_80012E2C(void)
{
	fn_80013130();

	return 1;
}

// Hands back this file's block.
void* fn_80012E50(void)
{
	return lbl_8029BBC0;
}
