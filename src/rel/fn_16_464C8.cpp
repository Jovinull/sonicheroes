typedef unsigned int u32;
struct RwFrame;
extern "C" {
void* fn_8013F484(RwFrame*);
void fn_8019EB10(RwFrame*, RwFrame* (*)(RwFrame*, void*), void*);
RwFrame* fn_16_464C8(RwFrame* frame, void* data);
}
RwFrame* fn_16_464C8(RwFrame* frame, void* data)
{
	void* h = *(void**)data;
	h       = fn_8013F484(frame);
	if (h == 0) {
		fn_8019EB10(frame, fn_16_464C8, data);
		return frame;
	}
	*(void**)data = h;
	return 0;
}
