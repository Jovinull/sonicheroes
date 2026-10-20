#include "game/pathctrl.h"

// sEffLeserBeam's Alive and Move (the PS2 build's names and spelling): one
// segment of the laser gadget's beam, alive until it falls below its bottom;
// each frame it falls by laserBeamStep and grows by laserBeamGrowth.

struct sEffLeserBeam {
	bool Alive();
	void Move();

	RwV3d pos;  // 0x00
	f32 bottom; // 0x0C
	f32 length; // 0x10
};

extern "C" const RwV3d laserBeamStep;
extern "C" const f32 laserBeamGrowth[1];

bool sEffLeserBeam::Alive()
{
	return !(bottom > pos.y);
}

void sEffLeserBeam::Move()
{
	pos.x += laserBeamStep.x;
	pos.y += laserBeamStep.y;
	pos.z += laserBeamStep.z;
	length += laserBeamGrowth[0];
}
