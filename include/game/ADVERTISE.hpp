#ifndef GAME_ADVERTISE_H
#define GAME_ADVERTISE_H

#include "game/MObject.hpp"

class ADVERTISE : public MObject {
public:
    ADVERTISE();
public:
    /* 0x08 */ virtual void Init();
    /* 0x0C */ virtual void Loop();
    /* 0x10 */ virtual void End();

    int GetKey(int button, int port);
    int GetButton(int port) const;

public:
    /* 0x00 */ u8 unk_0x0[0x68];
};

extern ADVERTISE Advertise;

#endif
