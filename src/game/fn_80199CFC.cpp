// Installs the default string functions in the engine globals (HYPOTHESIS: _rwStringOpen's
// function table set-up): the C library routines plus the local wrappers fn_80199CCC/fn_80199C98
// (character searches), fn_80199B80 (case-insensitive compare) and fn_80199C18/fn_80199C58 (case
// conversion). Always returns 1.
#include "game/rw_engine.h"

extern "C" {
s32 sprintf(char* buffer, const char* format, ...);
s32 vsprintf(char* buffer, const char* format, void* args);
char* strcpy(char* dst, const char* src);
char* strncpy(char* dst, const char* src, u32 size);
char* strcat(char* dst, const char* src);
char* strncat(char* dst, const char* src, u32 size);
char* strstr(const char* string, const char* search);
s32 strcmp(const char* lhs, const char* rhs);
s32 strncmp(const char* lhs, const char* rhs, u32 size);
u32 strlen(const char* string);
char* strtok(char* string, const char* delimiters);
s32 sscanf(const char* string, const char* format, ...);
char* fn_80199CCC(const char* string, s32 character);
char* fn_80199C98(const char* string, s32 character);
s32 fn_80199B80(const char* lhs, const char* rhs);
char* fn_80199C18(char* string);
char* fn_80199C58(char* string);

s32 fn_80199CFC(void)
{
	lbl_8042C9A4->rwsprintf  = sprintf;
	lbl_8042C9A4->rwvsprintf = vsprintf;
	lbl_8042C9A4->rwstrcpy   = strcpy;
	lbl_8042C9A4->rwstrncpy  = strncpy;
	lbl_8042C9A4->rwstrcat   = strcat;
	lbl_8042C9A4->rwstrncat  = strncat;
	lbl_8042C9A4->rwstrrchr  = fn_80199CCC;
	lbl_8042C9A4->rwstrchr   = fn_80199C98;
	lbl_8042C9A4->rwstrstr   = strstr;
	lbl_8042C9A4->rwstrcmp   = strcmp;
	lbl_8042C9A4->rwstrncmp  = strncmp;
	lbl_8042C9A4->rwstricmp  = fn_80199B80;
	lbl_8042C9A4->rwstrlen   = strlen;
	lbl_8042C9A4->rwstrupr   = fn_80199C18;
	lbl_8042C9A4->rwstrlwr   = fn_80199C58;
	lbl_8042C9A4->rwstrtok   = strtok;
	lbl_8042C9A4->rwsscanf   = sscanf;
	return 1;
}
}
