// Splits a colour box in two along its best axis (HYPOTHESIS: the palette quantizer's median-cut
// step): sums the colour statistics of the whole box (fn_801A5CD0 from the tree root), asks
// fn_801A5EE0 for the best cut and its gain along red, green, blue and alpha, and returns 0 when
// no axis gains anything. Otherwise copies the box into the second one and moves the cut plane of
// the axis with the largest gain (ties favour the earlier axis): the second box starts at the cut
// and the first one ends there. Returns 1.
// NonMatching: the box copy is C's word-pair copy in retail (C++ moves each word through r0), and
// retail loads the 0.0f constant only after the origin and index stores, as if the statistics
// init (the body of fn_801A540C) were inlined from another function (22 words).
#include "game/rw_palquant.h"

// Colour box: inclusive low corner and exclusive high corner, RGBA.
struct RwPalQuantBox801A63B4 {
	u8 lo[4]; // 0x0
	u8 hi[4]; // 0x4
};

// Accumulated leaf statistics (HYPOTHESIS: weight, RGBA sums and squared magnitude) plus the
// palette index slot, laid out like a tree leaf.
struct RwPalQuantSums801A63B4 {
	f32 value[6];    // 0x0
	u8 paletteIndex; // 0x18
};

extern "C" {
// .sdata2 constant 0.0f.
extern f32 lbl_8042F750;

void fn_801A5CD0(RwPalQuantNode* node, u8* origin, s32 depth, RwPalQuantBox801A63B4* box,
    RwPalQuantSums801A63B4* sums);
// HYPOTHESIS: the best cut of a box along one axis (1-4: red, green, blue, alpha) and its gain.
f32 fn_801A5EE0(RwPalQuantNode* root, RwPalQuantBox801A63B4* box, s32 axis, s32* cut,
    RwPalQuantSums801A63B4* whole);

s32 fn_801A63B4(RwPalQuantNode* root, RwPalQuantBox801A63B4* box1, RwPalQuantBox801A63B4* box2)
{
	RwPalQuantSums801A63B4 whole;
	s32 cutRed;
	s32 cutGreen;
	s32 cutBlue;
	s32 cutAlpha;
	u8 origin[4];
	f32 gainRed;
	f32 gainGreen;
	f32 gainBlue;
	f32 gainAlpha;

	origin[0]          = 0;
	origin[1]          = 0;
	origin[2]          = 0;
	origin[3]          = 0;
	whole.paletteIndex = 0xFF;
	whole.value[0]     = lbl_8042F750;
	whole.value[1]     = lbl_8042F750;
	whole.value[2]     = lbl_8042F750;
	whole.value[3]     = lbl_8042F750;
	whole.value[4]     = lbl_8042F750;
	whole.value[5]     = lbl_8042F750;
	fn_801A5CD0(root, origin, lbl_8042BE60, box1, &whole);

	gainRed   = fn_801A5EE0(root, box1, 1, &cutRed, &whole);
	gainGreen = fn_801A5EE0(root, box1, 2, &cutGreen, &whole);
	gainBlue  = fn_801A5EE0(root, box1, 3, &cutBlue, &whole);
	gainAlpha = fn_801A5EE0(root, box1, 4, &cutAlpha, &whole);
	if (gainRed <= lbl_8042F750 && gainGreen <= lbl_8042F750 && gainBlue <= lbl_8042F750
	    && gainAlpha <= lbl_8042F750) {
		return 0;
	}

	*box2 = *box1;
	if (gainRed >= gainGreen) {
		if (gainRed >= gainBlue) {
			if (gainRed >= gainAlpha) {
				box1->hi[0] = box2->lo[0] = cutRed;
			} else {
				box1->hi[3] = box2->lo[3] = cutAlpha;
			}
		} else if (gainBlue >= gainAlpha) {
			box1->hi[2] = box2->lo[2] = cutBlue;
		} else {
			box1->hi[3] = box2->lo[3] = cutAlpha;
		}
	} else if (gainGreen >= gainBlue) {
		if (gainGreen >= gainAlpha) {
			box1->hi[1] = box2->lo[1] = cutGreen;
		} else {
			box1->hi[3] = box2->lo[3] = cutAlpha;
		}
	} else if (gainBlue >= gainAlpha) {
		box1->hi[2] = box2->lo[2] = cutBlue;
	} else {
		box1->hi[3] = box2->lo[3] = cutAlpha;
	}
	return 1;
}
}
