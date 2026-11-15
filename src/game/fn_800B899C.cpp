#include "game/rw_engine.h"

// Tests an object against three points: when its count fn_80158918 is positive, the object's
// bounding box (+0x50), grown by lbl_8042DD90 on each side, is checked against each point
// (fn_80199FF4) and the first point inside passes the object to fn_80149214. Otherwise, or when
// no point is inside, it clears the object's slot at the offset fn_801589D4(0x120) and stores
// fn_8015BF04(0) at +0x84. Returns the object. HYPOTHESIS: RenderWare plugin bookkeeping; the
// callee roles are UNKNOWN.

struct Object800B899C {
	u8 pad0[0x50];
	RwBBox bbox; // 0x50
	u8 pad68[0x84 - 0x68];
	void* unknown84; // 0x84
};

extern "C" {
extern const f32 lbl_8042DD90;
s32 fn_80158918(Object800B899C* obj);
s32 fn_801589D4(s32 id);
void* fn_8015BF04(void* value);
s32 fn_80199FF4(const RwBBox* bbox, const RwV3d* point);
void fn_80149214(Object800B899C* obj);
}

static inline void Release(Object800B899C* obj)
{
	s32* slot      = (s32*)((u8*)obj + fn_801589D4(0x120));
	*slot          = 0;
	obj->unknown84 = fn_8015BF04(NULL);
}

extern "C" Object800B899C* fn_800B899C(Object800B899C* obj, const RwV3d points[3])
{
	if (fn_80158918(obj) <= 0) {
		Release(obj);
		return obj;
	}

	RwBBox bbox = obj->bbox;
	bbox.sup.x += lbl_8042DD90;
	bbox.sup.y += lbl_8042DD90;
	bbox.sup.z += lbl_8042DD90;
	bbox.inf.x -= lbl_8042DD90;
	bbox.inf.y -= lbl_8042DD90;
	bbox.inf.z -= lbl_8042DD90;
	for (s32 i = 0; i < 3; i++) {
		if (fn_80199FF4(&bbox, &points[i])) {
			fn_80149214(obj);
			return obj;
		}
	}
	Release(obj);
	return obj;
}
