#ifndef GAME_ADV_LANGUAGE_H
#define GAME_ADV_LANGUAGE_H

#include <types.h>

namespace ADV_LANGUAGE {
    void strcpy(u16* pDist, const u16* pFormat);
    const u16* GetText(int group, int idx);

};

#define ADV_WINDOW_GROUP_TEXT_ID 0
#define ADV_UNLOCKS_GROUP_TEXT_ID 7

#define ADV_WINDOW_FORMAT_TEXT_ID 84
#define ADV_WINDOW_DELETE_TEXT_ID 86

#endif
