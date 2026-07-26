#ifndef GAME_TNECFONT_H
#define GAME_TNECFONT_H

#include <types.h>

class TNECFont {
public:
    void Initialize();
    void Finalize();

    u32 GetWidth(const u16*);
public:
    /* 0x00 */ u8 unk_0x00[0x2338];
};

extern TNECFont NECFont;

#endif
