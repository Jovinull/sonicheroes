// Runs one AHX decode step through the first entry of the AHX exec callback table. The table form
// (not a lone pointer) is needed: the original addresses it with lis/@l, not small data.

extern "C" {
extern void (*ahxexecfunc[])(void*);
void ADXB_ExecOneAhx(void* o)
{
	(*ahxexecfunc)(o);
}
}
