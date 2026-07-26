#ifndef GAME_ONEFILE_H
#define GAME_ONEFILE_H

#include <stddef.h>
#include <types.h>
#include <rwsdk/rwcore.h>

class ONEFILE {
public:
    ONEFILE(char* pFileName, int flags);
    RwTexDictionary* OneFileLoadTextureDictionay(size_t, void*);

public:
    /* 0x00 */ u8 unk_0x00[0x58];
};

#endif
