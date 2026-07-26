#ifndef AUTOSAVED_ADV_WINDOW_H
#define AUTOSAVED_ADV_WINDOW_H

#include "game/TObject.hpp"
#include "autosaveD/ADV_MENU.hpp"
#include "rwsdk/rwplcore.h"

struct sADV_WINDOW_PARAM {
	sADV_WINDOW_PARAM();
	void operator=(const sADV_WINDOW_PARAM&);

	// The text for each of the options of the window
	/* 0x00 */ u16* mTitleText; // guess
	/* 0x04 */ u16* mOptionText1;
	/* 0x08 */ u16* mOptionText2;
	/* 0x0C */ u16* mOptionText3;
	/* 0x10 */ s32 mMode;
	/* 0x14 */ RwV2d unk_0x14;
	/* 0x1C */ f32 unk_0x1C;
	/* 0x20 */ f32 unk_0x20;
	/* 0x24 */ f32 unk_0x24;
	/* 0x28 */ int unk_0x28;
	/* 0x2C */ int unk_0x2C;
	/* 0x30 */ int unk_0x30;
	/* 0x34 */ int unk_0x34;
	/* 0x38 */ int unk_0x38;
	/* 0x3C */ u32 unk_0x3C;
	/* 0x40 */ int unk_0x40;
};

class ADV_WINDOW : public TObject {
public:
    ADV_WINDOW(TObject* pParent, const sADV_WINDOW_PARAM& rParam);

    /* 0x08 */ virtual ~ADV_WINDOW();
    /* 0x0C */ virtual void Exec();
    /* 0x10 */ virtual void Disp();

	void Begin();
	void End();
	void DispPoly(const RwRect&, const RwRGBA&);
	void RenderQuad(const RwV3d&, const RwV2d&, const RwV2d*, f32);

	void RenderQuad2Herf(const RwV3d&, const RwV2d&);
	void RenderQuad4SKY(const RwV3d&, const RwV2d&);

	void DispWindow(const RwV3d&, const RwV2d&);
	void DispSelect(const RwV3d&, const RwV2d&, int);

    static void Initialize();
    static void InitializeCore();
    static void Finalize();
    static void FinalizeCore();

	static ADV_WINDOW* Create(TObject* pParent, const sADV_WINDOW_PARAM& rParam);

public:
    /* 0x028 */ sADV_WINDOW_PARAM mParam;
	/* 0x06C */ u32 unk_0x6C;
	/* 0x070 */ int unk_0x70;
    /* 0x074 */ ADV_MENU mMenu;
	/* 0x100 */ int mMenuSelection;
	/* 0x104 */ f32 mOptionText1Width;
	/* 0x108 */ f32 mOptionText2Width;
	/* 0x10C */ f32 mOptionText3Width;
	/* 0x110 */ u16 unk_0x110[0x200];
	/* 0x510 */ u16 unk_0x510[0x80];
	/* 0x560 */ u16 unk_0x560[0x80];
	/* 0x610 */ u16 unk_0x610[0x80];
	/* 0x810 */ void* mRenderParameters[10];
};

#endif
