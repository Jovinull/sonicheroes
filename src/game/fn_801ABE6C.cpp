// Calls fn_801AD5E8 and fn_801B1CCC, then returns 1.

extern "C" {
void fn_801AD5E8();
void fn_801B1CCC();

int fn_801ABE6C()
{
	fn_801AD5E8();
	fn_801B1CCC();
	return 1;
}
}
