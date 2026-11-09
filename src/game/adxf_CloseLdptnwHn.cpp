// Closes the pending load-partition handle and resets its bookkeeping (handle, partition id -1, file number, flag).

extern "C" {
void ADXF_Close(void*);
extern int adxf_flno[];
extern int adxf_ldptnw_hn[];
extern int adxf_ldptnw_ptid[];
extern int lbl_8041D1AC[];

void adxf_CloseLdptnwHn(void)
{
	ADXF_Close((void*)adxf_ldptnw_hn[0]);
	adxf_ldptnw_hn[0]   = 0;
	adxf_ldptnw_ptid[0] = -1;
	adxf_flno[0]        = 0;
	lbl_8041D1AC[0]     = 0;
}
}
