struct V3i {
	int x;
	int y;
	int z;
};

extern "C" void fn_16_4E330(V3i* dst, V3i* a, V3i* b)
{
	dst->x = a->x + b->x;
	dst->y = a->y + b->y;
	dst->z = a->z + b->z;
}
