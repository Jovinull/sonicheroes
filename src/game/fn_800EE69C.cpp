// Sends a player toward a point behind its team's leader: the offset lbl_8023A604 is turned into
// the leader's frame (fn_8003E9B4 on its state at +0x6F0) and added to the leader's position
// (+0x708); a quarter of the vector from the player to that point becomes the player's velocity
// (+0x720, and +0x7C0 in its own frame via fn_8003EB18), and the player takes the leader's yaw
// (+0x700, also into the motion's +0x73C). HYPOTHESIS: formation catch-up; the roles are UNKNOWN.
// NonMatching (11 words, floating-point register numbering only): the retail code keeps the z sum
// in f5 and the vector in f4/f3/f2; MWCC uses one register less. Tried: declaration orders, a
// target vector, the sums inside the subtractions.
#include "types.h"

struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
};

struct Team800EE69C;

struct Player800EE69C {
	u8 pad0[0x6F0];
	u8 state[0x10]; // 0x6F0
	s32 yaw;        // 0x700
	u8 pad704[4];
	RwV3d position; // 0x708
	u8 pad714[0x720 - 0x714];
	RwV3d velocity; // 0x720
	u8 pad72C[0x73C - 0x72C];
	s32 motionYaw; // 0x73C
	u8 pad740[0x7C0 - 0x740];
	RwV3d speed; // 0x7C0
	u8 pad7CC[0x9B8 - 0x7CC];
	Team800EE69C* team; // 0x9B8
};

struct Team800EE69C {
	u8 pad0[0x3A];
	s8 leader; // 0x3A
	u8 pad3B[0x114 - 0x3B];
	Player800EE69C* players[3]; // 0x114
};

extern "C" {
extern const RwV3d lbl_8023A604;
extern f32 lbl_8042E418; // 0.25f
void fn_8003E9B4(void* state, RwV3d* v);
void fn_8003EB18(void* state, RwV3d* v);

void fn_800EE69C(Player800EE69C* p)
{
	Player800EE69C* leader;
	RwV3d offset;
	RwV3d d;
	f32 x;
	f32 y;
	f32 z;

	leader = p->team->players[p->team->leader];
	offset = lbl_8023A604;
	fn_8003E9B4(leader->state, &offset);
	y            = leader->position.y + offset.y;
	z            = leader->position.z + offset.z;
	x            = leader->position.x + offset.x;
	d.x          = x - p->position.x;
	d.y          = y - p->position.y;
	d.z          = z - p->position.z;
	d.x          = lbl_8042E418 * d.x;
	d.y          = lbl_8042E418 * d.y;
	d.z          = lbl_8042E418 * d.z;
	p->motionYaw = p->yaw = leader->yaw;
	p->velocity           = d;
	fn_8003EB18(p->state, &d);
	p->speed = d;
}
}
