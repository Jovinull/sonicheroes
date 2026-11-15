// Per-frame update of a spinning effect object (HYPOTHESIS: its Exec; the class name is UNKNOWN):
// rotates its frame (+0x4 of the model at +0xB4) about the z axis (fn_8019ED68, then
// fn_8019E880), fades its alpha (+0xB1) by 8 and raises the TObject delete signal once it is 0.
// While the alpha is above 0x28 and the game mode word +0x18 of lbl_8029C310 is 0, it refreshes its
// collision (C_COLLI at +0x28: previous/current position and the velocity lbl_8023A6A4, then
// Entry); otherwise the collision info is cleared. The roles are UNKNOWN.
#include "game/matrix.h"

class C_COLLI
{
public:
	void Entry();
	void ClearInfo();
};

struct Model800F535C {
	u8 pad0[4];
	void* frame; // 0x4
};

struct Mode800F535C {
	u8 pad0[0x18];
	s32 mode; // 0x18
};

struct Words800F535C {
	u32 w[3];
};

class Effect800F535C
{
public:
	// Moves the collision position: the old one is kept, then the position and velocity are set.
	void SetCollision(RwV3d* position, Words800F535C* velocity)
	{
		previous       = current;
		current        = *position;
		this->velocity = *velocity;
	}

	u8 pad0[4];
	u16 signal; // 0x4
	u8 pad6[0x28 - 0x6];
	C_COLLI colli; // 0x28
	u8 pad29[0x88 - 0x29];
	RwV3d current;          // 0x88
	Words800F535C velocity; // 0x94
	u8 padA0[4];
	RwV3d previous; // 0xA4
	u8 padB0;
	u8 alpha; // 0xB1
	u8 padB2[2];
	Model800F535C* model; // 0xB4
};

static inline s32 Fade(s32 alpha)
{
	alpha -= 8;
	if (alpha < 0) {
		alpha = 0;
	}
	return alpha;
}

extern "C" {
extern f32 lbl_8042E4FC;                 // 60.0f (HYPOTHESIS: degrees per frame)
extern const Words800F535C lbl_8023A6A4; // (0, 0, 0)
extern Mode800F535C lbl_8029C310;
void fn_8019ED68(void* frame, const RwV3d* axis, f32 angle, s32 combine);
void fn_8019E880(void* frame);

void fn_800F535C(Effect800F535C* e)
{
	void* frame = e->model->frame;

	fn_8019ED68(frame, &AxisZ, lbl_8042E4FC, 1);
	fn_8019E880(frame);
	e->alpha = Fade(e->alpha);
	if (e->alpha == 0) {
		e->signal |= 1;
	} else if (e->alpha > 0x28) {
		Words800F535C velocity = lbl_8023A6A4;

		if (lbl_8029C310.mode == 0) {
			e->SetCollision(&e->current, &velocity);
			e->colli.Entry();
		} else {
			e->colli.ClearInfo();
		}
	}
}
}
