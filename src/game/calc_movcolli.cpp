#include "game/calc_movcolli.h"
// Complete GameCube moving-collision unit, 0x800D2ED4--0x800D52AC.
// NonMatching: typed control-flow reconstruction under native comparison.
// Names and signatures correlated with C++ symbolic metadata; behavior is GameCube.
extern "C" f32 fn_801991B4(const RwV3d*);
extern "C" f32 fn_80199248(f32);
extern "C" f64 __fabs(f64);
extern "C" f64 __frsqrte(f64);
s32 clDetectS2T(const RwV3d*, f32, RwV3d*, RwV3d*, RwV3d*);
s32 clIsCrossLS2VonPlane(const RwV3d*, const RwV3d*, const RwV3d*, RwV3d*);
void clGetTriangleVectorCoef_CrsP(RwV3d*, RwV3d*, RwV3d*, RwV3d*, f32*, f32*);
extern const __declspec(section ".sdata2") f32 lbl_8042DFE8;
extern const __declspec(section ".sdata2") f32 lbl_8042DFEC;
extern const __declspec(section ".sdata2") f32 lbl_8042DFF0;
extern const __declspec(section ".sdata2") f32 lbl_8042DFF4;
extern const __declspec(section ".sdata2") f64 lbl_8042DFF8;
extern const __declspec(section ".sdata2") f64 lbl_8042E000;
enum ENUM_CL_MOVING clDetectMS2T(const RwV3d* sphere_pos, f32 sphere_rad, const RwV3d* sphere_vec,
    RwV3d* tri_vertex, RwV3d* ans_vec, RwV3d* coli_pos, s16* pOn_Edge)
{
	RwV3d vec_ao;
	RwV3d vec_ab;
	RwV3d vec_ac;
	RwV3d vec_oq;
	RwV3d vec_av__;
	RwV3d crsP;
	RwV3d vec_ov_;
	RwV3d coliVec;
	RwV3d ansVec;
	RwV3d vec_aq;
	RwV3d vec_oq_;
	RwV3d vec_av_;
	RwV3d vec_q_q;
	RwV3d sp70;
	RwV3d sp64;
	RwV3d sp58;
	RwV3d sp4C;
	RwV3d sp40;
	RwV3d sp34;
	RwV3d sp28;
	RwV3d sp1C;
	RwV3d sp10;
	f32 s;
	f32 t;
	enum ENUM_CL_MOVING temp_r3;
	enum ENUM_CL_MOVING temp_r3_2;
	enum ENUM_CL_MOVING temp_r3_3;
	enum ENUM_CL_MOVING var_r3;
	f32 temp_f0;
	f32 temp_f0_10;
	f32 temp_f0_11;
	f32 temp_f0_12;
	f32 temp_f0_13;
	f32 temp_f0_14;
	f32 temp_f0_15;
	f32 temp_f0_2;
	f32 temp_f0_3;
	f32 temp_f0_4;
	f32 temp_f0_5;
	f32 temp_f0_6;
	f32 temp_f0_7;
	f32 temp_f0_8;
	f32 temp_f0_9;
	f32 temp_f10;
	f32 temp_f10_2;
	f32 temp_f11;
	f32 temp_f11_2;
	f32 temp_f12;
	f32 temp_f13;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f1_5;
	f32 temp_f1_6;
	f32 temp_f1_7;
	f32 temp_f1_8;
	f32 temp_f29;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f2_3;
	f32 temp_f30;
	f32 temp_f3;
	f32 temp_f3_2;
	f32 temp_f3_3;
	f32 temp_f3_4;
	f32 temp_f3_5;
	f32 temp_f3_6;
	f32 temp_f4;
	f32 temp_f4_2;
	f32 temp_f4_3;
	f32 temp_f4_4;
	f32 temp_f4_5;
	f32 temp_f4_6;
	f32 temp_f5;
	f32 temp_f5_2;
	f32 temp_f5_3;
	f32 temp_f5_4;
	f32 temp_f6;
	f32 temp_f6_2;
	f32 temp_f6_3;
	f32 temp_f7;
	f32 temp_f7_2;
	f32 temp_f8;
	f32 temp_f8_2;
	f32 temp_f9;
	f32 temp_f9_2;
	f32 var_f2;
	f32 var_f3;
	s32 temp_cr0_lt;
	s32 var_r3_2;

	var_r3_2    = 0;
	temp_f30    = lbl_8042DFE8 + sphere_rad;
	temp_f0     = sphere_pos->y;
	var_f3      = temp_f0 - temp_f30;
	var_f2      = temp_f0 + temp_f30;
	temp_f1     = sphere_vec->y;
	temp_cr0_lt = temp_f1 < lbl_8042DFEC;
	if (temp_cr0_lt != 0) {
		var_f3 += temp_f1;
	}
	if (temp_cr0_lt == 0) {
		var_f2 += temp_f1;
	}
	temp_f0_2 = tri_vertex->y;
	if (temp_f0_2 < var_f3) {
		var_r3_2 = 1;
		goto block_7;
	}
	if (!(temp_f0_2 <= var_f2)) {
	block_7:
		temp_f0_3 = tri_vertex[1].y;
		if (temp_f0_3 < var_f3) {
			if (var_r3_2 != 0) {
				goto block_12;
			}
			goto block_18;
		}
		if ((temp_f0_3 > var_f2) && (var_r3_2 == 0)) {
		block_12:
			temp_f0_4 = tri_vertex[2].y;
			if (temp_f0_4 < var_f3) {
				if (var_r3_2 != 0) {
					return CL_MOVING_NONE;
				}
				goto block_18;
			}
			if ((temp_f0_4 > var_f2) && (var_r3_2 == 0)) {
				return CL_MOVING_NONE;
			}
			goto block_18;
		}
		goto block_18;
	}
block_18:
	temp_f0_5 = sphere_vec->z;
	temp_f0_6 = sphere_vec->x;
	temp_f0_7 = sphere_vec->y;
	if (((temp_f0_5 * temp_f0_5) + ((temp_f0_6 * temp_f0_6) + (temp_f0_7 * temp_f0_7)))
	    < lbl_8042DFE8) {
		if (clDetectS2T(sphere_pos, sphere_rad, tri_vertex, &ansVec, &coliVec) != 0) {
			if (coli_pos != NULL) {
				coli_pos->x = sphere_pos->x + coliVec.x;
				coli_pos->y = sphere_pos->y + coliVec.y;
				coli_pos->z = sphere_pos->z + coliVec.z;
			}
			if ((f32)__fabs(fn_801991B4(&coliVec) - sphere_rad) <= lbl_8042DFE8) {
				if (ans_vec != NULL) {
					ans_vec->z = lbl_8042DFEC;
					ans_vec->y = lbl_8042DFEC;
					ans_vec->x = lbl_8042DFEC;
				}
				return CL_MOVING_COLLISION;
			}
			if (ans_vec != NULL) {
				ans_vec->x = ansVec.x;
				ans_vec->y = ansVec.y;
				ans_vec->z = ansVec.z;
			}
			return CL_MOVING_INTERSECTION;
		}
		return CL_MOVING_NONE;
	}
	temp_f11  = tri_vertex->x;
	temp_f10  = tri_vertex[1].x - temp_f11;
	vec_ab.x  = temp_f10;
	temp_f9   = tri_vertex->y;
	temp_f8   = tri_vertex[1].y - temp_f9;
	vec_ab.y  = temp_f8;
	temp_f7   = tri_vertex->z;
	temp_f5   = tri_vertex[1].z - temp_f7;
	vec_ab.z  = temp_f5;
	temp_f4   = tri_vertex[2].x - temp_f11;
	vec_ac.x  = temp_f4;
	temp_f3   = tri_vertex[2].y - temp_f9;
	vec_ac.y  = temp_f3;
	temp_f2   = tri_vertex[2].z - temp_f7;
	vec_ac.z  = temp_f2;
	temp_f6   = (temp_f8 * temp_f2) - (temp_f5 * temp_f3);
	crsP.x    = temp_f6;
	temp_f5_2 = (temp_f5 * temp_f4) - (temp_f10 * temp_f2);
	crsP.y    = temp_f5_2;
	temp_f4_2 = (temp_f10 * temp_f3) - (temp_f8 * temp_f4);
	crsP.z    = temp_f4_2;
	temp_f1_2 = sphere_pos->x - temp_f11;
	vec_ao.x  = temp_f1_2;
	temp_f3_2 = sphere_pos->y - temp_f9;
	vec_ao.y  = temp_f3_2;
	temp_f0_8 = sphere_pos->z - temp_f7;
	vec_ao.z  = temp_f0_8;
	temp_f1_3
	    = fn_80199248((temp_f4_2 * temp_f4_2) + ((temp_f6 * temp_f6) + (temp_f5_2 * temp_f5_2)));
	temp_f3_3
	    = ((temp_f0_8 * temp_f4_2) + ((temp_f1_2 * temp_f6) + (temp_f3_2 * temp_f5_2))) * temp_f1_3;
	if (temp_f3_3 <= -sphere_rad) {
		return CL_MOVING_NONE;
	}
	temp_f4_3 = -(temp_f1_3 * temp_f3_3);
	temp_f2_2 = crsP.x * temp_f4_3;
	vec_oq.x  = temp_f2_2;
	temp_f1_4 = crsP.y * temp_f4_3;
	vec_oq.y  = temp_f1_4;
	temp_f0_9 = crsP.z * temp_f4_3;
	vec_oq.z  = temp_f0_9;
	temp_f29  = (f32)__fabs(temp_f3_3);
	if (temp_f29 <= temp_f30) {
		vec_aq.x = vec_ao.x + temp_f2_2;
		vec_aq.y = vec_ao.y + temp_f1_4;
		vec_aq.z = vec_ao.z + temp_f0_9;
		clGetTriangleVectorCoef_CrsP(&vec_ab, &vec_ac, &vec_aq, &crsP, &s, &t);
		if ((s >= lbl_8042DFEC) && (t >= lbl_8042DFEC) && ((s + t) <= lbl_8042DFF0)) {
			if (coli_pos != NULL) {
				coli_pos->x = tri_vertex->x + vec_aq.x;
				coli_pos->y = tri_vertex->y + vec_aq.y;
				coli_pos->z = tri_vertex->z + vec_aq.z;
			}
			if ((f32)__fabs(temp_f29 - sphere_rad) <= lbl_8042DFE8) {
				if (ans_vec != NULL) {
					ans_vec->z = lbl_8042DFEC;
					ans_vec->y = lbl_8042DFEC;
					ans_vec->x = lbl_8042DFEC;
				}
				return CL_MOVING_COLLISION;
			}
			if (ans_vec != NULL) {
				if (temp_f29 < lbl_8042DFE8) {
					temp_f1_5  = sphere_rad * temp_f1_3;
					ans_vec->x = crsP.x * temp_f1_5;
					ans_vec->y = crsP.y * temp_f1_5;
					ans_vec->z = crsP.z * temp_f1_5;
				} else {
					temp_f1_6  = -(sphere_rad - temp_f29) / temp_f29;
					ans_vec->x = vec_oq.x * temp_f1_6;
					ans_vec->y = vec_oq.y * temp_f1_6;
					ans_vec->z = vec_oq.z * temp_f1_6;
				}
			}
			return CL_MOVING_INTERSECTION;
		}
		goto block_61;
	}
	if (temp_f29 < lbl_8042DFE8) {
		return CL_MOVING_NONE;
	}
	temp_f3_4  = (temp_f29 - sphere_rad) / temp_f29;
	temp_f11_2 = temp_f2_2 * temp_f3_4;
	vec_oq_.x  = temp_f11_2;
	temp_f10_2 = temp_f1_4 * temp_f3_4;
	vec_oq_.y  = temp_f10_2;
	temp_f9_2  = temp_f0_9 * temp_f3_4;
	vec_oq_.z  = temp_f9_2;
	temp_f8_2  = sphere_vec->z;
	temp_f12   = sphere_vec->x;
	temp_f7_2  = sphere_vec->y;
	temp_f13   = (temp_f9_2 * temp_f8_2) + ((temp_f11_2 * temp_f12) + (temp_f10_2 * temp_f7_2));
	temp_f4_4  = (temp_f9_2 * temp_f9_2) + ((temp_f11_2 * temp_f11_2) + (temp_f10_2 * temp_f10_2));
	if (temp_f13 <= lbl_8042DFF4) {
		return CL_MOVING_NONE;
	}
	if (temp_f4_4 >= (lbl_8042DFE8 + temp_f13)) {
		return CL_MOVING_NONE;
	}
	temp_f3_5  = temp_f4_4 / temp_f13;
	temp_f6_2  = temp_f12 * temp_f3_5;
	vec_ov_.x  = temp_f6_2;
	temp_f5_3  = temp_f7_2 * temp_f3_5;
	vec_ov_.y  = temp_f5_3;
	temp_f4_5  = temp_f8_2 * temp_f3_5;
	vec_ov_.z  = temp_f4_5;
	temp_f6_3  = vec_ao.x + temp_f6_2;
	vec_av_.x  = temp_f6_3;
	temp_f5_4  = vec_ao.y + temp_f5_3;
	vec_av_.y  = temp_f5_4;
	temp_f4_6  = vec_ao.z + temp_f4_5;
	vec_av_.z  = temp_f4_6;
	temp_f3_6  = temp_f2_2 - temp_f11_2;
	vec_q_q.x  = temp_f3_6;
	temp_f2_3  = temp_f1_4 - temp_f10_2;
	vec_q_q.y  = temp_f2_3;
	temp_f1_7  = temp_f0_9 - temp_f9_2;
	vec_q_q.z  = temp_f1_7;
	vec_av__.x = temp_f6_3 + temp_f3_6;
	vec_av__.y = temp_f5_4 + temp_f2_3;
	vec_av__.z = temp_f4_6 + temp_f1_7;
	clGetTriangleVectorCoef_CrsP(&vec_ab, &vec_ac, &vec_av__, &crsP, &s, &t);
	if ((s >= lbl_8042DFEC) && (t >= lbl_8042DFEC) && ((s + t) <= lbl_8042DFF0)) {
		if (coli_pos != NULL) {
			coli_pos->x = tri_vertex->x + vec_av__.x;
			coli_pos->y = tri_vertex->y + vec_av__.y;
			coli_pos->z = tri_vertex->z + vec_av__.z;
		}
		if (ans_vec != NULL) {
			ans_vec->x = vec_ov_.x;
			ans_vec->y = vec_ov_.y;
			ans_vec->z = vec_ov_.z;
		}
		return CL_MOVING_COLLISION;
	}
block_61:
	if (s < lbl_8042DFEC) {
		if (t < lbl_8042DFEC) {
			temp_r3_3
			    = clDetectMS2LS_(&vec_ao, sphere_rad, sphere_vec, &vec_ab, &crsP, &sp70, &sp58);
			if (temp_r3_3 == CL_MOVING_INTERSECTION) {
				if (coli_pos != NULL) {
					coli_pos->x = sp58.x + tri_vertex->x;
					coli_pos->y = sp58.y + tri_vertex->y;
					coli_pos->z = sp58.z + tri_vertex->z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp70.x;
					ans_vec->y = sp70.y;
					ans_vec->z = sp70.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x10;
				}
				return temp_r3_3;
			}
			var_r3
			    = clDetectMS2LS_(&vec_ao, sphere_rad, sphere_vec, &vec_ac, &crsP, &sp64, coli_pos);
			if ((var_r3 == CL_MOVING_INTERSECTION)
			    || ((temp_r3_3 == CL_MOVING_NONE) && (var_r3 == CL_MOVING_COLLISION))) {
				if (coli_pos != NULL) {
					coli_pos->x += tri_vertex->x;
					coli_pos->y += tri_vertex->y;
					coli_pos->z += tri_vertex->z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp64.x;
					ans_vec->y = sp64.y;
					ans_vec->z = sp64.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x40;
					return var_r3;
				}
				return var_r3;
			}
			if ((temp_r3_3 == CL_MOVING_NONE) && (var_r3 == CL_MOVING_NONE)) {
				return CL_MOVING_NONE;
			}
			if ((temp_r3_3 == CL_MOVING_COLLISION) && (var_r3 == CL_MOVING_NONE)) {
				if (coli_pos != NULL) {
					coli_pos->x = sp58.x + tri_vertex->x;
					coli_pos->y = sp58.y + tri_vertex->y;
					coli_pos->z = sp58.z + tri_vertex->z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp70.x;
					ans_vec->y = sp70.y;
					ans_vec->z = sp70.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x10;
				}
				return temp_r3_3;
			}
			temp_f0_10 = sp70.x;
			temp_f0_11 = sp64.x;
			if (((sp70.z * sp70.z) + ((temp_f0_10 * temp_f0_10) + (sp70.y * sp70.y)))
			    <= ((sp64.z * sp64.z) + ((temp_f0_11 * temp_f0_11) + (sp64.y * sp64.y)))) {
				if (coli_pos != NULL) {
					coli_pos->x = sp58.x + tri_vertex->x;
					coli_pos->y = sp58.y + tri_vertex->y;
					coli_pos->z = sp58.z + tri_vertex->z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp70.x;
					ans_vec->y = sp70.y;
					ans_vec->z = sp70.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x10;
				}
				return temp_r3_3;
			}
			if (coli_pos != NULL) {
				coli_pos->x += tri_vertex->x;
				coli_pos->y += tri_vertex->y;
				coli_pos->z += tri_vertex->z;
			}
			if (ans_vec != NULL) {
				ans_vec->x = sp64.x;
				ans_vec->y = sp64.y;
				ans_vec->z = sp64.z;
			}
			if (pOn_Edge != NULL) {
				*pOn_Edge |= 0x40;
				return var_r3;
			}
			return var_r3;
		}
		if ((s + t) > lbl_8042DFF0) {
			temp_f1_8 = vec_ac.x;
			vec_ab.x  = vec_ab.x - temp_f1_8;
			vec_ab.y -= vec_ac.y;
			vec_ab.z -= vec_ac.z;
			vec_ao.x = vec_ao.x - temp_f1_8;
			vec_ao.y -= vec_ac.y;
			vec_ao.z -= vec_ac.z;
			temp_r3_2 = clDetectMS2LS_(
			    (RwV3d*)&vec_ao, sphere_rad, sphere_vec, (RwV3d*)&vec_ab, &crsP, &sp4C, &sp34);
			if (temp_r3_2 == CL_MOVING_INTERSECTION) {
				if (coli_pos != NULL) {
					coli_pos->x = sp34.x + tri_vertex[2].x;
					coli_pos->y = sp34.y + tri_vertex[2].y;
					coli_pos->z = sp34.z + tri_vertex[2].z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp4C.x;
					ans_vec->y = sp4C.y;
					ans_vec->z = sp4C.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x20;
				}
				return temp_r3_2;
			}
			vec_ac.x = -vec_ac.x;
			vec_ac.y = -vec_ac.y;
			vec_ac.z = -vec_ac.z;
			var_r3   = clDetectMS2LS_(
			    (RwV3d*)&vec_ao, sphere_rad, sphere_vec, (RwV3d*)&vec_ac, &crsP, &sp40, coli_pos);
			if ((var_r3 == CL_MOVING_INTERSECTION)
			    || ((temp_r3_2 == CL_MOVING_NONE) && (var_r3 == CL_MOVING_COLLISION))) {
				if (coli_pos != NULL) {
					coli_pos->x += tri_vertex[2].x;
					coli_pos->y += tri_vertex[2].y;
					coli_pos->z += tri_vertex[2].z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp40.x;
					ans_vec->y = sp40.y;
					ans_vec->z = sp40.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x40;
					return var_r3;
				}
				return var_r3;
			}
			if ((temp_r3_2 == CL_MOVING_NONE) && (var_r3 == CL_MOVING_NONE)) {
				return CL_MOVING_NONE;
			}
			if ((temp_r3_2 == CL_MOVING_COLLISION) && (var_r3 == CL_MOVING_NONE)) {
				if (coli_pos != NULL) {
					coli_pos->x = sp34.x + tri_vertex[2].x;
					coli_pos->y = sp34.y + tri_vertex[2].y;
					coli_pos->z = sp34.z + tri_vertex[2].z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp4C.x;
					ans_vec->y = sp4C.y;
					ans_vec->z = sp4C.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x20;
				}
				return temp_r3_2;
			}
			temp_f0_12 = sp4C.x;
			temp_f0_13 = sp40.x;
			if (((sp4C.z * sp4C.z) + ((temp_f0_12 * temp_f0_12) + (sp4C.y * sp4C.y)))
			    <= ((sp40.z * sp40.z) + ((temp_f0_13 * temp_f0_13) + (sp40.y * sp40.y)))) {
				if (coli_pos != NULL) {
					coli_pos->x = sp34.x + tri_vertex[2].x;
					coli_pos->y = sp34.y + tri_vertex[2].y;
					coli_pos->z = sp34.z + tri_vertex[2].z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp4C.x;
					ans_vec->y = sp4C.y;
					ans_vec->z = sp4C.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x20;
				}
				return temp_r3_2;
			}
			if (coli_pos != NULL) {
				coli_pos->x += tri_vertex[2].x;
				coli_pos->y += tri_vertex[2].y;
				coli_pos->z += tri_vertex[2].z;
			}
			if (ans_vec != NULL) {
				ans_vec->x = sp40.x;
				ans_vec->y = sp40.y;
				ans_vec->z = sp40.z;
			}
			if (pOn_Edge != NULL) {
				*pOn_Edge |= 0x40;
				return var_r3;
			}
			return var_r3;
		}
		var_r3 = clDetectMS2LS_(
		    (RwV3d*)&vec_ao, sphere_rad, sphere_vec, (RwV3d*)&vec_ac, &crsP, ans_vec, coli_pos);
		if (var_r3 != CL_MOVING_NONE) {
			if (coli_pos != NULL) {
				coli_pos->x += tri_vertex->x;
				coli_pos->y += tri_vertex->y;
				coli_pos->z += tri_vertex->z;
			}
			if (pOn_Edge != NULL) {
				*pOn_Edge |= 0x40;
			}
			return var_r3;
		}
		return var_r3;
	}
	if (t < lbl_8042DFEC) {
		if ((s + t) > lbl_8042DFF0) {
			vec_ac.x -= vec_ab.x;
			vec_ac.y -= vec_ab.y;
			vec_ac.z -= vec_ab.z;
			vec_ao.x -= vec_ab.x;
			vec_ao.y -= vec_ab.y;
			vec_ao.z -= vec_ab.z;
			temp_r3 = clDetectMS2LS_(
			    (RwV3d*)&vec_ao, sphere_rad, sphere_vec, (RwV3d*)&vec_ac, &crsP, &sp28, &sp10);
			if (temp_r3 == CL_MOVING_INTERSECTION) {
				if (coli_pos != NULL) {
					coli_pos->x = sp10.x + tri_vertex[1].x;
					coli_pos->y = sp10.y + tri_vertex[1].y;
					coli_pos->z = sp10.z + tri_vertex[1].z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp28.x;
					ans_vec->y = sp28.y;
					ans_vec->z = sp28.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x20;
				}
				return temp_r3;
			}
			vec_ab.x = -vec_ab.x;
			vec_ab.y = -vec_ab.y;
			vec_ab.z = -vec_ab.z;
			var_r3   = clDetectMS2LS_(
			    (RwV3d*)&vec_ao, sphere_rad, sphere_vec, (RwV3d*)&vec_ab, &crsP, &sp1C, coli_pos);
			if ((var_r3 == CL_MOVING_INTERSECTION)
			    || ((temp_r3 == CL_MOVING_NONE) && (var_r3 == CL_MOVING_COLLISION))) {
				if (coli_pos != NULL) {
					coli_pos->x += tri_vertex[1].x;
					coli_pos->y += tri_vertex[1].y;
					coli_pos->z += tri_vertex[1].z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp1C.x;
					ans_vec->y = sp1C.y;
					ans_vec->z = sp1C.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x10;
					return var_r3;
				}
				return var_r3;
			}
			if ((temp_r3 == CL_MOVING_NONE) && (var_r3 == CL_MOVING_NONE)) {
				return CL_MOVING_NONE;
			}
			if ((temp_r3 == CL_MOVING_COLLISION) && (var_r3 == CL_MOVING_NONE)) {
				if (coli_pos != NULL) {
					coli_pos->x = sp10.x + tri_vertex[1].x;
					coli_pos->y = sp10.y + tri_vertex[1].y;
					coli_pos->z = sp10.z + tri_vertex[1].z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp28.x;
					ans_vec->y = sp28.y;
					ans_vec->z = sp28.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x20;
				}
				return temp_r3;
			}
			temp_f0_14 = sp28.x;
			temp_f0_15 = sp1C.x;
			if (((sp28.z * sp28.z) + ((temp_f0_14 * temp_f0_14) + (sp28.y * sp28.y)))
			    <= ((sp1C.z * sp1C.z) + ((temp_f0_15 * temp_f0_15) + (sp1C.y * sp1C.y)))) {
				if (coli_pos != NULL) {
					coli_pos->x = sp10.x + tri_vertex[1].x;
					coli_pos->y = sp10.y + tri_vertex[1].y;
					coli_pos->z = sp10.z + tri_vertex[1].z;
				}
				if (ans_vec != NULL) {
					ans_vec->x = sp28.x;
					ans_vec->y = sp28.y;
					ans_vec->z = sp28.z;
				}
				if (pOn_Edge != NULL) {
					*pOn_Edge |= 0x20;
				}
				return temp_r3;
			}
			if (coli_pos != NULL) {
				coli_pos->x += tri_vertex[1].x;
				coli_pos->y += tri_vertex[1].y;
				coli_pos->z += tri_vertex[1].z;
			}
			if (ans_vec != NULL) {
				ans_vec->x = sp1C.x;
				ans_vec->y = sp1C.y;
				ans_vec->z = sp1C.z;
			}
			if (pOn_Edge != NULL) {
				*pOn_Edge |= 0x10;
				return var_r3;
			}
			return var_r3;
		}
		var_r3 = clDetectMS2LS_(
		    (RwV3d*)&vec_ao, sphere_rad, sphere_vec, (RwV3d*)&vec_ab, &crsP, ans_vec, coli_pos);
		if (var_r3 != CL_MOVING_NONE) {
			if (coli_pos != NULL) {
				coli_pos->x += tri_vertex->x;
				coli_pos->y += tri_vertex->y;
				coli_pos->z += tri_vertex->z;
			}
			if (pOn_Edge != NULL) {
				*pOn_Edge |= 0x10;
			}
			return var_r3;
		}
		return var_r3;
	}
	if ((s + t) > lbl_8042DFF0) {
		vec_ac.x -= vec_ab.x;
		vec_ac.y -= vec_ab.y;
		vec_ac.z -= vec_ab.z;
		vec_ao.x -= vec_ab.x;
		vec_ao.y -= vec_ab.y;
		vec_ao.z -= vec_ab.z;
		var_r3 = clDetectMS2LS_(
		    (RwV3d*)&vec_ao, sphere_rad, sphere_vec, (RwV3d*)&vec_ac, &crsP, ans_vec, coli_pos);
		if (var_r3 != CL_MOVING_NONE) {
			if (coli_pos != NULL) {
				coli_pos->x += tri_vertex[1].x;
				coli_pos->y += tri_vertex[1].y;
				coli_pos->z += tri_vertex[1].z;
			}
			if (pOn_Edge != NULL) {
				*pOn_Edge |= 0x20;
			}
			return var_r3;
		}
		return var_r3;
	}
	var_r3 = CL_MOVING_NONE;
	return var_r3;
}

enum ENUM_CL_MOVING clDetectMS2LS_(const RwV3d* sphere_pos, f32 sphere_rad, const RwV3d* sphere_vec,
    const RwV3d* detect_vec, const RwV3d* safe_vec, RwV3d* ans_vec, RwV3d* coli_pos)
{
	RwV3d crsP;
	RwV3d circlePos;
	RwV3d coliPos;
	RwV3d spAC;
	RwV3d spA0;
	RwV3d sp94;
	RwV3d sp88;
	RwV3d sp7C;
	RwV3d sp70;
	RwV3d sp64;
	RwV3d sp58;
	RwV3d sp4C;
	RwV3d sp40;
	RwV3d sp34;
	RwV3d sp28;
	f32 sp24;
	f32 sp20;
	f32 sp1C;
	f32 sp18;
	f32 sp14;
	f32 sp10;
	f32 spC;
	f32 sp8;
	enum ENUM_CL_MOVING var_r31;
	enum ENUM_CL_MOVING var_r3;
	f32 temp_f0_16;
	f32 temp_f0_17;
	f32 temp_f0_18;
	f32 temp_f0_19;
	f32 temp_f0_26;
	f32 temp_f0_27;
	f32 temp_f0_28;
	f32 temp_f0_29;
	f32 temp_f0_39;
	f32 temp_f0_40;
	f32 temp_f0_4;
	f32 temp_f0_5;
	f32 temp_f0_6;
	f32 temp_f0_7;
	f32 temp_f0_8;
	f32 temp_f0_9;
	f32 temp_f10;
	f32 temp_f10_2;
	f32 temp_f10_3;
	f32 temp_f11;
	f32 temp_f11_2;
	f32 temp_f12;
	f32 temp_f12_2;
	f32 temp_f13;
	f32 temp_f13_2;
	f32 temp_f1;
	f32 temp_f1_10;
	f32 temp_f1_11;
	f32 temp_f1_12;
	f32 temp_f1_13;
	f32 temp_f1_14;
	f32 temp_f1_15;
	f32 temp_f1_16;
	f32 temp_f1_17;
	f32 temp_f1_18;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f1_5;
	f32 temp_f1_6;
	f32 temp_f1_7;
	f32 temp_f1_8;
	f32 temp_f1_9;
	f32 temp_f27;
	f32 temp_f28;
	f32 temp_f29;
	f32 temp_f2;
	f32 temp_f2_2;
	f32 temp_f2_3;
	f32 temp_f2_4;
	f32 temp_f2_5;
	f32 temp_f2_6;
	f32 temp_f30;
	f32 temp_f3;
	f32 temp_f3_2;
	f32 temp_f3_3;
	f32 temp_f3_4;
	f32 temp_f3_5;
	f32 temp_f3_6;
	f32 temp_f3_7;
	f32 temp_f4;
	f32 temp_f4_10;
	f32 temp_f4_11;
	f32 temp_f4_12;
	f32 temp_f4_2;
	f32 temp_f4_3;
	f32 temp_f4_4;
	f32 temp_f4_5;
	f32 temp_f4_6;
	f32 temp_f4_7;
	f32 temp_f4_8;
	f32 temp_f4_9;
	f32 temp_f5;
	f32 temp_f5_2;
	f32 temp_f6;
	f32 temp_f6_2;
	f32 temp_f7;
	f32 temp_f7_2;
	f32 temp_f7_3;
	f32 temp_f7_4;
	f32 temp_f7_5;
	f32 temp_f7_6;
	f32 temp_f7_7;
	f32 temp_f8;
	f32 temp_f8_2;
	f32 temp_f8_3;
	f32 temp_f8_4;
	f32 temp_f8_5;
	f32 temp_f9;
	f32 temp_f9_2;
	f32 temp_f9_3;
	f32 var_f1;
	f32 var_f1_2;
	f32 var_f1_3;
	f32 var_f1_4;
	f32 var_f1_5;
	f32 var_f1_6;
	f32 var_f4;
	f32 var_f4_2;
	f64 temp_f0;
	f64 temp_f0_10;
	f64 temp_f0_11;
	f64 temp_f0_12;
	f64 temp_f0_13;
	f64 temp_f0_14;
	f64 temp_f0_15;
	f64 temp_f0_20;
	f64 temp_f0_21;
	f64 temp_f0_22;
	f64 temp_f0_23;
	f64 temp_f0_24;
	f64 temp_f0_25;
	f64 temp_f0_2;
	f64 temp_f0_30;
	f64 temp_f0_31;
	f64 temp_f0_32;
	f64 temp_f0_33;
	f64 temp_f0_34;
	f64 temp_f0_35;
	f64 temp_f0_36;
	f64 temp_f0_37;
	f64 temp_f0_38;
	f64 temp_f0_3;
	s32 ignoreDetectCylinderFlag;

	ignoreDetectCylinderFlag = 0;
	temp_f4                  = detect_vec->z;
	temp_f3                  = detect_vec->x;
	temp_f2                  = detect_vec->y;
	temp_f6                  = (temp_f4 * temp_f4) + ((temp_f3 * temp_f3) + (temp_f2 * temp_f2));
	if (temp_f6 < lbl_8042DFE8) {
		var_r3 = clDetectMS2P_(sphere_pos, sphere_rad, sphere_vec, safe_vec, ans_vec);
		if ((var_r3 != CL_MOVING_NONE) && (coli_pos != NULL)) {
			coli_pos->z = lbl_8042DFEC;
			coli_pos->y = lbl_8042DFEC;
			coli_pos->x = lbl_8042DFEC;
			return var_r3;
		}

		return var_r3;
	}
	temp_f9    = sphere_vec->z;
	temp_f8    = sphere_vec->y;
	temp_f10   = (temp_f2 * temp_f9) - (temp_f4 * temp_f8);
	crsP.x     = temp_f10;
	temp_f7    = sphere_vec->x;
	temp_f9_2  = (temp_f4 * temp_f7) - (temp_f3 * temp_f9);
	crsP.y     = temp_f9_2;
	temp_f8_2  = (temp_f3 * temp_f8) - (temp_f2 * temp_f7);
	crsP.z     = temp_f8_2;
	temp_f13   = sphere_pos->z;
	temp_f12   = sphere_pos->x;
	temp_f11   = sphere_pos->y;
	temp_f1    = (temp_f8_2 * temp_f13) + ((temp_f10 * temp_f12) + (temp_f9_2 * temp_f11));
	temp_f10_2 = (temp_f8_2 * temp_f8_2) + ((temp_f10 * temp_f10) + (temp_f9_2 * temp_f9_2));
	temp_f5    = sphere_rad * sphere_rad;
	if (temp_f10_2 < lbl_8042DFE8) {
		temp_f8_3
		    = ((temp_f4 * temp_f13) + ((temp_f3 * temp_f12) + (temp_f2 * temp_f11))) / temp_f6;
		temp_f3_2 = temp_f3 * temp_f8_3;
		spAC.x    = temp_f3_2;
		temp_f7_2 = temp_f2 * temp_f8_3;
		spAC.y    = temp_f7_2;
		temp_f2_2 = temp_f4 * temp_f8_3;
		spAC.z    = temp_f2_2;
		temp_f3_3 = temp_f12 - temp_f3_2;
		spA0.x    = temp_f3_3;
		temp_f7_3 = temp_f11 - temp_f7_2;
		spA0.y    = temp_f7_3;
		temp_f2_3 = temp_f13 - temp_f2_2;
		spA0.z    = temp_f2_3;
		temp_f4_2 = (temp_f2_3 * temp_f2_3) + ((temp_f3_3 * temp_f3_3) + (temp_f7_3 * temp_f7_3));
		if (temp_f4_2 > temp_f5) {
			return CL_MOVING_NONE;
		}
		if ((lbl_8042DFEC <= temp_f8_3) && (temp_f8_3 <= lbl_8042DFF0)) {
			if (ans_vec != NULL) {
				if (temp_f4_2 < lbl_8042DFE8) {
					if (safe_vec != NULL) {
						temp_f1_2 = fn_801991B4(safe_vec);
						if (temp_f1_2 > lbl_8042DFE8) {
							temp_f1_3  = sphere_rad / temp_f1_2;
							ans_vec->x = safe_vec->x * temp_f1_3;
							ans_vec->y = safe_vec->y * temp_f1_3;
							ans_vec->z = safe_vec->z * temp_f1_3;
						} else {
							ans_vec->z = lbl_8042DFEC;
							ans_vec->y = lbl_8042DFEC;
							ans_vec->x = lbl_8042DFEC;
						}
					} else {
						ans_vec->z = lbl_8042DFEC;
						ans_vec->y = lbl_8042DFEC;
						ans_vec->x = lbl_8042DFEC;
					}
				} else {
					var_f4 = temp_f4_2 / temp_f5;
					if (var_f4 > lbl_8042DFEC) {
						temp_f0   = __frsqrte(var_f4);
						temp_f0_2 = lbl_8042DFF8 * temp_f0
						    * (lbl_8042E000 - ((f64)var_f4 * (temp_f0 * temp_f0)));
						temp_f0_3 = lbl_8042DFF8 * temp_f0_2
						    * (lbl_8042E000 - ((f64)var_f4 * (temp_f0_2 * temp_f0_2)));
						sp24   = (f32)((f64)var_f4
						    * (lbl_8042DFF8 * temp_f0_3
						        * (lbl_8042E000 - ((f64)var_f4 * (temp_f0_3 * temp_f0_3)))));
						var_f4 = sp24;
					}
					temp_f1_4  = lbl_8042DFF0 - var_f4;
					ans_vec->x = spA0.x * temp_f1_4;
					ans_vec->y = spA0.y * temp_f1_4;
					ans_vec->z = spA0.z * temp_f1_4;
				}
			}
			if (coli_pos != NULL) {
				coli_pos->x = spAC.x;
				coli_pos->y = spAC.y;
				coli_pos->z = spAC.z;
			}
			return CL_MOVING_INTERSECTION;
		}
		if (temp_f8_3 < lbl_8042DFEC) {
			var_r3 = clDetectMS2P_(sphere_pos, sphere_rad, sphere_vec, safe_vec, ans_vec);
			if ((var_r3 != CL_MOVING_NONE) && (coli_pos != NULL)) {
				coli_pos->z = lbl_8042DFEC;
				coli_pos->y = lbl_8042DFEC;
				coli_pos->x = lbl_8042DFEC;
				return var_r3;
			}

			return var_r3;
		}
		if (temp_f8_3 > lbl_8042DFEC) {
			sp94.x = sphere_pos->x - detect_vec->x;
			sp94.y = sphere_pos->y - detect_vec->y;
			sp94.z = sphere_pos->z - detect_vec->z;
			var_r3 = clDetectMS2P_(&sp94, sphere_rad, sphere_vec, safe_vec, ans_vec);
			if ((var_r3 != CL_MOVING_NONE) && (coli_pos != NULL)) {
				coli_pos->x = detect_vec->x;
				coli_pos->y = detect_vec->y;
				coli_pos->z = detect_vec->z;
				return var_r3;
			}

			return var_r3;
		}
		goto block_30;
	}
block_30:
	temp_f4_3 = temp_f1 / temp_f10_2;
	temp_f7_4 = temp_f1 * temp_f4_3;
	if (temp_f7_4 > temp_f5) {
		return CL_MOVING_NONE;
	}
	temp_f3_4   = sphere_pos->x - (crsP.x * temp_f4_3);
	circlePos.x = temp_f3_4;
	temp_f2_4   = sphere_pos->y - (crsP.y * temp_f4_3);
	circlePos.y = temp_f2_4;
	temp_f1_5   = sphere_pos->z - (crsP.z * temp_f4_3);
	circlePos.z = temp_f1_5;
	if (temp_f7_4 == temp_f5) {
		if (clIsCrossLS2VonPlane(&circlePos, sphere_vec, detect_vec, &coliPos) != 0) {
			if (coli_pos != NULL) {
				coli_pos->x = coliPos.x;
				coli_pos->y = coliPos.y;
				coli_pos->z = coliPos.z;
			}
			if (ans_vec != NULL) {
				ans_vec->x = coliPos.x - circlePos.x;
				ans_vec->y = coliPos.y - circlePos.y;
				ans_vec->z = coliPos.z - circlePos.z;
			}
			return CL_MOVING_COLLISION;
		}
		return CL_MOVING_NONE;
	}
	temp_f4_4  = temp_f5 - temp_f7_4;
	temp_f30   = detect_vec->z;
	temp_f29   = detect_vec->x;
	temp_f13_2 = detect_vec->y;
	temp_f28   = (temp_f30 * temp_f1_5) + ((temp_f29 * temp_f3_4) + (temp_f13_2 * temp_f2_4));
	temp_f27   = temp_f28 / temp_f6;
	temp_f12_2 = temp_f29 * temp_f27;
	sp88.x     = temp_f12_2;
	temp_f11_2 = temp_f13_2 * temp_f27;
	sp88.y     = temp_f11_2;
	temp_f10_3 = temp_f30 * temp_f27;
	sp88.z     = temp_f10_3;
	temp_f9_3  = temp_f12_2 - temp_f3_4;
	sp70.x     = temp_f9_3;
	temp_f8_4  = temp_f11_2 - temp_f2_4;
	sp70.y     = temp_f8_4;
	temp_f7_5  = temp_f10_3 - temp_f1_5;
	sp70.z     = temp_f7_5;
	temp_f5_2  = (temp_f7_5 * temp_f7_5) + ((temp_f9_3 * temp_f9_3) + (temp_f8_4 * temp_f8_4));
	if (temp_f28 <= lbl_8042DFEC) {
		temp_f7_6 = (temp_f1_5 * temp_f1_5) + ((temp_f3_4 * temp_f3_4) + (temp_f2_4 * temp_f2_4));
		if (temp_f7_6 <= (lbl_8042DFE8 + temp_f4_4)) {
			if (coli_pos != NULL) {
				coli_pos->z = lbl_8042DFEC;
				coli_pos->y = lbl_8042DFEC;
				coli_pos->x = lbl_8042DFEC;
			}
			if ((f32)__fabs(temp_f7_6 - temp_f4_4) <= lbl_8042DFE8) {
				if (ans_vec != NULL) {
					ans_vec->z = lbl_8042DFEC;
					ans_vec->y = lbl_8042DFEC;
					ans_vec->x = lbl_8042DFEC;
				}
				return CL_MOVING_COLLISION;
			}
			if (ans_vec != NULL) {
				temp_f0_4 = sphere_pos->z;
				temp_f0_5 = sphere_pos->x;
				temp_f0_6 = sphere_pos->y;
				temp_f4_5
				    = (temp_f0_4 * temp_f0_4) + ((temp_f0_5 * temp_f0_5) + (temp_f0_6 * temp_f0_6));
				if (temp_f4_5 < lbl_8042DFE8) {
					temp_f0_7 = sphere_vec->z;
					temp_f0_8 = sphere_vec->x;
					temp_f0_9 = sphere_vec->y;
					temp_f4_6 = (temp_f0_7 * temp_f0_7)
					    + ((temp_f0_8 * temp_f0_8) + (temp_f0_9 * temp_f0_9));
					if (temp_f4_6 < lbl_8042DFE8) {
						if (safe_vec != NULL) {
							temp_f1_6 = fn_801991B4(safe_vec);
							if (temp_f1_6 > lbl_8042DFE8) {
								temp_f1_7  = sphere_rad / temp_f1_6;
								ans_vec->x = safe_vec->x * temp_f1_7;
								ans_vec->y = safe_vec->y * temp_f1_7;
								ans_vec->z = safe_vec->z * temp_f1_7;
							} else {
								ans_vec->z = lbl_8042DFEC;
								ans_vec->y = lbl_8042DFEC;
								ans_vec->x = lbl_8042DFEC;
							}
						} else {
							ans_vec->z = lbl_8042DFEC;
							ans_vec->y = lbl_8042DFEC;
							ans_vec->x = lbl_8042DFEC;
						}
					} else {
						if (temp_f4_6 > lbl_8042DFEC) {
							temp_f0_10 = __frsqrte(temp_f4_6);
							temp_f0_11 = lbl_8042DFF8 * temp_f0_10
							    * (lbl_8042E000 - ((f64)temp_f4_6 * (temp_f0_10 * temp_f0_10)));
							temp_f0_12 = lbl_8042DFF8 * temp_f0_11
							    * (lbl_8042E000 - ((f64)temp_f4_6 * (temp_f0_11 * temp_f0_11)));
							sp20   = (f32)((f64)temp_f4_6
							    * (lbl_8042DFF8 * temp_f0_12
							        * (lbl_8042E000
							            - ((f64)temp_f4_6 * (temp_f0_12 * temp_f0_12)))));
							var_f1 = sp20;
						} else {
							var_f1 = temp_f4_6;
						}
						temp_f1_8  = -sphere_rad / var_f1;
						ans_vec->x = sphere_vec->x * temp_f1_8;
						ans_vec->y = sphere_vec->y * temp_f1_8;
						ans_vec->z = sphere_vec->z * temp_f1_8;
					}
				} else {
					if (temp_f4_5 > lbl_8042DFEC) {
						temp_f0_13 = __frsqrte(temp_f4_5);
						temp_f0_14 = lbl_8042DFF8 * temp_f0_13
						    * (lbl_8042E000 - ((f64)temp_f4_5 * (temp_f0_13 * temp_f0_13)));
						temp_f0_15 = lbl_8042DFF8 * temp_f0_14
						    * (lbl_8042E000 - ((f64)temp_f4_5 * (temp_f0_14 * temp_f0_14)));
						sp1C     = (f32)((f64)temp_f4_5
						    * (lbl_8042DFF8 * temp_f0_15
						        * (lbl_8042E000 - ((f64)temp_f4_5 * (temp_f0_15 * temp_f0_15)))));
						var_f1_2 = sp1C;
					} else {
						var_f1_2 = temp_f4_5;
					}
					temp_f1_9  = (sphere_rad - var_f1_2) / var_f1_2;
					ans_vec->x = sphere_pos->x * temp_f1_9;
					ans_vec->y = sphere_pos->y * temp_f1_9;
					ans_vec->z = sphere_pos->z * temp_f1_9;
				}
			}
			return CL_MOVING_INTERSECTION;
		}
		if (((temp_f1_5 * sphere_vec->z)
		        + ((temp_f3_4 * sphere_vec->x) + (temp_f2_4 * sphere_vec->y)))
		    > lbl_8042DFEC) {
			return CL_MOVING_NONE;
		}
		goto block_120;
	}
	if (temp_f27 >= lbl_8042DFF0) {
		temp_f8_5 = temp_f29 - temp_f3_4;
		sp64.x    = temp_f8_5;
		temp_f7_7 = temp_f13_2 - temp_f2_4;
		sp64.y    = temp_f7_7;
		temp_f6_2 = temp_f30 - temp_f1_5;
		sp64.z    = temp_f6_2;
		temp_f2_5 = (temp_f6_2 * temp_f6_2) + ((temp_f8_5 * temp_f8_5) + (temp_f7_7 * temp_f7_7));
		if (temp_f2_5 <= (lbl_8042DFE8 + temp_f4_4)) {
			if (coli_pos != NULL) {
				coli_pos->x = detect_vec->x;
				coli_pos->y = detect_vec->y;
				coli_pos->z = detect_vec->z;
			}
			if ((f32)__fabs(temp_f2_5 - temp_f4_4) <= lbl_8042DFE8) {
				if (ans_vec != NULL) {
					ans_vec->z = lbl_8042DFEC;
					ans_vec->y = lbl_8042DFEC;
					ans_vec->x = lbl_8042DFEC;
				}
				return CL_MOVING_COLLISION;
			}
			if (ans_vec != NULL) {
				temp_f4_7  = sphere_pos->x - detect_vec->x;
				sp58.x     = temp_f4_7;
				temp_f3_5  = sphere_pos->y - detect_vec->y;
				sp58.y     = temp_f3_5;
				temp_f0_16 = sphere_pos->z - detect_vec->z;
				sp58.z     = temp_f0_16;
				temp_f4_8  = (temp_f0_16 * temp_f0_16)
				    + ((temp_f4_7 * temp_f4_7) + (temp_f3_5 * temp_f3_5));
				if (temp_f4_8 < lbl_8042DFE8) {
					temp_f0_17 = sphere_vec->z;
					temp_f0_18 = sphere_vec->x;
					temp_f0_19 = sphere_vec->y;
					temp_f4_9  = (temp_f0_17 * temp_f0_17)
					    + ((temp_f0_18 * temp_f0_18) + (temp_f0_19 * temp_f0_19));
					if (temp_f4_9 < lbl_8042DFE8) {
						if (safe_vec != NULL) {
							temp_f1_10 = fn_801991B4(safe_vec);
							if (temp_f1_10 > lbl_8042DFE8) {
								temp_f1_11 = sphere_rad / temp_f1_10;
								ans_vec->x = safe_vec->x * temp_f1_11;
								ans_vec->y = safe_vec->y * temp_f1_11;
								ans_vec->z = safe_vec->z * temp_f1_11;
							} else {
								ans_vec->z = lbl_8042DFEC;
								ans_vec->y = lbl_8042DFEC;
								ans_vec->x = lbl_8042DFEC;
							}
						} else {
							ans_vec->z = lbl_8042DFEC;
							ans_vec->y = lbl_8042DFEC;
							ans_vec->x = lbl_8042DFEC;
						}
					} else {
						if (temp_f4_9 > lbl_8042DFEC) {
							temp_f0_20 = __frsqrte(temp_f4_9);
							temp_f0_21 = lbl_8042DFF8 * temp_f0_20
							    * (lbl_8042E000 - ((f64)temp_f4_9 * (temp_f0_20 * temp_f0_20)));
							temp_f0_22 = lbl_8042DFF8 * temp_f0_21
							    * (lbl_8042E000 - ((f64)temp_f4_9 * (temp_f0_21 * temp_f0_21)));
							sp18     = (f32)((f64)temp_f4_9
							    * (lbl_8042DFF8 * temp_f0_22
							        * (lbl_8042E000
							            - ((f64)temp_f4_9 * (temp_f0_22 * temp_f0_22)))));
							var_f1_3 = sp18;
						} else {
							var_f1_3 = temp_f4_9;
						}
						temp_f1_12 = -sphere_rad / var_f1_3;
						ans_vec->x = sphere_vec->x * temp_f1_12;
						ans_vec->y = sphere_vec->y * temp_f1_12;
						ans_vec->z = sphere_vec->z * temp_f1_12;
					}
				} else {
					if (temp_f4_8 > lbl_8042DFEC) {
						temp_f0_23 = __frsqrte(temp_f4_8);
						temp_f0_24 = lbl_8042DFF8 * temp_f0_23
						    * (lbl_8042E000 - ((f64)temp_f4_8 * (temp_f0_23 * temp_f0_23)));
						temp_f0_25 = lbl_8042DFF8 * temp_f0_24
						    * (lbl_8042E000 - ((f64)temp_f4_8 * (temp_f0_24 * temp_f0_24)));
						sp14     = (f32)((f64)temp_f4_8
						    * (lbl_8042DFF8 * temp_f0_25
						        * (lbl_8042E000 - ((f64)temp_f4_8 * (temp_f0_25 * temp_f0_25)))));
						var_f1_4 = sp14;
					} else {
						var_f1_4 = temp_f4_8;
					}
					temp_f1_13 = (sphere_rad - var_f1_4) / var_f1_4;
					ans_vec->x = sp58.x * temp_f1_13;
					ans_vec->y = sp58.y * temp_f1_13;
					ans_vec->z = sp58.z * temp_f1_13;
				}
			}
			return CL_MOVING_INTERSECTION;
		}
		if (((temp_f6_2 * sphere_vec->z)
		        + ((temp_f8_5 * sphere_vec->x) + (temp_f7_7 * sphere_vec->y)))
		    < lbl_8042DFEC) {
			return CL_MOVING_NONE;
		}
		goto block_120;
	}
	if ((lbl_8042DFE8 + temp_f4_4) >= temp_f5_2) {
		if (coli_pos != NULL) {
			coli_pos->x = temp_f12_2;
			coli_pos->y = temp_f11_2;
			coli_pos->z = temp_f10_3;
		}
		if (lbl_8042DFE8 >= (f32)__fabs(temp_f4_4 - temp_f5_2)) {
			if (ans_vec != NULL) {
				ans_vec->z = lbl_8042DFEC;
				ans_vec->y = lbl_8042DFEC;
				ans_vec->x = lbl_8042DFEC;
			}
			return CL_MOVING_COLLISION;
		}
		if (ans_vec != NULL) {
			temp_f4_10 = sphere_pos->x - sp88.x;
			sp4C.x     = temp_f4_10;
			temp_f3_6  = sphere_pos->y - sp88.y;
			sp4C.y     = temp_f3_6;
			temp_f0_26 = sphere_pos->z - sp88.z;
			sp4C.z     = temp_f0_26;
			temp_f4_11
			    = (temp_f0_26 * temp_f0_26) + ((temp_f4_10 * temp_f4_10) + (temp_f3_6 * temp_f3_6));
			if (temp_f4_11 < lbl_8042DFE8) {
				temp_f0_27 = sphere_vec->z;
				temp_f0_28 = sphere_vec->x;
				temp_f0_29 = sphere_vec->y;
				temp_f4_12 = (temp_f0_27 * temp_f0_27)
				    + ((temp_f0_28 * temp_f0_28) + (temp_f0_29 * temp_f0_29));
				if (temp_f4_12 < lbl_8042DFE8) {
					if (safe_vec != NULL) {
						temp_f1_14 = fn_801991B4(safe_vec);
						if (temp_f1_14 > lbl_8042DFE8) {
							temp_f1_15 = sphere_rad / temp_f1_14;
							ans_vec->x = safe_vec->x * temp_f1_15;
							ans_vec->y = safe_vec->y * temp_f1_15;
							ans_vec->z = safe_vec->z * temp_f1_15;
						} else {
							ans_vec->z = lbl_8042DFEC;
							ans_vec->y = lbl_8042DFEC;
							ans_vec->x = lbl_8042DFEC;
						}
					} else {
						ans_vec->z = lbl_8042DFEC;
						ans_vec->y = lbl_8042DFEC;
						ans_vec->x = lbl_8042DFEC;
					}
				} else {
					if (temp_f4_12 > lbl_8042DFEC) {
						temp_f0_30 = __frsqrte(temp_f4_12);
						temp_f0_31 = lbl_8042DFF8 * temp_f0_30
						    * (lbl_8042E000 - ((f64)temp_f4_12 * (temp_f0_30 * temp_f0_30)));
						temp_f0_32 = lbl_8042DFF8 * temp_f0_31
						    * (lbl_8042E000 - ((f64)temp_f4_12 * (temp_f0_31 * temp_f0_31)));
						sp10     = (f32)((f64)temp_f4_12
						    * (lbl_8042DFF8 * temp_f0_32
						        * (lbl_8042E000 - ((f64)temp_f4_12 * (temp_f0_32 * temp_f0_32)))));
						var_f1_5 = sp10;
					} else {
						var_f1_5 = temp_f4_12;
					}
					temp_f1_16 = -sphere_rad / var_f1_5;
					ans_vec->x = sphere_vec->x * temp_f1_16;
					ans_vec->y = sphere_vec->y * temp_f1_16;
					ans_vec->z = sphere_vec->z * temp_f1_16;
				}
			} else {
				if (temp_f4_11 > lbl_8042DFEC) {
					temp_f0_33 = __frsqrte(temp_f4_11);
					temp_f0_34 = lbl_8042DFF8 * temp_f0_33
					    * (lbl_8042E000 - ((f64)temp_f4_11 * (temp_f0_33 * temp_f0_33)));
					temp_f0_35 = lbl_8042DFF8 * temp_f0_34
					    * (lbl_8042E000 - ((f64)temp_f4_11 * (temp_f0_34 * temp_f0_34)));
					spC      = (f32)((f64)temp_f4_11
					    * (lbl_8042DFF8 * temp_f0_35
					        * (lbl_8042E000 - ((f64)temp_f4_11 * (temp_f0_35 * temp_f0_35)))));
					var_f1_6 = spC;
				} else {
					var_f1_6 = temp_f4_11;
				}
				temp_f1_17 = (sphere_rad - var_f1_6) / var_f1_6;
				ans_vec->x = sp4C.x * temp_f1_17;
				ans_vec->y = sp4C.y * temp_f1_17;
				ans_vec->z = sp4C.z * temp_f1_17;
			}
		}
		return CL_MOVING_INTERSECTION;
	}
	if (((temp_f7_5 * sphere_vec->z) + ((temp_f9_3 * sphere_vec->x) + (temp_f8_4 * sphere_vec->y)))
	    < lbl_8042DFEC) {
		return CL_MOVING_NONE;
	}
block_120:
	if (temp_f4_4 >= temp_f5_2) {
		ignoreDetectCylinderFlag = 1;
	}
	var_f4_2 = temp_f4_4 / temp_f5_2;
	if (var_f4_2 > lbl_8042DFEC) {
		temp_f0_36 = __frsqrte(var_f4_2);
		temp_f0_37 = lbl_8042DFF8 * temp_f0_36
		    * (lbl_8042E000 - ((f64)var_f4_2 * (temp_f0_36 * temp_f0_36)));
		temp_f0_38 = lbl_8042DFF8 * temp_f0_37
		    * (lbl_8042E000 - ((f64)var_f4_2 * (temp_f0_37 * temp_f0_37)));
		sp8      = (f32)((f64)var_f4_2
		    * (lbl_8042DFF8 * temp_f0_38
		        * (lbl_8042E000 - ((f64)var_f4_2 * (temp_f0_38 * temp_f0_38)))));
		var_f4_2 = sp8;
	}
	temp_f3_7  = sp70.x * var_f4_2;
	sp70.x     = temp_f3_7;
	temp_f2_6  = sp70.y * var_f4_2;
	sp70.y     = temp_f2_6;
	temp_f1_18 = sp70.z * var_f4_2;
	sp70.z     = temp_f1_18;
	sp7C.x     = circlePos.x + temp_f3_7;
	sp7C.y     = circlePos.y + temp_f2_6;
	sp7C.z     = circlePos.z + temp_f1_18;
	if ((ignoreDetectCylinderFlag == 0)
	    && (clIsCrossLS2VonPlane(&sp7C, sphere_vec, detect_vec, &coliPos) != 0)) {
		if (coli_pos != NULL) {
			coli_pos->x = coliPos.x;
			coli_pos->y = coliPos.y;
			coli_pos->z = coliPos.z;
		}
		if (ans_vec != NULL) {
			ans_vec->x = coliPos.x - sp7C.x;
			ans_vec->y = coliPos.y - sp7C.y;
			ans_vec->z = coliPos.z - sp7C.z;
		}
		return CL_MOVING_COLLISION;
	}
	var_r31 = clDetectMS2P_(sphere_pos, sphere_rad, sphere_vec, safe_vec, &sp34);
	sp40.x  = sphere_pos->x - detect_vec->x;
	sp40.y  = sphere_pos->y - detect_vec->y;
	sp40.z  = sphere_pos->z - detect_vec->z;
	var_r3  = clDetectMS2P_(&sp40, sphere_rad, sphere_vec, safe_vec, &sp28);
	if ((var_r31 != CL_MOVING_NONE) && (var_r3 != CL_MOVING_NONE)) {
		if ((var_r31 == CL_MOVING_INTERSECTION) && (var_r3 != CL_MOVING_INTERSECTION)) {
			var_r3 = CL_MOVING_NONE;
		} else if ((var_r31 != CL_MOVING_INTERSECTION) && (var_r3 == CL_MOVING_INTERSECTION)) {
			var_r31 = CL_MOVING_NONE;
		} else {
			temp_f0_39 = sp34.x;
			temp_f0_40 = sp28.x;
			if (((sp34.z * sp34.z) + ((temp_f0_39 * temp_f0_39) + (sp34.y * sp34.y)))
			    < ((sp28.z * sp28.z) + ((temp_f0_40 * temp_f0_40) + (sp28.y * sp28.y)))) {
				var_r3 = CL_MOVING_NONE;
			} else {
				var_r31 = CL_MOVING_NONE;
			}
		}
	}
	if (var_r31 != CL_MOVING_NONE) {
		if (ans_vec != NULL) {
			ans_vec->x = sp34.x;
			ans_vec->y = sp34.y;
			ans_vec->z = sp34.z;
		}
		if (coli_pos != NULL) {
			coli_pos->z = lbl_8042DFEC;
			coli_pos->y = lbl_8042DFEC;
			coli_pos->x = lbl_8042DFEC;
		}
		return var_r31;
	}
	if (var_r3 != CL_MOVING_NONE) {
		if (ans_vec != NULL) {
			ans_vec->x = sp28.x;
			ans_vec->y = sp28.y;
			ans_vec->z = sp28.z;
		}
		if (coli_pos != NULL) {
			coli_pos->x = detect_vec->x;
			coli_pos->y = detect_vec->y;
			coli_pos->z = detect_vec->z;
			return var_r3;
		}

		return var_r3;
	}
	var_r3 = CL_MOVING_NONE;
	return var_r3;
}

// The GameCube implementation is deliberately a no-collision return.
// Its five calls survive in clDetectMS2LS_; do not import the other platform body.
enum ENUM_CL_MOVING clDetectMS2P_(const RwV3d* sphere_pos, f32 sphere_rad, const RwV3d* sphere_vec,
    const RwV3d* safe_vec, RwV3d* ans_vec)
{
	return CL_MOVING_NONE;
}

extern const __declspec(section ".sdata2") f32 lbl_8042DFE8 = 0.000123f;
extern const __declspec(section ".sdata2") f32 lbl_8042DFEC = 0.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042DFF0 = 1.0f;
extern const __declspec(section ".sdata2") f32 lbl_8042DFF4 = 0.0001f;
extern const __declspec(section ".sdata2") f64 lbl_8042DFF8 = 0.5;
extern const __declspec(section ".sdata2") f64 lbl_8042E000 = 3.0;
