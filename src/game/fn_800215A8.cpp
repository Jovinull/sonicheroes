#include "game/light.h"

// Resets the player input/target state for a new world: points the light manager (lbl_802D5E80) at
// the current world (lbl_8042C1D0 +0x7250), clears the per-player tables as fn_8002171C does, runs
// the six table builders fn_8002461C .. fn_80021848 on the argument inside a matrix push/pop, and
// clears the input counters (keeping the previous words in lbl_8042C190/lbl_8042C192). Unlike
// fn_8002171C it leaves lbl_8042C1A0 alone. HYPOTHESIS: the roles are UNKNOWN.

struct Quad800215A8 {
	s32 f0;
	s32 f4;
	s32 f8;
	s32 fC;
};

struct SlotC800215A8 {
	s32 f0;
	u8 pad[0x1484];
};

struct SlotD800215A8 {
	s32 f0;
	u8 pad[0x804];
};

struct Game800215A8 {
	u8 pad0[0x7250];
	RpWorld* world; // 0x7250
};

extern CLIGHT lbl_802D5E80;

extern "C" {
extern Game800215A8* lbl_8042C1D0;
extern Quad800215A8 lbl_802AD060;
extern s16 lbl_802AD040[8];
extern s16 lbl_802AD050[8];
extern SlotC800215A8 lbl_8029EBC0[8];
extern SlotD800215A8 lbl_802A9000[8];
extern s16 lbl_8042C188;
extern s16 lbl_8042C18A;
extern u16 lbl_8042C18C;
extern u16 lbl_8042C18E;
extern u16 lbl_8042C190;
extern u16 lbl_8042C192;
extern s16 lbl_8042C194;
extern s16 lbl_8042C196;
extern s16 lbl_8042C198;
extern s16 lbl_8042C19A;
extern s16 lbl_8042C19C;
extern s16 lbl_8042C19E;
void fn_8002461C(void* arg);
void fn_8002358C(void* arg);
void fn_80022508(void* arg);
void fn_80021D9C(void* arg);
void fn_80021AF0(void* arg);
void fn_80021848(void* arg);
}

void PushMatrixEx();
void PopMatrixEx();

extern "C" void fn_800215A8(void* arg)
{
	int i;

	lbl_802D5E80.ChangeWorld(lbl_8042C1D0->world);
	lbl_802AD060.f0 = 0;
	lbl_802AD060.f4 = -1;
	lbl_802AD060.f8 = -1;
	lbl_802AD060.fC = -1;
	for (i = 0; i < 8; i++) {
		lbl_802AD040[i]    = 0;
		lbl_802AD050[i]    = 0;
		lbl_8029EBC0[i].f0 = 0;
		lbl_802A9000[i].f0 = 0;
	}
	PushMatrixEx();
	fn_8002461C(arg);
	fn_8002358C(arg);
	fn_80022508(arg);
	fn_80021D9C(arg);
	fn_80021AF0(arg);
	fn_80021848(arg);
	PopMatrixEx();
	lbl_8042C188 = 0;
	lbl_8042C18A = 0;
	lbl_8042C190 = lbl_8042C18C;
	lbl_8042C192 = lbl_8042C18E;
	lbl_8042C18C = 0;
	lbl_8042C18E = 0;
	lbl_8042C194 = 0;
	lbl_8042C196 = 0;
	lbl_8042C198 = 0;
	lbl_8042C19A = 0;
	lbl_8042C19C = 0;
	lbl_8042C19E = 0;
}
