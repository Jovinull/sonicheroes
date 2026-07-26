#ifndef AUTOSAVED_ADV_MENU_H
#define AUTOSAVED_ADV_MENU_H

#include <types.h>

class ADV_MENU {
public:
    ADV_MENU();
    ~ADV_MENU();

    void SetSelect(int select);
    void OnLoop();
    void Set(int value);

    void Commit();
    int UpdateQUAD2(int firstRowLength, int secondRowLength, int port);
    int UpdateQUAD(int port);
    int UpdateLR(int port);
    int UpdateUD2();
    int UpdateUD(int port);
    void Clr();
    void Add(int value);

    inline bool checkSelect() {
        return mSelect == 0;
    }
public:
	/* 0x00 */ int mSelectItems[32];
	/* 0x80 */ int mCount;
	/* 0x84 */ int mSelect;
	/* 0x88 */ int mLoop;
};

#endif
