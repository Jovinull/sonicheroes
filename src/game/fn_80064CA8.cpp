#include "types.h"

// PARTICLE_MATERIAL::Detach() (CORROBORATED by PS2 metadata): deletes all instances (fn_80064DF4, 68 bytes like
// PS2 DeleteAllInstance), deletes the sprite, unlinks from the core's material chain and destroys the frame.
// Names are from PS2; the symbol keeps its address-based name.
#include "game/rw_engine.h"

struct PM;

struct SubC {
	u8 pad[4];
	void* f4;
};

struct Sub34 {
	u8 pad0[4];
	void* f4;
	u8 pad8[4];
	SubC* fC;
	void* f10;
};

struct PM {
	u8 pad0[8];
	s32 f8;
	u8 padC[0x30 - 0xC];
	void* f30;
	Sub34* f34;
	u8 pad38[0x44 - 0x38];
	PM* f44;
	PM* f48;
	void* f4C;
};

struct Mgr {
	u8 pad[0x28];
	PM* head;
};

extern "C" {
void fn_80064DF4(PM*);
void fn_80152220(SubC*, int);
void fn_801FD1F4(void*);
void fn_8019E480(void*);
void __dl__FPv(void*);
extern Mgr* lbl_8042C2E0;

void fn_80064CA8(PM* o)
{
	Sub34* p;
	PM* next;
	Mgr* m;

	fn_80064DF4(o);
	p = o->f34;
	if (p != NULL) {
		if (p != NULL) {
			if (p->f4 != NULL) {
				__dl__FPv(p->f4);
				p->f4 = NULL;
			}
			if (p->f10 != NULL) {
				lbl_8042C9A4->rwfree(p->f10);
				p->f10 = NULL;
			}
			if (p->fC != NULL) {
				if (p->fC->f4 != NULL) {
					fn_80152220(p->fC, 0);
				}
				fn_801FD1F4(p->fC);
				p->fC = NULL;
			}
			__dl__FPv(p);
		}
		o->f34 = NULL;
	}
	if (o->f8 != 0) {
		m = lbl_8042C2E0;
		if (o == m->head) {
			next = o->f48;
			if (next == NULL) {
				m->head = NULL;
			} else {
				next->f44 = NULL;
				m         = lbl_8042C2E0;
				m->head   = next;
			}
		} else {
			next = o->f48;
			if (next != NULL) {
				next->f44 = o->f44;
			}
			o->f44->f48 = next;
		}
		o->f44 = NULL;
		o->f48 = NULL;
		o->f8  = 0;
	}
	if (o->f30 != NULL) {
		fn_8019E480(o->f30);
		o->f30 = NULL;
	}
}
}
