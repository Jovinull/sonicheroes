// movieD's startup registration (a .ctors entry): fills the MoviePlay hook
// table with the module's five routines and registers its global object's
// destructor (fn_17_2738) with __register_global_object.

typedef void (*MoviePlayRoutine)(void);

typedef struct MoviePlayTable {
	MoviePlayRoutine fn0;
	MoviePlayRoutine fn1;
	MoviePlayRoutine fn2;
	MoviePlayRoutine fn3;
	MoviePlayRoutine fn4;
} MoviePlayTable;

extern "C" {
extern MoviePlayTable MoviePlay;
void fn_17_2738(void);
void fn_17_27E4(void);
void fn_17_282C(void);
void fn_17_2864(void);
void fn_17_288C(void);
void fn_17_292C(void);
extern unsigned char lbl_17_bss_14[];
extern unsigned char lbl_17_bss_20[];
void __register_global_object(void*, void*, void*);

void fn_17_2954(void)
{
	MoviePlay.fn0 = fn_17_292C;
	MoviePlay.fn1 = fn_17_288C;
	MoviePlay.fn2 = fn_17_2864;
	MoviePlay.fn3 = fn_17_282C;
	MoviePlay.fn4 = fn_17_27E4;
	__register_global_object(&lbl_17_bss_20[0], fn_17_2738, &lbl_17_bss_14[0]);
}
}

extern "C" __declspec(section ".ctors") MoviePlayRoutine const moviePlayRegisterCtorEntry
    = fn_17_2954;
