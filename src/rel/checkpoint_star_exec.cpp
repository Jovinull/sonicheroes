#include "types.h"

// The checkpoint star's Exec (checkpointStarExec here): it moves the star
// (checkpointStarMove, still assembly).

typedef struct CheckpointStar CheckpointStar;

extern "C" void checkpointStarMove(CheckpointStar* star);

extern "C" void checkpointStarExec(CheckpointStar* star)
{
	checkpointStarMove(star);
}
