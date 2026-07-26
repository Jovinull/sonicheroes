#ifndef AUTOSAVED_ADV_WINDOW_H
#define AUTOSAVED_ADV_WINDOW_H

#include "game/TObject.hpp"
#include "autosaveD/ADV_MENU.hpp"

struct Pair {
	u32 first;
	u32 second;
};

struct sADV_WINDOW_PARAM {
	u16* unk_0x0;
	u16* resource_1;
	u16* resource_2;
	u16* resource_3;
	s32 mode;
	Pair unk_0x14;
	u32 unk_0x1C;
	Pair unk_0x20;
	Pair unk_0x28;
	Pair unk_0x30;
	u32 unk_0x38;
	u32 unk_0x3C;
	u32 unk_0x40;
};

class ADV_WINDOW : public TObject {
public:
    ADV_WINDOW(TObject* pParent, const sADV_WINDOW_PARAM&);

    /* 0x08 */ virtual ~ADV_WINDOW();
    /* 0x0C */ virtual void Exec();
    /* 0x10 */ virtual void Disp();

    static void Initialize();
    static void InitializeCore();
    static void Finalize();
    static void FinalizeCore();
public:
    /* 0x028 */ sADV_WINDOW_PARAM mParam;
	/* 0x06C */ u32 unk_0x6C;
	/* 0x070 */ u32 unk_0x70;
    /* 0x074 */ ADV_MENU mMenu;
	/* 0x100 */ u32 mMenuState;
	/* 0x104 */ f32 resource_value_1;
	/* 0x108 */ f32 resource_value_2;
	/* 0x10C */ f32 resource_value_3;
	/* 0x110 */ u16 unk_0x110[0x200];
	/* 0x510 */ u16 unk_0x510[0x80];
	/* 0x560 */ u16 unk_0x560[0x80];
	/* 0x610 */ u16 unk_0x610[0x94];
};

#endif
