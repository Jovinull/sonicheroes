// Per-material setup callback (HYPOTHESIS: it receives an RpMaterial): reads its surface values
// (fn_801B27EC), and for a texture with more than one mip level (fn_801A1844 on +0x0) takes the low
// byte of +0x50 from the stage value +0x8C1C of lbl_8042C1D0 and, by the raster flags (+0x23 << 8),
// re-applies the surface with mode 0 (flags 0x6000) or, on stage value 6, mode 2 (flags 0x9000)
// (fn_801B2620). Without mip levels the low byte becomes 2 on stage value 6, else 1. Returns the
// material. The names are UNKNOWN.
#include "types.h"

struct Raster8004A81C {
	u8 pad0[0x23];
	u8 flags; // 0x23
};

struct Material8004A81C {
	Raster8004A81C* texture; // 0x0
	u8 pad4[0x50 - 0x4];
	u32 unknown50; // 0x50
};

struct Stage8004A81C {
	u8 pad0[0x8C1C];
	s32 unknown8C1C; // 0x8C1C
};

extern "C" {
extern Stage8004A81C* lbl_8042C1D0;
void fn_801B27EC(Material8004A81C* m, f32* a, s32* b, s32* c, s32* d);
s32 fn_801A1844(Raster8004A81C* texture);
void fn_801B2620(Material8004A81C* m, f32 a, s32 b, s32 c, s32 mode);

Material8004A81C* fn_8004A81C(Material8004A81C* m)
{
	f32 a;
	s32 b;
	s32 c;
	s32 d;
	Raster8004A81C* texture;

	fn_801B27EC(m, &a, &b, &c, &d);
	texture = m->texture;
	if (fn_801A1844(texture) > 1) {
		s32 flags;

		m->unknown50 = (m->unknown50 & ~0xFF) | (lbl_8042C1D0->unknown8C1C & 0xFF);
		flags        = texture->flags << 8;
		if (flags & 0x6000) {
			fn_801B2620(m, a, b, 1, 0);
		} else if ((flags & 0x9000) && lbl_8042C1D0->unknown8C1C == 6) {
			fn_801B2620(m, a, b, 1, 2);
		}
	} else if (lbl_8042C1D0->unknown8C1C == 6) {
		m->unknown50 = (m->unknown50 & ~0xFF) | 2;
	} else {
		m->unknown50 = (m->unknown50 & ~0xFF) | 1;
	}
	return m;
}
}
