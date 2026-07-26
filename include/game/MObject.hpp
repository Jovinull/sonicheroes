#ifndef GAME_MOBJECT_H
#define GAME_MOBJECT_H

#include <types.h>

class MObject {
public:
    MObject();
public:
    /* 0x08 */ virtual void Init() = 0;
    /* 0x0C */ virtual void Loop() = 0;
    /* 0x10 */ virtual void End() = 0;
};

#endif
