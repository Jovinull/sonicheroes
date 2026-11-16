struct V3 {
	int a[3];
};
struct R {
	V3 v;
	int w;
};
struct S40 {
	R r[4];
};
extern "C" void fn_16_13F1C(S40* dst, S40* src)
{
	dst->r[0].v = src->r[0].v;
	dst->r[0].w = src->r[0].w;
	dst->r[1].v = src->r[1].v;
	dst->r[1].w = src->r[1].w;
	dst->r[2].v = src->r[2].v;
	dst->r[2].w = src->r[2].w;
	dst->r[3].v = src->r[3].v;
	dst->r[3].w = src->r[3].w;
}
