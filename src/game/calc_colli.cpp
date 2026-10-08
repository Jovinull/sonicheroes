#include "types.h"

// calc_colli.cpp is identified as C++ in the PS2 symbolic metadata.
// GameCube arithmetic and aliasing behavior are reconstructed from this build.
// NonMatching: remaining instruction differences are recorded in docs/language-audit.md.
struct RwV3d {
	f32 x, y, z;
};
extern const __declspec(section ".sdata2") f32 lbl_8042DFD0;
extern const __declspec(section ".sdata2") f32 lbl_8042DFD4;
extern const __declspec(section ".sdata2") f32 lbl_8042DFD8;
extern "C" f64 __fabs(f64);

// Separate storage view for the address-taken vector writes in the GameCube code.
// This is a reconstruction aid, not an asserted original type name.
struct VectorComponents {
	f32 x, y, z;
};
#define Subtract(o, a, b)                                                                          \
	(((VectorComponents*)(o))->x = (a)->x - (b)->x, ((VectorComponents*)(o))->y = (a)->y - (b)->y, \
	    ((VectorComponents*)(o))->z = (a)->z - (b)->z)
#define Cross(o, a, b)                                                                             \
	(((VectorComponents*)(o))->x    = (a)->y * (b)->z - (a)->z * (b)->y,                           \
	    ((VectorComponents*)(o))->y = (a)->z * (b)->x - (a)->x * (b)->z,                           \
	    ((VectorComponents*)(o))->z = (a)->x * (b)->y - (a)->y * (b)->x)
#define Scale(o, a, t)                                                                             \
	(((VectorComponents*)(o))->x = (a)->x * (t), ((VectorComponents*)(o))->y = (a)->y * (t),       \
	    ((VectorComponents*)(o))->z = (a)->z * (t))
#define Add(o, a, b)                                                                               \
	(((VectorComponents*)(o))->x = (a)->x + (b)->x, ((VectorComponents*)(o))->y = (a)->y + (b)->y, \
	    ((VectorComponents*)(o))->z = (a)->z + (b)->z)
#define Dot(a, b) ((a)->z * (b)->z + ((a)->x * (b)->x + (a)->y * (b)->y))

static s32 clIntersectTriangleY(const RwV3d*, const RwV3d*, RwV3d*, f32*);
static s32 clIntersectTriangle(const RwV3d*, const RwV3d*, RwV3d*, f32*);

extern "C" f32 fn_801991B4(RwV3d*);
void clGetTriangleVectorCoef_CrsP(RwV3d*, RwV3d*, RwV3d*, RwV3d*, f32*, f32*);

inline f32 clDistanceP2V2(const RwV3d* pos, const RwV3d* vec)
{
	f32 APAB = Dot(pos, vec);
	if (APAB > lbl_8042DFD4) {
		f32 lABl2 = Dot(vec, vec);
		if (lABl2 < lbl_8042DFD0)
			return Dot(pos, pos);
		if (APAB >= lABl2) {
			f32 x = pos->x - vec->x, y = pos->y - vec->y, z = pos->z - vec->z;
			return z * z + (x * x + y * y);
		}
		f32 t = APAB / lABl2;
		f32 x = pos->x - t * vec->x, y = pos->y - t * vec->y, z = pos->z - t * vec->z;
		return z * z + (x * x + y * y);
	}
	return Dot(pos, pos);
}
inline f32 clDistanceP2V2_ans(const RwV3d* pos, const RwV3d* vec, RwV3d* ans)
{
	f32 APAB = Dot(pos, vec);
	RwV3d Q;
	if (APAB > lbl_8042DFD4) {
		f32 lABl2 = Dot(vec, vec);
		if (lABl2 < lbl_8042DFD0) {
			if (ans)
				ans->x = ans->y = ans->z = lbl_8042DFD4;
			return Dot(pos, pos);
		}
		if (APAB >= lABl2) {
			if (ans) {
				ans->x = vec->x;
				ans->y = vec->y;
				ans->z = vec->z;
			}
			Q.x = pos->x - vec->x;
			Q.y = pos->y - vec->y;
			Q.z = pos->z - vec->z;
			return Dot(&Q, &Q);
		}
		f32 t = APAB / lABl2;
		Q.x   = t * vec->x;
		Q.y   = t * vec->y;
		Q.z   = t * vec->z;
		if (ans) {
			ans->x = Q.x;
			ans->y = Q.y;
			ans->z = Q.z;
		}
		Q.x = pos->x - Q.x;
		Q.y = pos->y - Q.y;
		Q.z = pos->z - Q.z;
		return Dot(&Q, &Q);
	}
	if (ans)
		ans->x = ans->y = ans->z = lbl_8042DFD4;
	return Dot(pos, pos);
}

s32 clDetectS2T(
    const RwV3d* sphere_pos, f32 sphere_rad, RwV3d* tri_vertex, RwV3d* push_vec, RwV3d* coli_vec)
{
	f32 lANl2, AOAN;
	RwV3d vec_ao, vec_ab, vec_ac, crsP, vec_po, coliVec;
	f32 len_po2;
	RwV3d pos_p;
	VectorComponents ans;
	s32 across;
	Subtract(&vec_ab, tri_vertex + 1, tri_vertex);
	Subtract(&vec_ac, tri_vertex + 2, tri_vertex);
	Subtract(&vec_ao, sphere_pos, tri_vertex);
	Cross(&crsP, &vec_ab, &vec_ac);
	AOAN = Dot(&vec_ao, &crsP);
	if (AOAN < lbl_8042DFD4)
		return 0;
	lANl2 = Dot(&crsP, &crsP);
	if (lANl2 > lbl_8042DFD0) {
		f32 t = AOAN / lANl2;
		Scale(&vec_po, &crsP, t);
		len_po2 = Dot(&vec_po, &vec_po);
		Subtract(&pos_p, &vec_ao, &vec_po);
	} else {
		vec_po.x = vec_po.y = vec_po.z = lbl_8042DFD4;
		len_po2                        = lbl_8042DFD4;
		pos_p.x                        = vec_ao.x;
		pos_p.y                        = vec_ao.y;
		pos_p.z                        = vec_ao.z;
	}
	if (lbl_8042DFD0 + sphere_rad * sphere_rad < len_po2)
		return 0;
	f32 s, t;
	clGetTriangleVectorCoef_CrsP(&vec_ab, &vec_ac, &pos_p, &crsP, &s, &t);
	if (s < lbl_8042DFD4) {
		if (t < lbl_8042DFD4) {
			if (Dot(&vec_ab, &vec_ac) < lbl_8042DFD4) {
				if (Dot(&vec_ab, &vec_ao) > lbl_8042DFD4)
					across = 1;
				else if (Dot(&vec_ac, &vec_ao) > lbl_8042DFD4)
					across = 2;
				else
					across = 4;
			} else
				across = 4;
		} else if (s + t > lbl_8042DFD8) {
			RwV3d vec_cb, vec_co;
			Subtract(&vec_cb, &vec_ab, &vec_ac);
			if (Dot(&vec_ac, &vec_cb) > lbl_8042DFD4) {
				Subtract(&vec_co, &vec_ao, &vec_ac);
				if (Dot(&vec_ac, &vec_co) < lbl_8042DFD4)
					across = 2;
				else if (Dot(&vec_cb, &vec_co) > lbl_8042DFD4)
					across = 3;
				else
					across = 6;
			} else
				across = 6;
		} else
			across = 2;
	} else if (t < lbl_8042DFD4) {
		if (s + t > lbl_8042DFD8) {
			RwV3d vec_bc, vec_bo;
			Subtract(&vec_bc, &vec_ac, &vec_ab);
			if (Dot(&vec_ab, &vec_bc) > lbl_8042DFD4) {
				Subtract(&vec_bo, &vec_ao, &vec_ab);
				if (Dot(&vec_ab, &vec_bo) < lbl_8042DFD4)
					across = 1;
				else if (Dot(&vec_bc, &vec_bo) > lbl_8042DFD4)
					across = 3;
				else
					across = 5;
			} else
				across = 5;
		} else
			across = 1;
	} else if (s + t > lbl_8042DFD8)
		across = 3;
	else
		across = 0;
	switch (across) {
		case 0:
			coliVec.x = -vec_po.x;
			coliVec.y = -vec_po.y;
			coliVec.z = -vec_po.z;
			break;
		case 4:
			if (lbl_8042DFD0 + sphere_rad * sphere_rad < Dot(&vec_ao, &vec_ao))
				return 0;
			coliVec.x = -vec_ao.x;
			coliVec.y = -vec_ao.y;
			coliVec.z = -vec_ao.z;
			break;
		case 5:
			Subtract(&vec_ao, &vec_ao, &vec_ab);
			if (lbl_8042DFD0 + sphere_rad * sphere_rad < Dot(&vec_ao, &vec_ao))
				return 0;
			coliVec.x = -vec_ao.x;
			coliVec.y = -vec_ao.y;
			coliVec.z = -vec_ao.z;
			break;
		case 6:
			Subtract(&vec_ao, &vec_ao, &vec_ac);
			if (lbl_8042DFD0 + sphere_rad * sphere_rad < Dot(&vec_ao, &vec_ao))
				return 0;
			coliVec.x = -vec_ao.x;
			coliVec.y = -vec_ao.y;
			coliVec.z = -vec_ao.z;
			break;
		case 1: {
			if (lbl_8042DFD0 + sphere_rad * sphere_rad < clDistanceP2V2(&vec_ao, &vec_ab))
				return 0;
			RwV3d vec_ap;
			Subtract(&vec_ap, (const VectorComponents*)&vec_ao, (const VectorComponents*)&vec_po);
			clDistanceP2V2_ans(&vec_ap, &vec_ab, (RwV3d*)&ans);
			Subtract(&coliVec, &ans, &vec_ao);
			break;
		}
		case 2: {
			if (lbl_8042DFD0 + sphere_rad * sphere_rad < clDistanceP2V2(&vec_ao, &vec_ac))
				return 0;
			RwV3d vec_ap;
			Subtract(&vec_ap, (const VectorComponents*)&vec_ao, (const VectorComponents*)&vec_po);
			clDistanceP2V2_ans(&vec_ap, &vec_ac, (RwV3d*)&ans);
			Subtract(&coliVec, &ans, &vec_ao);
			break;
		}
		case 3: {
			Subtract(&vec_ao, &vec_ao, &vec_ab);
			Subtract(&vec_ac, &vec_ac, &vec_ab);
			if (lbl_8042DFD0 + sphere_rad * sphere_rad < clDistanceP2V2(&vec_ao, &vec_ac))
				return 0;
			RwV3d vec_bp;
			Subtract(&vec_bp, (const VectorComponents*)&vec_ao, (const VectorComponents*)&vec_po);
			clDistanceP2V2_ans(&vec_bp, &vec_ac, (RwV3d*)&ans);
			Subtract(&coliVec, &ans, &vec_ao);
			break;
		}
	}
	if (push_vec) {
		f32 coef = fn_801991B4(&coliVec) / sphere_rad - lbl_8042DFD8;
		Scale(push_vec, &coliVec, coef);
	}
	if (coli_vec) {
		coli_vec->x = coliVec.x;
		coli_vec->y = coliVec.y;
		coli_vec->z = coliVec.z;
	}
	return 1;
}

static s32 clIntersectTriangle(
    const RwV3d* line_pos, const RwV3d* line_vec, RwV3d* tri_vertex, f32* t)
{
	RwV3d ao, ab, ac, crsP0, crsP1;
	Subtract(&ab, tri_vertex + 1, tri_vertex);
	Subtract(&ac, tri_vertex + 2, tri_vertex);
	Cross(&crsP0, line_vec, &ac);
	f32 det = Dot(&ab, &crsP0);
	if (det < 0.0001)
		return 0;
	Subtract(&ao, line_pos, tri_vertex);
	f32 u = Dot(&ao, &crsP0);
	if (u < lbl_8042DFD4)
		return 0;
	if (u > det)
		return 0;
	Cross(&crsP1, &ao, &ab);
	f32 v = Dot(line_vec, &crsP1);
	if (v < lbl_8042DFD4)
		return 0;
	if (u + v > det)
		return 0;
	if (t) {
		*t = Dot(&ac, &crsP1);
		*t /= det;
	}
	return 1;
}

static s32 clIntersectTriangleY(
    const RwV3d* line_pos, const RwV3d* line_vec, RwV3d* tri_vertex, f32* t)
{
	RwV3d ao, ab, ac, crsP1;
	Subtract(&ab, tri_vertex + 1, tri_vertex);
	Subtract(&ac, tri_vertex + 2, tri_vertex);
	f32 cx  = line_vec->y * ac.z;
	f32 cz  = -line_vec->y * ac.x;
	f32 det = ab.x * cx + ab.z * cz;
	if (det < 0.0001)
		return 0;
	Subtract(&ao, line_pos, tri_vertex);
	f32 u = ao.x * cx + ao.z * cz;
	if (u < lbl_8042DFD4)
		return 0;
	if (u > det)
		return 0;
	Cross(&crsP1, &ao, &ab);
	f32 v = line_vec->y * crsP1.y;
	if (v < lbl_8042DFD4)
		return 0;
	if (u + v > det)
		return 0;
	if (t) {
		*t = Dot(&ac, &crsP1);
		*t /= det;
	}
	return 1;
}

s32 clDetectLS2T(
    const RwV3d* line_pos, const RwV3d* line_vec, RwV3d* tri_vertex, RwV3d* ans, u32* bits_across)
{
	f32 t;
	if (clIntersectTriangle(line_pos, line_vec, tri_vertex, &t)) {
		if (t < lbl_8042DFD4 || t > lbl_8042DFD8) {
			*bits_across = 0x80;
			return 0;
		}
		if (ans) {
			ans->x       = line_pos->x + line_vec->x * t;
			ans->y       = line_pos->y + line_vec->y * t;
			ans->z       = line_pos->z + line_vec->z * t;
			*bits_across = 1;
			return 1;
		}
	} else {
		*bits_across = 0x80;
		return 0;
	}
	return 0;
}

s32 clDetectLSY2T(
    const RwV3d* line_pos, const RwV3d* line_vec, RwV3d* tri_vertex, RwV3d* ans, u32* bits_across)
{
	f32 t;
	if (clIntersectTriangleY(line_pos, line_vec, tri_vertex, &t)) {
		if (t < lbl_8042DFD4 || t > lbl_8042DFD8) {
			*bits_across = 0x80;
			return 0;
		}
		if (ans) {
			ans->x       = line_pos->x;
			ans->y       = line_pos->y + line_vec->y * t;
			ans->z       = line_pos->z;
			*bits_across = 1;
			return 1;
		}
	} else {
		*bits_across = 0x80;
		return 0;
	}
	return 0;
}

s32 clIsCrossLS2VonPlane(
    const RwV3d* line_pos, const RwV3d* line_vec, const RwV3d* vector, RwV3d* ans)
{
	RwV3d crsP0, crsP1, vec_bp;
	Cross(&crsP0, vector, line_pos);
	((VectorComponents*)&vec_bp)->x = ((const VectorComponents*)vector)->x
	    - ((const VectorComponents*)line_pos)->x - line_vec->x;
	((VectorComponents*)&vec_bp)->y = ((const VectorComponents*)vector)->y
	    - ((const VectorComponents*)line_pos)->y - line_vec->y;
	((VectorComponents*)&vec_bp)->z = ((const VectorComponents*)vector)->z
	    - ((const VectorComponents*)line_pos)->z - line_vec->z;
	Cross(&crsP1, vector, &vec_bp);
	if ((crsP0.x * crsP1.x < lbl_8042DFD4
	        && ((f32)__fabs(crsP0.x) > 0.0001 || (f32)__fabs(crsP1.x) > 0.0001))
	    || (crsP0.y * crsP1.y < lbl_8042DFD4
	        && ((f32)__fabs(crsP0.y) > 0.0001 || (f32)__fabs(crsP1.y) > 0.0001))
	    || (crsP0.z * crsP1.z < lbl_8042DFD4
	        && ((f32)__fabs(crsP0.z) > 0.0001 || (f32)__fabs(crsP1.z) > 0.0001)))
		return 0;
	((VectorComponents*)&crsP0)->x = line_vec->z * line_pos->y - line_vec->y * line_pos->z;
	((VectorComponents*)&crsP0)->y = line_vec->x * line_pos->z - line_vec->z * line_pos->x;
	((VectorComponents*)&crsP0)->z = line_vec->y * line_pos->x - line_vec->x * line_pos->y;
	((VectorComponents*)&crsP1)->x = line_vec->z * vec_bp.y - line_vec->y * vec_bp.z;
	((VectorComponents*)&crsP1)->y = line_vec->x * vec_bp.z - line_vec->z * vec_bp.x;
	((VectorComponents*)&crsP1)->z = line_vec->y * vec_bp.x - line_vec->x * vec_bp.y;
	if ((crsP0.x * crsP1.x >= lbl_8042DFD4
	        || ((f32)__fabs(crsP0.x) < 0.0001 && (f32)__fabs(crsP1.x) < 0.0001))
	    && (crsP0.y * crsP1.y >= lbl_8042DFD4
	        || ((f32)__fabs(crsP0.y) < 0.0001 && (f32)__fabs(crsP1.y) < 0.0001))
	    && (crsP0.z * crsP1.z >= lbl_8042DFD4
	        || ((f32)__fabs(crsP0.z) < 0.0001 && (f32)__fabs(crsP1.z) < 0.0001))) {
		if (ans) {
			f32 t;
			if ((f32)__fabs(crsP0.y) >= 0.0001 && (f32)__fabs(crsP1.y) >= 0.0001) {
				t = crsP0.y / (crsP0.y + crsP1.y);
				Scale(ans, vector, t);
			} else if ((f32)__fabs(crsP0.z) >= 0.0001 && (f32)__fabs(crsP1.z) >= 0.0001) {
				t = crsP0.z / (crsP0.z + crsP1.z);
				Scale(ans, vector, t);
			} else if ((f32)__fabs(crsP0.x) >= 0.0001 && (f32)__fabs(crsP1.x) >= 0.0001) {
				t = crsP0.x / (crsP0.x + crsP1.x);
				Scale(ans, vector, t);
			} else {
				f32 OAOP = Dot(line_pos, vector), lOPl2 = Dot(vector, vector);
				if (OAOP > lbl_8042DFD4) {
					if (OAOP >= lOPl2) {
						ans->x = vector->x;
						ans->y = vector->y;
						ans->z = vector->z;
					} else {
						t = OAOP / lOPl2;
						Scale(ans, vector, t);
					}
				} else {
					ans->x = ans->y = ans->z = lbl_8042DFD4;
				}
			}
		}
		return 1;
	}
	return 0;
}

void clGetTriangleVectorCoef_CrsP(RwV3d* ab, RwV3d* ac, RwV3d* ap, RwV3d* crsP, f32* s, f32* t)
{
	if ((f32)__fabs(crsP->y) > lbl_8042DFD0) {
		*t = ab->z * ap->x - ab->x * ap->z;
		*t /= crsP->y;
		if ((f32)__fabs(ab->x) > lbl_8042DFD0)
			*s = (ap->x - ac->x * *t) / ab->x;
		else if ((f32)__fabs(ab->z) > lbl_8042DFD0)
			*s = (ap->z - ac->z * *t) / ab->z;
		else
			for (;;) {
			}
	} else if ((f32)__fabs(crsP->z) > lbl_8042DFD0) {
		*t = ab->y * ap->x - ab->x * ap->y;
		*t /= -crsP->z;
		if ((f32)__fabs(ab->y) > lbl_8042DFD0)
			*s = (ap->y - ac->y * *t) / ab->y;
		else if ((f32)__fabs(ab->x) > lbl_8042DFD0)
			*s = (ap->x - ac->x * *t) / ab->x;
		else
			for (;;) {
			}
	} else if ((f32)__fabs(crsP->x) > lbl_8042DFD0) {
		*t = ab->z * ap->y - ab->y * ap->z;
		*t /= -crsP->x;
		if ((f32)__fabs(ab->z) > lbl_8042DFD0)
			*s = (ap->z - ac->z * *t) / ab->z;
		else if ((f32)__fabs(ab->y) > lbl_8042DFD0)
			*s = (ap->y - ac->y * *t) / ab->y;
		else
			for (;;) {
			}
	} else {
		*s = -1.0f;
		*t = -1.0f;
	}
}

f32 clDistanceP2L2(RwV3d* point_pos, RwV3d* line_pos, RwV3d* line_vec, RwV3d* ans_pos)
{
	RwV3d tmpvec;
	f32 CDCA, lCDl2, u, x, y, z;
	Subtract(&tmpvec, point_pos, line_pos);
	CDCA  = Dot(line_vec, &tmpvec);
	lCDl2 = Dot(line_vec, line_vec);
	if (lCDl2 < lbl_8042DFD0) {
		x = line_pos->x - point_pos->x;
		x = x * x;
		y = line_pos->y - point_pos->y;
		y = y * y;
		z = line_pos->z - point_pos->z;
		z = z * z;
		return z + (x + y);
	}
	u = CDCA / lCDl2;
	Scale(&tmpvec, line_vec, u);
	Add(&tmpvec, &tmpvec, line_pos);
	if (ans_pos) {
		ans_pos->x = tmpvec.x;
		ans_pos->y = tmpvec.y;
		ans_pos->z = tmpvec.z;
	}
	Subtract(&tmpvec, &tmpvec, point_pos);
	return Dot(&tmpvec, &tmpvec);
}

const __declspec(section ".sdata2") f32 lbl_8042DFD0 = 0.000123f;
const __declspec(section ".sdata2") f32 lbl_8042DFD4 = 0.0f;
const __declspec(section ".sdata2") f32 lbl_8042DFD8 = 1.0f;
