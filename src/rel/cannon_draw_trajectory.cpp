#include "types.h"

// A TObjCannon debug member (cannonDrawTrajectory here; the name is ours), the
// out-of-line copy nothing calls. It turns a launch speed straight up by the two
// barrel angles (about X, then Y), then steps the ball along: each step moves the
// position by objCalculateVelocityAsCannonBall and draws the segment travelled in
// the module's trajectory colour. The cannon itself is not read.

typedef struct RwV3d {
	f32 x, y, z;
} RwV3d;

typedef struct RwRGBA {
	u8 red, green, blue, alpha;
} RwRGBA;

struct RwMatrixTag {
	u8 data[0x40];
};

extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;
extern "C" RwRGBA cannonTrajectoryColour;
extern "C" const f32 cannonZero[1];
extern "C" const f32 cannonOne[1];

extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019947C(RwV3d* out, RwV3d* in, s32 count, RwMatrixTag* matrix);
void objCalculateVelocityAsCannonBall(RwV3d* velocity, RwV3d* position);
void DrawLine_(RwV3d* line, RwRGBA* colour);

extern "C" void cannonDrawTrajectory(
    void* object, s32 angX, s32 angY, s32 steps, RwV3d* pos, f32 speed)
{
	RwMatrixTag matrix;
	RwV3d line[2];
	RwV3d velocity;
	f32 sin;

	velocity.x = cannonZero[0];
	velocity.y = speed;
	velocity.z = cannonZero[0];
	sin        = fn_800D7B00(angX);
	fn_80195790(&matrix, &AxisX, cannonOne[0] - fn_800D7AE4(angX), sin, 0);
	sin = fn_800D7B00(angY);
	fn_80195790(&matrix, &AxisY, cannonOne[0] - fn_800D7AE4(angY), sin, 2);
	fn_8019947C(&velocity, &velocity, 1, &matrix);

	line[0] = *pos;
	line[1] = *pos;
	for (; steps > 0; steps--) {
		line[0] = line[1];
		objCalculateVelocityAsCannonBall(&velocity, pos);
		line[1] = *pos;
		DrawLine_(line, &cannonTrajectoryColour);
	}
}
