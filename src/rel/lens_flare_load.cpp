// The lens flare's unload and load routines (endObjEFLens and initObjEFLens
// in the PS2 symbols, lensFlareUnload and lensFlareLoad here, the names the
// register unit gives them). Load reads ./textures/ef_lens.txd, filters it
// linear-mip-linear, gives the first particle kind "panlight" and the next
// eight "lens", and installs CreateEfLens in the hook at +4 of lbl_8042B338
// if nothing is there; unload clears the hook, destroys the dictionary and
// takes the textures back (a loop of nine the compiler unrolls by three).
//
// The strings sit in the module's .data, so they are named here rather than
// written as literals. The `else { return; }` after the dictionary test is
// what leaves the original's `b` to the next instruction and the dead `b`
// to the end behind the first call.

#define LENS_FLARE_CTOR     inline
#define LENS_FLARE_SET_CTOR inline
#define LENS_FLARE_DTOR     inline
#include "src/rel/lens_flare_class.inc"
#include "game/object.h"
extern "C" int sprintf(char* buffer, const char* format, ...);

// The hook block at lbl_8042B338 (only the lens flare's slot is used here).
struct EfLensHooks {
	void* unk0;                                    // 0x00
	TObjEFLens* (*createEfLens)(TObject*, RwV3d*); // 0x04
};

extern "C" char lensFlareTxdPath[];
extern "C" char lensFlareTexLens[];
extern "C" char lensFlareTexPanlight[];
extern "C" RwTexDictionary* lensFlareTexDict;
extern "C" EfLensHooks lbl_8042B338;
extern "C" s32 fn_801A46D0(RwTexDictionary* dict);
extern "C" RwTexDictionary* fn_801A4C84(RwTexDictionary* dict);
extern "C" RwTexture* fn_8005FA0C(RwTexDictionary* dict, char* name);
RwTexDictionary* texLoadTexDictionaryFile(char* path);
void objChangeTextureFilterMode(RwTexDictionary* dict, RwTextureFilterMode mode);
TObjEFLens* CreateEfLens(TObject* parent, RwV3d* position);

extern "C" void lensFlareUnload(void)
{
	lbl_8042B338.createEfLens = NULL;

	if (lensFlareTexDict != NULL) {
		fn_801A46D0(lensFlareTexDict);
		lensFlareTexDict = NULL;
	}

	for (s8 i = 0; i < 9; i++) {
		efLensTable[i].texture = NULL;
	}
}

extern "C" void lensFlareLoad(void)
{
	char path[0x20];

	sprintf(path, lensFlareTxdPath);
	lensFlareTexDict = texLoadTexDictionaryFile(path);
	if (lensFlareTexDict != NULL) {
		fn_801A4C84(lensFlareTexDict);
	} else {
		return;
	}

	objChangeTextureFilterMode(lensFlareTexDict, rwFILTERLINEARMIPLINEAR);
	RwTexture* lens     = fn_8005FA0C(lensFlareTexDict, lensFlareTexLens);
	RwTexture* panlight = fn_8005FA0C(lensFlareTexDict, lensFlareTexPanlight);

	for (s8 i = 0; i < 9; i++) {
		if (i == 0) {
			efLensTable[i].texture = panlight;
		} else {
			efLensTable[i].texture = lens;
		}
	}

	if (lbl_8042B338.createEfLens == NULL) {
		lbl_8042B338.createEfLens = CreateEfLens;
	}
}
