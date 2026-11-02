#include "types.h"

// ItempanelInstance::Disp (the PS2 build's name), the same in the thirteen
// stage modules that share the engine core: unless the game is paused (a
// counted panel still draws), the panel's item texture is drawn as a square of
// the given size centred on the given screen point, from the shared four-vertex
// strip itempanelVertices.

typedef struct RwTexture {
	void* raster; // 0x00
} RwTexture;

typedef struct ItempanelTexture {
	RwTexture* texture; // 0x00
	const char* name;   // 0x04
} ItempanelTexture;

typedef struct Im2DVertex {
	f32 x;
	f32 y;
	u8 unk08[0x10];
} Im2DVertex;

typedef struct GameState {
	u8 unk00[0x20];
	s8 unk20; // 0x20
} GameState;

class ItempanelInstance
{
public:
	void Disp(f32 x, f32 y, f32 size);

	u8 unk00[0x10];
	s32 item; // 0x10
	u8 unk14[0x18];
	s32 counted; // 0x2C
};

extern "C" GameState* lbl_8042C180;
extern "C" ItempanelTexture itempanelTextures[13];
extern "C" Im2DVertex itempanelVertices[4];
extern "C" const f32 itempanelHalfSize;

extern "C" void fn_80194234(s32 state, void* value);
extern "C" void fn_801942C0(s32 type, Im2DVertex* vertices, s32 count);
void fn_800A7594();

void ItempanelInstance::Disp(f32 x, f32 y, f32 size)
{
	f32 half;
	f32 top;
	f32 bottom;

	if (lbl_8042C180->unk20 != 0 && counted == 0) {
		return;
	}
	if (itempanelTextures[item].texture == NULL) {
		return;
	}
	fn_80194234(1, itempanelTextures[item].texture->raster);
	half                   = itempanelHalfSize * size;
	itempanelVertices[1].x = itempanelVertices[0].x = x - half;
	itempanelVertices[3].x = itempanelVertices[2].x = x + half;
	top                                             = y - half;
	itempanelVertices[0].y                          = top;
	bottom                                          = y + half;
	itempanelVertices[1].y                          = bottom;
	itempanelVertices[2].y                          = top;
	itempanelVertices[3].y                          = bottom;
	fn_801942C0(4, itempanelVertices, 4);
	fn_800A7594();
}
