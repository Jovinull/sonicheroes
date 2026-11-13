#include "types.h"

extern "C" {

typedef struct ADXB_OBJ {
	s16 used; /* 0x00 */
	unsigned char pad0[6];
	void* xpd; /* 0x08 */
	unsigned char pad1[0x2c];
	int f38; /* 0x38 */
	int f3c; /* 0x3c */
	int f40; /* 0x40 */
	int f44; /* 0x44 */
	unsigned char pad2[0x30];
	void (*f78)(); /* 0x78 */
	void* f7c;     /* 0x7c */
	void (*f80)(); /* 0x80 */
	void* f84;     /* 0x84 */
	unsigned char pad3[0x34];
	int fbc;                 /* 0xbc */
	unsigned char fc0[0x10]; /* 0xc0 */
	s16 d0;                  /* 0xd0 */
	s16 d2;                  /* 0xd2 */
	s16 d4;                  /* 0xd4 */
} ADXB_OBJ;

extern ADXB_OBJ adxb_obj[];
void* ADXPD_Create(void);
void ADXPD_Destroy(void*);
void* memset(void*, int, unsigned);
void adxb_DefGetWr();
void adxb_DefAddWr();

void* ADXB_Create(int a, int b, int c, int d)
{
	int i;
	void* t;
	ADXB_OBJ* o;

	for (i = 0; i < 16; i++) {
		if (adxb_obj[i].used == 0) {
			break;
		}
	}
	if (i == 16) {
		return NULL;
	}
	o = &adxb_obj[i];
	memset(o, 0, sizeof(ADXB_OBJ));
	o->used = 1;
	o->xpd  = ADXPD_Create();
	if (o->xpd == NULL) {
		if (o != NULL) {
			t      = o->xpd;
			o->xpd = NULL;
			ADXPD_Destroy(t);
			memset(o, 0, sizeof(ADXB_OBJ));
			o->used = 0;
		}
		return NULL;
	}
	o->f38 = a;
	o->f3c = b;
	o->f40 = c;
	o->f44 = d;
	o->f78 = adxb_DefGetWr;
	o->f7c = o;
	o->f80 = adxb_DefAddWr;
	o->f84 = o;
	o->fbc = 0;
	o->d0  = 0;
	o->d2  = -0x80;
	o->d4  = -0x80;
	memset(o->fc0, 0, 0x10);
	return o;
}
}
