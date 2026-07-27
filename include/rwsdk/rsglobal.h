#ifndef RSGLOBAL_H
#define RSGLOBAL_H

struct RsGlobalStruct
{
	const char* lpWindowName;
	int windowWidth;
	int windowHeight;
	int field_C;
	int hasConfirmedExit;
	int* HWND;
	int field_18;
	int field_1C;
	int(*field_20)(int, int);
	int field_24;
	int field_28;
	int field_2C;
	int field_30;
	int field_34;
	int field_38;
	void* field_3C;
};

extern struct RsGlobalStruct RsGlobal;

#endif
