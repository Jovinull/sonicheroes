#include "game/scanpath.h"

// Complete C++ scanpath unit; see docs/scanpath-unit-evidence.md.
// Fifteen bodies match directly. CalcPNNPntParam retains four register fields
// across two instructions, normalized by tools/fix_scanpath_registers.py.
// Metadata-local scopes, assignment orders, casts and compiler options were
// compared; O3 preserves the smallest remainder. No source spelling yet fixes
// the load/copy allocation without regressing another body. Remove the tool
// once source reproduces that transfer directly.

struct MemoryAllocator {
	u8 pad[0x134];
	void* (*Alloc)(u32);
	void (*Free)(void*);
};
extern "C" {
extern MemoryAllocator* lbl_8042C9A4;
f32 DistanceP2P__FPC5RwV3dPC5RwV3d(RwV3d*, RwV3d*);
f32 fn_801991B4(RwV3d*);
f32 DistanceP2SegL__FP5RwV3dP5RwV3dP5RwV3dP5RwV3d(RwV3d*, RwV3d*, RwV3d*, RwV3d*);
s32 SubAngle__Fii(s32, s32);
f64 __fabs(f64);
f64 asin(f64);
f64 atan2(f64, f64);
f32 GetFloatMod__Fff(f32, f32);
f32 fn_800D7AE4(s32);
f32 fn_800D7B00(s32);
RwV3d* fn_801990E0(RwV3d*, RwV3d*);
}

static void SCPathSubCheckTheNearestPoint(PATHPOINTCHECK*);
static void CalcPNNPntParam(PATHTAG*, s32, void*);

PATHTAG** MargePathTag(PATHTAG** first, PATHTAG** second)
{
	s32 count   = 0;
	PATHTAG** p = first;
	while (*p) {
		++p;
		++count;
	}
	p = second;
	while (*p) {
		++p;
		++count;
	}
	PATHTAG** result = (PATHTAG**)lbl_8042C9A4->Alloc((count + 1) * sizeof(PATHTAG*));
	PATHTAG** dest   = result;
	PATHTAG* tag;
	while ((tag = *first) != NULL) {
		*dest++ = tag;
		++first;
	}
	while ((tag = *second) != NULL) {
		*dest++ = tag;
		++second;
	}
	*dest = NULL;
	return result;
}

f32 SCPathPntNearToOnpos(PATHTAG* tag, RwV3d* pos, RwV3d* nearest, f32* onpos, f32 range)
{
	s32 remaining;
	s32 end;
	PATHPOINTCHECK check;
	check.S_length  = 0.0f;
	check.pt        = pos;
	check.onpnt3    = nearest;
	check.min_onpos = onpos;
	if (onpos)
		check.onpos_Refer = *onpos;
	check.range_Search = range;
	if ((tag->pathtype & 0x8000) == 0x8000)
		end = 0;
	else
		end = 1;

	switch (tag->pathtype & 0x3FFF) {
		case 1: {
			PATHTBL_P* p = (PATHTBL_P*)tag->pathtbl;
			for (remaining = tag->points; remaining > end; --remaining) {
				check.length = p->length;
				check.p0     = &p->pos;
				++p;
				if (remaining != 1)
					check.p1 = &p->pos;
				else
					check.p1 = &((PATHTBL_P*)tag->pathtbl)->pos;
				SCPathSubCheckTheNearestPoint(&check);
			}
			break;
		}
		case 2: {
			PATHTBL_R* p = (PATHTBL_R*)tag->pathtbl;
			for (remaining = tag->points; remaining > end; --remaining) {
				check.length = p->length;
				check.p0     = &p->pos;
				++p;
				// The retail closed-rail fallback uses offset 8, like a point record.
				if (remaining != 1)
					check.p1 = &p->pos;
				else
					check.p1 = &((PATHTBL_P*)tag->pathtbl)->pos;
				SCPathSubCheckTheNearestPoint(&check);
			}
			break;
		}
		default:
			return 0.0f;
	}
	return check.min_dist;
}

static void SCPathSubCheckTheNearestPoint(PATHPOINTCHECK* arg0)
{
	RwV3d tmppos;
	RwV3d tmppos2;
	RwV3d* temp_r3;
	RwV3d* temp_r3_3;
	RwV3d* temp_r3_4;
	RwV3d* temp_r3_5;
	f32 temp_f1;
	f32 temp_f31;
	f64 candidateDistance;
	f32 temp_f3;

	if (0.0f == arg0->S_length) {
		arg0->min_dist
		    = DistanceP2SegL__FP5RwV3dP5RwV3dP5RwV3dP5RwV3d(arg0->pt, arg0->p0, arg0->p1, &tmppos);
		temp_r3 = arg0->onpnt3;
		if (temp_r3 != NULL) {
			temp_r3->x = tmppos.x;
			temp_r3->y = tmppos.y;
			temp_r3->z = tmppos.z;
		}
		if ((f32*)arg0->min_onpos != NULL) {
			*arg0->min_onpos = arg0->S_length + DistanceP2P__FPC5RwV3dPC5RwV3d(arg0->p0, &tmppos);
		}
	} else {
		temp_f31
		    = DistanceP2SegL__FP5RwV3dP5RwV3dP5RwV3dP5RwV3d(arg0->pt, arg0->p0, arg0->p1, &tmppos2);
		if (((f32*)arg0->min_onpos != NULL) && (arg0->range_Search > 0.0f)) {
			if (arg0->range_Search >= DistanceP2P__FPC5RwV3dPC5RwV3d(arg0->pt, &tmppos2)) {
				temp_f3 = arg0->S_length + DistanceP2P__FPC5RwV3dPC5RwV3d(arg0->p0, &tmppos2);
				temp_f1 = arg0->onpos_Refer;
				candidateDistance = __fabs(temp_f3 - temp_f1);
				if ((f32)__fabs(*arg0->min_onpos - temp_f1) > (f32)candidateDistance) {
					*arg0->min_onpos = temp_f3;
					arg0->min_dist   = temp_f31;
					temp_r3_3        = arg0->onpnt3;
					if (temp_r3_3 != NULL) {
						temp_r3_3->x = tmppos2.x;
						temp_r3_3->y = tmppos2.y;
						temp_r3_3->z = tmppos2.z;
					}
				}
			} else if (temp_f31 < arg0->min_dist) {
				arg0->min_dist = temp_f31;
				if ((f32*)arg0->min_onpos != NULL) {
					*arg0->min_onpos
					    = arg0->S_length + DistanceP2P__FPC5RwV3dPC5RwV3d(arg0->p0, &tmppos2);
				}
				temp_r3_4 = arg0->onpnt3;
				if (temp_r3_4 != NULL) {
					temp_r3_4->x = tmppos2.x;
					temp_r3_4->y = tmppos2.y;
					temp_r3_4->z = tmppos2.z;
				}
			}
		} else if (temp_f31 < arg0->min_dist) {
			arg0->min_dist = temp_f31;
			if ((f32*)arg0->min_onpos != NULL) {
				*arg0->min_onpos
				    = arg0->S_length + DistanceP2P__FPC5RwV3dPC5RwV3d(arg0->p0, &tmppos2);
			}
			temp_r3_5 = arg0->onpnt3;
			if (temp_r3_5 != NULL) {
				temp_r3_5->x = tmppos2.x;
				temp_r3_5->y = tmppos2.y;
				temp_r3_5->z = tmppos2.z;
			}
		}
	}
	arg0->S_length += arg0->length;
}

s32 SCPathOnposToPntnmb(PATHTAG* tag, f32 onpos, u32* point)
{
	s32 points = tag->points;
	s32 count;
	f32 sum;
	switch (tag->pathtype & 0x3FFF) {
		case 1: {
			PATHTBL_P* p = (PATHTBL_P*)tag->pathtbl;
			count        = 0;
			sum          = 0.0f;
			for (s32 remaining = points; remaining > 0; --remaining) {
				f32 part = p->length;
				if (onpos <= sum + part)
					break;
				++p;
				++count;
				sum += part;
			}
			break;
		}
		case 2: {
			PATHTBL_R* p = (PATHTBL_R*)tag->pathtbl;
			count        = 0;
			sum          = 0.0f;
			for (s32 remaining = points; remaining > 0; --remaining) {
				f32 part = p->length;
				if (onpos <= sum + part)
					break;
				++p;
				++count;
				sum += part;
			}
			break;
		}
		default:
			return 0;
	}
	*point = count;
	return (s32)count < points;
}

s32 GetStatusOnPath(PATHTAG* arg0, PATHINFO* arg1)
{
	PATHTBL_P ptP[2];
	PATHTBL_R ptR[2];
	RwV3d tonextP;
	RwV3d tonextR;
	RwV3d* temp_r3;
	f32 temp_f0_3;
	f32 temp_f1;
	f32 temp_f1_2;
	f32 temp_f1_3;
	f32 temp_f1_4;
	f32 temp_f31;
	s16 temp_r0_2;
	s16 temp_r0_3;
	s32 temp_r0;
	s32 temp_r4;
	s32 var_r4;
	s32 var_r4_2;
	PATHTBL_P* var_r3;
	PATHTBL_R* var_r3_2;

	temp_f1 = arg1->onpathpos;
	temp_r4 = arg0->pathtype & 0x8000;
	switch (temp_r4) {
		case 0x0:
			if ((temp_f1 < 0.0f) || (temp_f1 > arg0->totallen)) {
				return 0;
			}
			break;
		case 0x8000:
			arg1->onpathpos = GetFloatMod__Fff(temp_f1, arg0->totallen);
			break;
	}
	temp_r0 = arg0->pathtype & 0x3FFF;
	switch (temp_r0) {
		case 1: {
			f32 sumP, partP, nowP;
			var_r3    = (PATHTBL_P*)arg0->pathtbl;
			nowP      = arg1->onpathpos;
			var_r4    = 0;
			sumP      = 0.0f;
			temp_r0_2 = arg0->points;
			temp_f1_2 = sumP;
			for (; var_r4 < temp_r0_2;) {
				partP = var_r3->length;
				if (temp_f1_2 == partP) {
					partP = 1.0f;
					sumP -= partP;
				}
				if (nowP <= sumP + partP)
					break;
				++var_r3;
				++var_r4;
				sumP += partP;
			}
			if (temp_r0_2 <= var_r4) {
				return 0;
			}
			CalcPNNPntParam(arg0, var_r4, &ptP[0]);
			temp_f31      = (nowP - sumP) / partP;
			arg1->slangx  = (s32)ptP[0].slangx;
			arg1->slangz  = (s32)ptP[0].slangz;
			arg1->slangax = ptP[0].slangx
			    + (s32)(temp_f31 * (f32)SubAngle__Fii((s32)ptP[0].slangx, (s32)ptP[1].slangx));
			arg1->slangaz = ptP[0].slangz
			    + (s32)(temp_f31 * (f32)SubAngle__Fii((s32)ptP[0].slangz, (s32)ptP[1].slangz));
			tonextP.x       = ptP[1].pos.x - ptP[0].pos.x;
			tonextP.y       = ptP[1].pos.y - ptP[0].pos.y;
			tonextP.z       = ptP[1].pos.z - ptP[0].pos.z;
			arg1->pos.x     = ptP[0].pos.x + tonextP.x * temp_f31;
			arg1->pos.y     = ptP[0].pos.y + tonextP.y * temp_f31;
			arg1->pos.z     = ptP[0].pos.z + tonextP.z * temp_f31;
			arg1->normal.x  = -fn_800D7B00(arg1->slangz) * fn_800D7AE4(arg1->slangx);
			arg1->normal.y  = fn_800D7AE4(arg1->slangz) * fn_800D7AE4(arg1->slangx);
			arg1->normal.z  = fn_800D7B00(arg1->slangx);
			arg1->normala.x = -fn_800D7B00(arg1->slangaz) * fn_800D7AE4(arg1->slangax);
			arg1->normala.y = fn_800D7AE4(arg1->slangaz) * fn_800D7AE4(arg1->slangax);
			arg1->normala.z = fn_800D7B00(arg1->slangax);
			fn_801990E0(&tonextP, &tonextP);
			arg1->front.x = tonextP.x;
			arg1->front.y = tonextP.y;
			arg1->front.z = tonextP.z;
			break;
		}
		case 2: {
			f32 sumR, partR, nowR;
			var_r3_2  = (PATHTBL_R*)arg0->pathtbl;
			nowR      = arg1->onpathpos;
			var_r4_2  = 0;
			sumR      = 0.0f;
			temp_r0_3 = arg0->points;
			temp_f1_3 = sumR;
			for (; var_r4_2 < temp_r0_3;) {
				partR = var_r3_2->length;
				if (temp_f1_3 == partR) {
					partR = 1.0f;
				}
				if (nowR <= sumR + partR)
					break;
				++var_r3_2;
				++var_r4_2;
				sumR += partR;
			}
			CalcPNNPntParam(arg0, var_r4_2, &ptR[0]);
			temp_f0_3       = (nowR - sumR) / partR;
			temp_f1_4       = 1.0f - temp_f0_3;
			tonextR.x       = ptR[1].pos.x - ptR[0].pos.x;
			tonextR.y       = ptR[1].pos.y - ptR[0].pos.y;
			tonextR.z       = ptR[1].pos.z - ptR[0].pos.z;
			arg1->pos.x     = ptR[0].pos.x + tonextR.x * temp_f0_3;
			arg1->pos.y     = ptR[0].pos.y + tonextR.y * temp_f0_3;
			arg1->pos.z     = ptR[0].pos.z + tonextR.z * temp_f0_3;
			arg1->normal.x  = ptR[0].n.x;
			arg1->normal.y  = ptR[0].n.y;
			arg1->normal.z  = ptR[0].n.z;
			arg1->normala.x = (ptR[0].n.x * temp_f0_3) + (ptR[1].n.x * temp_f1_4);
			arg1->normala.y = (ptR[0].n.y * temp_f0_3) + (ptR[1].n.y * temp_f1_4);
			arg1->normala.z = (ptR[0].n.z * temp_f0_3) + (ptR[1].n.z * temp_f1_4);
			temp_r3         = &arg1->normala;
			fn_801990E0(temp_r3, temp_r3);
			fn_801990E0(&tonextR, &tonextR);
			arg1->front.x = tonextR.x;
			arg1->front.y = tonextR.y;
			arg1->front.z = tonextR.z;
			arg1->slangx  = (s32)(10430.380859375f * (f32)asin((f64)arg1->normal.z));
			arg1->slangz
			    = -(s32)(10430.380859375f * (f32)atan2((f64)arg1->normal.x, (f64)arg1->normal.y));
			arg1->slangax = (s32)(10430.380859375f * (f32)asin((f64)arg1->normala.z));
			arg1->slangaz
			    = -(s32)(10430.380859375f * (f32)atan2((f64)arg1->normala.x, (f64)arg1->normala.y));
			break;
		}
		case 0:
		default:
			return 0;
	}
	return 1;
}

static void CalcPNNPntParam(PATHTAG* tag, s32 point, void* out)
{
	s32 prev = point - 1;
	s32 next = point + 1;
	switch (tag->pathtype & 0x8000) {
		case 0:
			if (prev < 0)
				prev = 0;
			else if (next >= tag->points)
				next = tag->points - 1;
			break;
		case 0x8000:
			if (prev < 0)
				prev = tag->points - 1;
			else if (next >= tag->points)
				next = 0;
			break;
	}

	switch (tag->pathtype & 0x3FFF) {
		case 0: {
			PATHTBL_C* table     = (PATHTBL_C*)tag->pathtbl;
			PATHTBL_C* current   = &table[point];
			PATHTBL_C* following = &table[next];
			PATHTBL_C* dest      = (PATHTBL_C*)out;
			dest[0].pos.x        = current->pos.x;
			dest[0].pos.y        = current->pos.y;
			dest[0].pos.z        = current->pos.z;
			dest[1].pos.x        = following->pos.x;
			dest[1].pos.y        = following->pos.y;
			dest[1].pos.z        = following->pos.z;
			break;
		}
		case 1: {
			PATHTBL_P *current, *previous, *following, *dest;
			s16 x, z;
			PATHTBL_P* table = (PATHTBL_P*)tag->pathtbl;
			previous         = &table[prev];
			current          = &table[point];
			following        = &table[next];
			dest             = (PATHTBL_P*)out;
			x                = current->slangx;
			z                = current->slangz;
			dest[0].slangx   = (s16)(previous->slangx + (SubAngle__Fii(previous->slangx, x) >> 1));
			dest[0].slangz   = (s16)(previous->slangz + (SubAngle__Fii(previous->slangz, z) >> 1));
			dest[1].slangx   = (s16)(x + (SubAngle__Fii(x, following->slangx) >> 1));
			dest[1].slangz   = (s16)(z + (SubAngle__Fii(z, following->slangz) >> 1));
			dest[0].pos.x    = current->pos.x;
			dest[0].pos.y    = current->pos.y;
			dest[0].pos.z    = current->pos.z;
			dest[1].pos.x    = following->pos.x;
			dest[1].pos.y    = following->pos.y;
			dest[1].pos.z    = following->pos.z;
			dest[0].length   = current->length;
			dest[1].length   = following->length;
			break;
		}
		case 2: {
			PATHTBL_R* table     = (PATHTBL_R*)tag->pathtbl;
			PATHTBL_R* current   = &table[point];
			PATHTBL_R* following = &table[next];
			PATHTBL_R* dest      = (PATHTBL_R*)out;
			dest[0].pos.x        = current->pos.x;
			dest[0].pos.y        = current->pos.y;
			dest[0].pos.z        = current->pos.z;
			dest[1].pos.x        = following->pos.x;
			dest[1].pos.y        = following->pos.y;
			dest[1].pos.z        = following->pos.z;
			dest[0].n.x          = current->n.x;
			dest[0].n.y          = current->n.y;
			dest[0].n.z          = current->n.z;
			dest[1].n.x          = following->n.x;
			dest[1].n.y          = following->n.y;
			dest[1].n.z          = following->n.z;
			dest[0].length       = current->length;
			dest[1].length       = following->length;
			break;
		}
	}
}

void GetPointDataOnPath(PATHTAG* tag, s32 point, RwV3d* out)
{
	switch (tag->pathtype & 0x3FFF) {
		case 0: {
			PATHTBL_C* p = &((PATHTBL_C*)tag->pathtbl)[point];
			out->x       = p->pos.x;
			out->y       = p->pos.y;
			out->z       = p->pos.z;
			break;
		}
		case 1: {
			PATHTBL_P* p = &((PATHTBL_P*)tag->pathtbl)[point];
			out->x       = p->pos.x;
			out->y       = p->pos.y;
			out->z       = p->pos.z;
			break;
		}
		case 2: {
			PATHTBL_R* p = &((PATHTBL_R*)tag->pathtbl)[point];
			out->x       = p->pos.x;
			out->y       = p->pos.y;
			out->z       = p->pos.z;
			break;
		}
	}
}

extern "C" {
TObjPathManage* lbl_8042C380;
}

PATHTAG* TObjPathManage::scanpathGetTheConnectedPath(PATHTAG* excluded, RwV3d* pos, f32* onpos)
{
	RwV3d nearest;
	f32 candidateOnpos;
	f32 bestDistance;
	f32 bestOnpos;
	if (!lbl_8042C380)
		return NULL;
	CLASS_PATH* path = lbl_8042C380->pPath;
	PATHTAG* result  = NULL;
	bestDistance     = 5;
	while (path) {
		f32 distance = 5.0f;
		if (excluded != path->tagptr && !(pos->x > path->maxpos.x + distance)
		    && !(pos->x < path->minpos.x - distance) && !(pos->z > path->maxpos.z + distance)
		    && !(pos->z < path->minpos.z - distance) && !(pos->y > path->maxpos.y + distance)
		    && !(pos->y < path->minpos.y - distance)) {
			candidateOnpos = 0.0f;
			distance = SCPathPntNearToOnpos(path->tagptr, pos, &nearest, &candidateOnpos, 0.0f);
			if (!(bestDistance < distance)) {
				result       = path->tagptr;
				bestDistance = distance;
				bestOnpos    = candidateOnpos;
			}
		}
		path = path->next;
	}
	if (!result)
		return NULL;
	if (onpos)
		*onpos = bestOnpos;
	return result;
}

PATHTAG* scanpathGetTheNearestPath(RwV3d* pos, RwV3d* direction, f32 range)
{
	f32 onpos;
	RwV3d nearest, difference;
	if (!lbl_8042C380)
		return NULL;
	CLASS_PATH* path = lbl_8042C380->pPath;
	PATHTAG* result  = NULL;
	f32 bestDistance = range;
	while (path) {
		if (!(pos->x > path->maxpos.x + range) && !(pos->x < path->minpos.x - range)
		    && !(pos->z > path->maxpos.z + range) && !(pos->z < path->minpos.z - range)
		    && !(pos->y > path->maxpos.y + range) && !(pos->y < path->minpos.y - range)) {
			onpos        = 0.0f;
			f32 distance = SCPathPntNearToOnpos(path->tagptr, pos, &nearest, &onpos, 0.0f);
			if (!(distance >= range)) {
				difference.x = nearest.x - pos->x;
				difference.y = nearest.y - pos->y;
				difference.z = nearest.z - pos->z;
				if (!(fn_801991B4(&difference) < 3.0f)
				    && !((difference.z * direction->z
				             + (difference.x * direction->x + difference.y * direction->y))
				        < 0.0f)
				    && !(bestDistance < distance)) {
					result       = path->tagptr;
					bestDistance = distance;
				}
			}
		}
		path = path->next;
	}
	return !result ? NULL : result;
}

void TObjPathManage::ReleasePath(CLASS_PATH* path)
{
	if (!path)
		return;
	if (path->useCopyData) {
		lbl_8042C9A4->Free(path->tagptr->pathtbl);
		lbl_8042C9A4->Free(path->tagptr);
	}
	if (!path->next) {
		path->last->next = NULL;
		pPath->last      = path->last;
	} else if (pPath == path) {
		if (!pPath->next)
			pPath = NULL;
		else {
			pPath->next->last = pPath->last;
			pPath             = path->next;
		}
	} else {
		path->next->last = path->last;
		path->last->next = path->next;
	}
	delete path;
}

struct RwMatrix {
	RwV3d right;
	u32 flags;
	RwV3d up;
	u32 pad1;
	RwV3d at;
	u32 pad2;
	RwV3d pos;
	u32 pad3;
};
extern "C" {
RwMatrix* fn_80195A74(RwMatrix*, const RwV3d*, f32, s32);
RwMatrix* fn_80195E44(RwMatrix*, const RwV3d*, s32);
RwMatrix* fn_80196050(RwMatrix*, const RwV3d*, s32);
void GetAngleXZ__FfffPiPi(s32*, s32*, f32, f32, f32);
extern RwV3d AxisX, AxisY, AxisZ, lbl_80239F60;
}

inline void TObjPathManage::reEntryLen(f32* length, RwV3d* pos1, RwV3d* pos2)
{
	RwV3d scl;
	scl.x   = pos1->x - pos2->x;
	scl.y   = pos1->y - pos2->y;
	scl.z   = pos1->z - pos2->z;
	*length = fn_801991B4(&scl);
}

inline void TObjPathManage::reEntryVec(RwV3d* normal, sAngle* ang, PATH_ROT_STATUS rot)
{
	RwMatrix mat;
	mat.right.x = mat.up.y = mat.at.z = 1.0f;
	mat.right.y = mat.right.z = mat.up.x = 0.0f;
	mat.up.z = mat.at.x = mat.at.y = 0.0f;
	mat.pos.x = mat.pos.y = mat.pos.z = 0.0f;
	mat.flags |= 0x20003;
	fn_80196050(&mat, normal, 0);
	if (ang) {
		switch (rot) {
			case PATH_ROT_YXZ:
				fn_80195A74(&mat, &AxisY, 0.0054931640625f * ang->y, 2);
				fn_80195A74(&mat, &AxisX, 0.0054931640625f * ang->x, 2);
				fn_80195A74(&mat, &AxisZ, 0.0054931640625f * ang->z, 2);
				break;
			case PATH_ROT_ZXY:
				fn_80195A74(&mat, &AxisZ, 0.0054931640625f * ang->z, 2);
				fn_80195A74(&mat, &AxisX, 0.0054931640625f * ang->x, 2);
				fn_80195A74(&mat, &AxisY, 0.0054931640625f * ang->y, 2);
				break;
		}
	}
	normal->x = mat.pos.x;
	normal->y = mat.pos.y;
	normal->z = mat.pos.z;
}

inline void TObjPathManage::reEntryAng(s16* angX, s16* angZ, sAngle* ang, PATH_ROT_STATUS rot)
{
	RwV3d normal = lbl_80239F60;
	RwMatrix mat;
	s32 ax, az;
	mat.right.x = mat.up.y = mat.at.z = 1.0f;
	mat.right.y = mat.right.z = mat.up.x = 0.0f;
	mat.up.z = mat.at.x = mat.at.y = 0.0f;
	mat.pos.x = mat.pos.y = mat.pos.z = 0.0f;
	mat.flags |= 0x20003;
	fn_80196050(&mat, &normal, 0);
	fn_80195A74(&mat, &AxisX, *angX, 2);
	fn_80195A74(&mat, &AxisZ, *angZ, 2);
	if (ang) {
		switch (rot) {
			case PATH_ROT_YXZ:
				fn_80195A74(&mat, &AxisY, 0.0054931640625f * ang->y, 2);
				fn_80195A74(&mat, &AxisX, 0.0054931640625f * ang->x, 2);
				fn_80195A74(&mat, &AxisZ, 0.0054931640625f * ang->z, 2);
				break;
			case PATH_ROT_ZXY:
				fn_80195A74(&mat, &AxisZ, 0.0054931640625f * ang->z, 2);
				fn_80195A74(&mat, &AxisX, 0.0054931640625f * ang->x, 2);
				fn_80195A74(&mat, &AxisY, 0.0054931640625f * ang->y, 2);
				break;
		}
	}
	normal.x = mat.pos.x;
	normal.y = mat.pos.y;
	normal.z = mat.pos.z;
	GetAngleXZ__FfffPiPi(&ax, &az, normal.x, normal.y, normal.z);
	*angX = ax;
	*angZ = az;
}

inline void TObjPathManage::reEntryPos(
    RwV3d* pos, RwV3d* offset, sAngle* ang, RwV3d* scl, PATH_ROT_STATUS rot)
{
	RwMatrix mat;
	mat.right.x = mat.up.y = mat.at.z = 1.0f;
	mat.right.y = mat.right.z = mat.up.x = 0.0f;
	mat.up.z = mat.at.x = mat.at.y = 0.0f;
	mat.pos.x = mat.pos.y = mat.pos.z = 0.0f;
	mat.flags |= 0x20003;
	fn_80196050(&mat, pos, 0);
	if (scl)
		fn_80195E44(&mat, scl, 2);
	if (ang) {
		switch (rot) {
			case PATH_ROT_YXZ:
				fn_80195A74(&mat, &AxisY, 0.0054931640625f * ang->y, 2);
				fn_80195A74(&mat, &AxisX, 0.0054931640625f * ang->x, 2);
				fn_80195A74(&mat, &AxisZ, 0.0054931640625f * ang->z, 2);
				break;
			case PATH_ROT_ZXY:
				fn_80195A74(&mat, &AxisZ, 0.0054931640625f * ang->z, 2);
				fn_80195A74(&mat, &AxisX, 0.0054931640625f * ang->x, 2);
				fn_80195A74(&mat, &AxisY, 0.0054931640625f * ang->y, 2);
				break;
		}
	}
	if (offset)
		fn_80196050(&mat, offset, 2);
	pos->x = mat.pos.x;
	pos->y = mat.pos.y;
	pos->z = mat.pos.z;
}

CLASS_PATH* TObjPathManage::EntryPath(
    PATHTAG* tag, RwV3d* pos, sAngle* ang, RwV3d* scl, PATH_ROT_STATUS rot)
{
	CLASS_PATH* path = NULL;
	if (tag) {
		if (!pos && !ang && !scl) {
			path = new CLASS_PATH(tag->pathtask);
			if (path) {
				path->tagptr      = tag;
				path->useCopyData = 0;
				goto link_path;
			}
			return NULL;
		} else {
			PATHTAG* copy = (PATHTAG*)lbl_8042C9A4->Alloc(sizeof(PATHTAG));
			if (!copy)
				return NULL;
			*copy = *tag;
			void* table;
			switch (copy->pathtype) {
				case 0:
					table = lbl_8042C9A4->Alloc(copy->points * sizeof(PATHTBL_C));
					break;
				case 1:
					table = lbl_8042C9A4->Alloc(copy->points * sizeof(PATHTBL_P));
					break;
				case 2:
					table = lbl_8042C9A4->Alloc(copy->points * sizeof(PATHTBL_R));
					break;
			}
			if (!table) {
				lbl_8042C9A4->Free(copy);
				return NULL;
			}
			copy->pathtbl  = table;
			PATHTBL_C* pc  = (PATHTBL_C*)table;
			PATHTBL_P* pp  = (PATHTBL_P*)table;
			PATHTBL_R* pr  = (PATHTBL_R*)table;
			PATHTBL_C* pco = (PATHTBL_C*)tag->pathtbl;
			PATHTBL_P* ppo = (PATHTBL_P*)tag->pathtbl;
			PATHTBL_R* pro = (PATHTBL_R*)tag->pathtbl;
			s32 i;
			for (i = 0; i < copy->points; ++i) {
				switch (copy->pathtype) {
					case 0:
						*pc = *pco;
						reEntryPos(&pc->pos, pos, ang, scl, rot);
						++pc;
						++pco;
						break;
					case 1:
						*pp = *ppo;
						reEntryAng(&pp->slangx, &pp->slangz, ang, rot);
						reEntryPos(&pp->pos, pos, ang, scl, rot);
						++pp;
						++ppo;
						break;
					case 2:
						*pr = *pro;
						reEntryVec(&pr->n, ang, rot);
						reEntryPos(&pr->pos, pos, ang, scl, rot);
						++pr;
						++pro;
						break;
				}
			}
			pp             = (PATHTBL_P*)table;
			pr             = (PATHTBL_R*)table;
			copy->totallen = 0.0f;
			for (i = 0; i < copy->points - 1; ++i) {
				switch (copy->pathtype) {
					case 1:
						reEntryLen(&pp->length, &pp->pos, &(pp + 1)->pos);
						copy->totallen += pp->length;
						++pp;
						break;
					case 2:
						reEntryLen(&pr->length, &pr->pos, &(pr + 1)->pos);
						copy->totallen += pr->length;
						++pr;
						break;
				}
			}
			path = new CLASS_PATH(copy->pathtask);
			if (path) {
				path->tagptr      = copy;
				path->useCopyData = 1;
				goto link_path;
			}
			return NULL;
		}
	link_path:
		if (pPath) {
			path->last        = pPath->last;
			pPath->last->next = path;
			pPath->last       = path;
		} else {
			pPath      = path;
			path->last = path;
		}
	}
	return path;
}

struct ScanTaskView {
	s16 mode, modeLast, smode, flag;
	u16 wtimer;
	u8 padA[2];
	sAngle ang;
	RwV3d pos, scl;
};
struct ScanResetView {
	u8 pad[0x18];
	s32 reset;
};
extern "C" {
extern ScanTaskView* lbl_802AD090[8];
extern ScanResetView lbl_8029C310;
extern TObject* lbl_8042C0FC;
void fn_8003E2E4(s32, s32, RwV3d*, s32);
f64 __frsqrte(f64);
}
char* CL_TObjPathManage = "TObjPathManage";

void TObjPathManage::Disp() { }

void TObjPathManage::Exec()
{
	CLASS_PATH* path = pPath;
	for (s32 player = 0; player < 8; ++player) {
		ScanTaskView* task = lbl_802AD090[player];
		if (task) {
			fn_8003E2E4(player, 1, &pos_pl_Last[player], 0);
			l_pl_Temp[player].p.x  = pos_pl_Last[player].x;
			l_pl_Temp[player].p.y  = pos_pl_Last[player].y;
			l_pl_Temp[player].p.z  = pos_pl_Last[player].z;
			diff_pl_Temp[player].x = task->pos.x - pos_pl_Last[player].x;
			diff_pl_Temp[player].y = task->pos.y - pos_pl_Last[player].y;
			diff_pl_Temp[player].z = task->pos.z - pos_pl_Last[player].z;
			f32 squared            = diff_pl_Temp[player].z * diff_pl_Temp[player].z
			    + (diff_pl_Temp[player].x * diff_pl_Temp[player].x
			        + diff_pl_Temp[player].y * diff_pl_Temp[player].y);
			if (squared >= 0.0625f) {
				f32 distance;
				if (squared > 0.0f) {
					f64 estimate = __frsqrte(squared);
					estimate     = 0.5 * estimate * (3.0 - (f64)squared * (estimate * estimate));
					estimate     = 0.5 * estimate * (3.0 - (f64)squared * (estimate * estimate));
					volatile f32 length = (f32)((f64)squared
					    * (0.5 * estimate * (3.0 - (f64)squared * (estimate * estimate))));
					distance            = length;
				} else {
					distance = squared;
				}
				dist_pl_Temp[player] = distance;
			} else
				dist_pl_Temp[player] = 0.0f;
			if (!(dist_pl_Temp[player] < 0.25f)) {
				fn_801990E0(&dir_pl_Temp[player], &diff_pl_Temp[player]);
				l_pl_Temp[player].v.x = dir_pl_Temp[player].x;
				l_pl_Temp[player].v.y = dir_pl_Temp[player].y;
				l_pl_Temp[player].v.z = dir_pl_Temp[player].z;
			}
		}
	}
	if (lbl_8029C310.reset) {
		while (path) {
			path->Reset();
			path = path->next;
		}
		path = pPath;
	}
	while (path) {
		path->Exec();
		path = path->next;
	}
}

s32 EndPath()
{
	if (lbl_8042C380) {
		lbl_8042C380->flags |= 1;
		lbl_8042C380 = NULL;
	}
	return 1;
}

inline void TObjPathManage::SetPath(PATHTAG** tags)
{
	PATHTAG* tag;
	PATHTAG** cursor = tags;
	CLASS_PATH* last = NULL;
	CLASS_PATH* path;
	pPath        = NULL;
	tagTblTopPtr = cursor;
	tag          = *cursor++;
	path         = NULL;
	while (tag) {
		if (tag->pathtask) {
			path = new CLASS_PATH(tag->pathtask);
			if (path) {
				if (!pPath)
					pPath = path;
				path->tagptr = tag;
				path->last   = last;
				path->next   = NULL;
				if (path->last)
					path->last->next = path;
				last = path;
			}
		}
		tag = *cursor++;
	}
	if (pPath)
		pPath->last = path;
}

inline TObjPathManage::TObjPathManage(PATHTAG** tags)
    : TObject(lbl_8042C0FC)
{
	*(char**)kind = CL_TObjPathManage;
	field1E       = sizeof(TObjPathManage);
	lbl_8042C380  = this;
	SetPath(tags);
}

inline void* TObject::operator new(unsigned long size)
{
	return lbl_8042C148->Malloc(size);
}

inline void TObject::operator delete(void* object)
{
	lbl_8042C148->Free(object);
}

s32 InitPath(PATHTAG** tags)
{
	return new TObjPathManage(tags) != NULL;
}

TObjPathManage::~TObjPathManage()
{
	lbl_8042C380     = NULL;
	CLASS_PATH* path = pPath;
	while (path) {
		CLASS_PATH* next = path->next;
		ReleasePath(path);
		path = next;
	}
}
