#include "types.h"

// TObjEFLens::DispPtcl (the PS2 build's name), the same in the thirteen stage
// modules that share the engine core. The lens's direction from the camera is
// set against the camera's view axis; when the lens is in front, its screen
// point is found and its particles drawn (EFLensPtcl::Draw, still assembly):
// the glow, when the lens is near the middle of the view, the core, and then
// each flare along the line from the lens to the middle of the screen, sized
// and faded by its table entry and by how straight the camera looks at it.

typedef struct RwV3d {
	f32 x;
	f32 y;
	f32 z;
} RwV3d;

typedef struct RwV2d {
	f32 x;
	f32 y;
} RwV2d;

struct RwMatrixTag {
	u8 data[0x40];
};

typedef struct EFLensTableEntry {
	f32 spread; // 0x00
	f32 size;   // 0x04
	f32 shrink; // 0x08
	f32 fade;   // 0x0C
	f32 depth;  // 0x10
} EFLensTableEntry;

class EFLensPtcl
{
public:
	void Draw();

	s16 id;                        // 0x00
	u8 unk02[0x2];                 // 0x02
	f32 x;                         // 0x04
	f32 y;                         // 0x08
	f32 z;                         // 0x0C
	f32 size;                      // 0x10
	f32 alpha;                     // 0x14
	const EFLensTableEntry* entry; // 0x18
	void* owner;                   // 0x1C
	EFLensPtcl* next;              // 0x20
};

typedef struct LensCamera {
	RwV3d pos; // 0x00
	s32 angX;  // 0x0C
	s32 angY;  // 0x10
} LensCamera;

class TObjEFLens
{
public:
	void DispPtcl();

	u8 unk00[0x18];
	virtual void Virtual08();
	virtual void Virtual0C();
	virtual void Virtual10();
	virtual void Virtual14();
	virtual void Virtual18();
	virtual void Virtual1C();
	virtual void Virtual20();
	virtual void Virtual24();
	virtual void Virtual28();
	virtual void Virtual2C();
	virtual RwV3d* GetPosition();
	u8 unk1C[0x10];
	EFLensPtcl* ptclTop; // 0x2C
};

extern "C" LensCamera* lbl_8042C208;
extern "C" const RwV3d lensFlareForward;
extern "C" const f32 lensFlareBaseDepth;
extern "C" const f32 lensFlareZero[1];
extern "C" const f32 lensFlareOne[1];
extern "C" const f32 lensFlareGlowStart;
extern "C" const f32 lensFlareGlowScale;
extern "C" const f32 lensFlareGlowOffset;
extern "C" const f32 lensFlareGlowAlpha;
extern "C" const f32 lensFlareGlowSize;
extern "C" const f32 lensFlareFadeScale;
extern "C" const f32 lensFlareFadeStart;
extern "C" const f32 lensFlareCenterX;
extern "C" const f32 lensFlareCenterY;
extern "C" const RwV3d AxisX;
extern "C" const RwV3d AxisY;

extern "C" f32 fn_80199248(f32 value);
extern "C" f32 fn_800D7B00(s32 angle);
extern "C" f32 fn_800D7AE4(s32 angle);
extern "C" void fn_80195790(
    RwMatrixTag* matrix, const RwV3d* axis, f32 oneMinusCos, f32 sin, s32 combine);
extern "C" void fn_8019947C(RwV3d* out, const RwV3d* in, s32 count, const RwMatrixTag* matrix);
void ProjectScreen(RwMatrixTag* matrix, RwV3d* pos, RwV2d* screen);

void TObjEFLens::DispPtcl()
{
	RwMatrixTag matrix;
	RwV3d view;
	RwV3d* pos = GetPosition();
	f32 dot;
	f32 dx;
	f32 dy;
	f32 dz;
	f32 len2;
	EFLensPtcl* ptcl;

	dx   = pos->x - lbl_8042C208->pos.x;
	dy   = pos->y - lbl_8042C208->pos.y;
	dz   = pos->z - lbl_8042C208->pos.z;
	len2 = dz * dz + (dx * dx + dy * dy);

	if (lensFlareZero[0] != len2) {
		f32 scale = fn_80199248(len2);

		dx *= scale;
		dy *= scale;
		dz *= scale;
	}
	RwV3d forward = lensFlareForward;
	RwV2d screen;

	fn_80195790(&matrix, &AxisY, lensFlareOne[0] - fn_800D7AE4(lbl_8042C208->angY),
	    fn_800D7B00(lbl_8042C208->angY), 0);
	fn_80195790(&matrix, &AxisX, lensFlareOne[0] - fn_800D7AE4(lbl_8042C208->angX),
	    fn_800D7B00(lbl_8042C208->angX), 1);
	fn_8019947C(&view, &forward, 1, &matrix);
	ptcl = ptclTop;
	dot  = view.z * dz + (view.x * dx + view.y * dy);
	if (dot > lensFlareZero[0]) {
		ProjectScreen(NULL, pos, &screen);
		if (dot > lensFlareGlowStart) {
			f32 glow = lensFlareGlowScale * (dot - lensFlareGlowOffset);

			glow        = glow * glow;
			ptcl->x     = screen.x;
			ptcl->y     = screen.y;
			ptcl->z     = lensFlareBaseDepth;
			ptcl->alpha = lensFlareGlowAlpha * glow;
			ptcl->size  = lensFlareGlowSize * glow;
			ptcl->Draw();
		}
		ptcl = ptcl->next;
		if (dot > lensFlareFadeStart) {
			dot = lensFlareFadeScale * (dot - lensFlareFadeStart);
		} else {
			dot = lensFlareZero[0];
		}
		ptcl->x     = screen.x;
		ptcl->y     = screen.y;
		ptcl->z     = lensFlareBaseDepth;
		ptcl->alpha = lensFlareOne[0];
		ptcl->size  = lensFlareBaseDepth;
		ptcl->Draw();
		ptcl = ptcl->next;
		{
			f32 offsetX;
			f32 offsetY;
			f32 fade;

			fade    = (dot * dot) * (dot * dot);
			offsetX = lensFlareCenterX - screen.x;
			offsetY = lensFlareCenterY - screen.y;

			while (ptcl != NULL) {
				const EFLensTableEntry* entry = ptcl->entry;
				f32 keep                      = lensFlareOne[0] - entry->fade;
				f32 size = entry->size * (lensFlareOne[0] - keep * entry->shrink);

				if (size < lensFlareZero[0]) {
					// volatile is a reconstruction aid: the retail reloads the
					// bound rather than reusing the value the loop keeps.
					size = *(volatile const f32*)lensFlareZero;
				}
				ptcl->x     = screen.x + offsetX * entry->spread;
				ptcl->y     = screen.y + offsetY * entry->spread;
				ptcl->z     = lensFlareBaseDepth - entry->depth;
				ptcl->alpha = fade * entry->fade;
				ptcl->size  = size;
				ptcl->Draw();
				ptcl = ptcl->next;
			}
		}
	}
}
