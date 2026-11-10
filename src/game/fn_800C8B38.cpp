// Draws one frame of the current screen: resets the screen state on first use, sets up the camera, runs the update (returning 2 when it asks to finish), renders the world and flips the raster.
extern "C" {
extern int lbl_803A6690[];
extern int lbl_8042AEB0;
extern int lbl_8042C460;
extern signed char lbl_8042C464;
void* GetCurrentCameraPointer__Fv();
void* GetCurrentWorldPointer__Fv();
void RsCameraShowRaster(void* cam);
void fn_8001D718();
int fn_800C7E34(int a);
void fn_800C85D4(int a);
void fn_80159754(void* w);
void fn_80177C50();
void fn_80194234(int a, int b);
void fn_8019CC00(void* cam);
void fn_8019CC28(void* cam);
void fn_8019CF28(void* cam, int* p, int n);

int fn_800C8B38(int a)
{
	int r = 0;
	if (lbl_8042C464 == 0) {
		lbl_8042C460 = 1;
		lbl_8042C464 = 1;
	}
	if (lbl_8042C460 != 0) {
		lbl_803A6690[1] = 0;
		lbl_8042C460    = 0;
	}
	fn_8019CF28(GetCurrentCameraPointer__Fv(), &lbl_8042AEB0, 3);
	fn_8019CC28(GetCurrentCameraPointer__Fv());
	fn_80194234(6, 1);
	fn_80194234(8, 1);
	if (fn_800C7E34(a) != 0) {
		r = 2;
	}
	fn_800C85D4(a);
	fn_80159754(GetCurrentWorldPointer__Fv());
	fn_80177C50();
	fn_8019CC00(GetCurrentCameraPointer__Fv());
	RsCameraShowRaster(GetCurrentCameraPointer__Fv());
	fn_8019CF28(GetCurrentCameraPointer__Fv(), &lbl_8042AEB0, 3);
	fn_8001D718();
	return r;
}
}
