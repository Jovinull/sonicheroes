typedef unsigned int u32;
extern "C" u32 fn_16_1748(u32 p);
extern "C" u32 fn_16_170C(u32* arg0)
{
	return (fn_16_1748(*arg0 + 0x18) & 0x1C0000) >> 18;
}
