typedef int s32;
extern "C" {
void fn_16_DD80(s32 a, s32 b);
void fn_16_2B338(s32* arg0)
{
	fn_16_DD80(*arg0 + 0x18, 0x20000);
}
}
