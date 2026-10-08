// Reconstructed miscs.cpp. The GameCube unit boundary is inferred from the
// correlated PS2 C++ source marker, function sequence, and shared math data.
// All eleven surviving bodies match. tools/fix_miscs_object.py reorders six
// compiler-generated scalar atoms; it never changes instructions. Remove that
// step when source/compiler choices reproduce the original constant order.
// Deferred depths and literal ownership were tested without a source-only fix.
// SetPos/SetColor are reconstruction helpers.
#include "game/miscs.h"

// GameCube vertex layout, independently checked against DrawLine_ accesses.
struct MiscsVertex {
	RwV3d pos, normal;
	RwRGBA color;
	f32 u, v;
	void SetColor(const RwRGBA& c)
	{
		u32 a, b, g;
		g           = c.green;
		b           = c.blue;
		a           = c.alpha;
		color.red   = c.red;
		color.green = g;
		color.blue  = b;
		color.alpha = a;
	}
	void SetPos(const RwV3d& p)
	{
		f32 z, y;
		y     = p.y;
		z     = p.z;
		pos.x = p.x;
		pos.y = y;
		pos.z = z;
	}
};
struct MiscsSegment {
	RwV3d origin, direction;
};

extern "C" {
MiscsVertex lbl_803A6FE0[2];
f32 lbl_803A7028[0x10000];
const RwRGBA lbl_8042E040 = { 255, 255, 255, 255 };
f64 __frsqrte(f64);
f64 __fabs(f64);
f64 sin(f64);
f64 atan2(f64, f64);
f32 fn_800D7044(const RwV3d*, const MiscsSegment*, RwV3d*);
void* fn_801B2934(MiscsVertex*, u32, void*, u32);
s32 fn_801B2C00(s32);
s32 fn_801B2A14();
}

static inline f32 Sqrt(f32 value)
{
	if (value > 0.0f) {
		f64 estimate        = __frsqrte(value);
		estimate            = 0.5 * estimate * (3.0 - estimate * estimate * value);
		estimate            = 0.5 * estimate * (3.0 - estimate * estimate * value);
		estimate            = 0.5 * estimate * (3.0 - estimate * estimate * value);
		volatile f32 result = (f32)(value * estimate);
		return result;
	}
	return value;
}

static inline s32 QuadraticEquation(f32 a, f32 b, f32 c, f32* x0, f32* x1)
{
	f32 d;
	if ((f32)__fabs(a) > 0.000123f) {
		b /= a;
		c /= a;
		if ((f32)__fabs(c) > 0.000123f) {
			b *= 0.5f;
			d = b * b - c;
			if (d > 0.0f) {
				if (b > 0.0f)
					b = -b - Sqrt(d);
				else
					b = -b + Sqrt(d);
				*x0 = b;
				*x1 = c / b;
				return 1;
			} else if (d < 0.0f)
				return 0;
			else {
				*x0 = *x1 = -b;
				return 1;
			}
		} else {
			*x0 = -b;
			*x1 = 0.0f;
			return 1;
		}
	} else if ((f32)__fabs(b) > 0.000123f) {
		*x0 = *x1 = -c / b;
		return 1;
	}
	return 0;
}

static inline s32 Yangle(f32 xp, f32 zp)
{
	return (s16)(u16)(-((s32)(10430.381f * (f32)atan2(zp, xp)) - 0x4000));
}

s32 GetYangle(f32 xp, f32 zp)
{
	return Yangle(xp, zp);
}

s32 CmpAngleRelative(s32 srcYAng, s32 dstYAng)
{
	return (s16)(u16)(dstYAng - srcYAng);
}

s32 SetPlayerYAngle(s32 yAng)
{
	return 0x4000 - yAng;
}

void DrawLine_(RwV3d* line, RwRGBA* lineColor)
{
	RwRGBA defaultLineColor = lbl_8042E040;
	if (lineColor == 0)
		lineColor = &defaultLineColor;
	lbl_803A6FE0[0].SetPos(line[0]);
	lbl_803A6FE0[1].SetPos(line[1]);
	lbl_803A6FE0[0].u = 0.0f;
	lbl_803A6FE0[0].v = 0.0f;
	lbl_803A6FE0[1].u = 0.0f;
	lbl_803A6FE0[1].v = 0.0f;
	lbl_803A6FE0[0].SetColor(*lineColor);
	lbl_803A6FE0[1].SetColor(*lineColor);
	if (fn_801B2934(lbl_803A6FE0, 2, 0, 2)) {
		fn_801B2C00(1);
		fn_801B2A14();
	}
}

void DrawSphere_(RwV3d* pos, f32 size) { }

s32 CalcV2(RwV3d* now, RwV3d* trg, f32 max_y, f32 grav, RwV3d* v0)
{
	f32 x0, x1, Vxz;
	v0->y = Sqrt(2.0f * grav * (max_y - now->y));
	if (QuadraticEquation(0.5f * -grav, v0->y, -(trg->y - now->y), &x0, &x1)) {
		grav = (x0 > x1) ? x0 : x1;
	} else
		return 0;
	if (0.0f == grav)
		return 0;
	Vxz      = Sqrt((trg->x - now->x) * (trg->x - now->x) + (trg->z - now->z) * (trg->z - now->z));
	s32 yang = Yangle(now->x - trg->x, now->z - trg->z);
	GetSclXZ(yang, -(Vxz / grav), &v0->x, &v0->z);
	return 1;
}

s32 CalcV2_Time(RwV3d* now, RwV3d* trg, f32 max_y, f32 grav, RwV3d* v0, s32* time)
{
	f32 x0, x1, Vxz;
	v0->y = Sqrt(2.0f * grav * (max_y - now->y));
	if (QuadraticEquation(0.5f * -grav, v0->y, -(trg->y - now->y), &x0, &x1)) {
		grav = (x0 > x1) ? x0 : x1;
	} else
		return 0;
	if (0.0f == grav)
		return 0;
	Vxz      = Sqrt((trg->x - now->x) * (trg->x - now->x) + (trg->z - now->z) * (trg->z - now->z));
	s32 yang = Yangle(now->x - trg->x, now->z - trg->z);
	GetSclXZ(yang, -(Vxz / grav), &v0->x, &v0->z);
	*time = (s32)grav;
	return 1;
}

s32 CalcV2_TimeGP(
    RwV3d* now, RwV3d* trg, f32 max_y, f32 grav, RwV3d* v0, RwV3d* v0p, s32* yAng, s32* time)
{
	f32 x0, x1, Vxz;
	v0->y = Sqrt(2.0f * grav * (max_y - now->y));
	if (QuadraticEquation(0.5f * -grav, v0->y, -(trg->y - now->y), &x0, &x1)) {
		grav = (x0 > x1) ? x0 : x1;
	} else
		return 0;
	if (0.0f == grav)
		return 0;
	Vxz = Sqrt((trg->x - now->x) * (trg->x - now->x) + (trg->z - now->z) * (trg->z - now->z));
	Vxz /= grav;
	*yAng = Yangle(now->x - trg->x, now->z - trg->z);
	GetSclXZ(*yAng, -Vxz, &v0->x, &v0->z);
	v0p->x = Vxz;
	v0p->y = v0->y;
	v0p->z = 0.0f;
	*time  = (s32)grav;
	return 1;
}

void GetSclXZ(s32 angle, f32 scale, f32* sine, f32* cosine)
{
	*sine   = scale * lbl_803A7028[(u16)angle];
	*cosine = scale * lbl_803A7028[(u16)(angle + 0x4000)];
}

f32 DistanceP2SegL(RwV3d* point, RwV3d* first, RwV3d* second, RwV3d* closest)
{
	f32 x;
	f32 directionX;
	f32 y;
	f32 z;
	f32 directionY;
	f32 directionZ;
	f32 firstX;
	f32 firstY;
	f32 firstZ;
	f32 pointX;
	f32 secondX;
	f32 pointY;
	f32 secondY;
	f32 pointZ;
	f32 secondZ;

	pointX     = point->x;
	firstX     = first->x;
	x          = pointX - firstX;
	pointY     = point->y;
	firstY     = first->y;
	y          = pointY - firstY;
	pointZ     = point->z;
	firstZ     = first->z;
	z          = pointZ - firstZ;
	secondX    = second->x;
	directionX = secondX - firstX;
	secondY    = second->y;
	directionY = secondY - firstY;
	secondZ    = second->z;
	directionZ = secondZ - firstZ;

	if (x * directionX + y * directionY + z * directionZ < 0.0f) {
		f32 distanceSquared;
		if (closest != 0) {
			closest->x = firstX;
			closest->y = first->y;
			closest->z = first->z;
		}
		distanceSquared = x * x + y * y + z * z;
		if (distanceSquared <= 0.025f) {
			return 0.0f;
		}
		return Sqrt(distanceSquared);
	}

	x = secondX - pointX;
	y = secondY - pointY;
	z = secondZ - pointZ;
	if (directionX * x + directionY * y + directionZ * z < 0.0f) {
		f32 distanceSquared;
		if (closest != 0) {
			closest->x = secondX;
			closest->y = second->y;
			closest->z = second->z;
		}
		distanceSquared = x * x + y * y + z * z;
		if (distanceSquared <= 0.025f) {
			return 0.0f;
		}
		return Sqrt(distanceSquared);
	}

	MiscsSegment segment;
	segment.origin.x    = firstX;
	segment.origin.y    = firstY;
	segment.origin.z    = firstZ;
	segment.direction.x = directionX;
	segment.direction.y = directionY;
	segment.direction.z = directionZ;
	return fn_800D7044(point, &segment, closest);
}

void njInitSinTable()
{
	u32 angle;
	f32* output = lbl_803A7028;
	u32 index   = 0;
	angle       = 0;
	for (; index < 0x10000; index++) {
		*output = (f32)sin(3.141592f * angle / 65536.0f);
		output++;
		angle += 2;
	}
}
