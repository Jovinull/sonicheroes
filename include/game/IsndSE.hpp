#ifndef  GAME_ISNDSE_HPP
#define GAME_ISNDSE_HPP

#include <types.h>
#include "game/SoundIDS.hpp" // IWYU pragma: export

class IsndSE {
public:
    void Play(u16 soundID, s8, u32);

public:
    u8 unk_0x0[0xA54];
};

extern IsndSE* SndSE;

#endif
