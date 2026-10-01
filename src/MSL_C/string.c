#include "types.h"

// MSL string.c, 0x801C39F0 to 0x801C3EBC. Built with -inline deferred, so the
// binary holds the functions in reverse source order: strstr, strtok, strchr,
// strncmp and strcmp at the front, strlen last.
// References: PrimeDecomp/prime extern/sdk/runtime/string.c (strchr, strncmp,
// strcmp), mariopartyrd/marioparty4 src/MSL_C.PPCEABI.bare.H/string.c (strstr);
// strtok was written from the original instructions. strcpy is compiled at
// optimization level 3, as the rest of the unit was before it grew.
// The Metrowerks source walks a pointer decremented by one and pre-incremented
// in the loop, the same idiom as mem.c, so the length counter starts at -1.

// The walking destination pointer is u8* rather than char*. Keeping it the
// same type as the parameter lets the compiler propagate the copy away, and
// the byte stores then come out through the parameter register instead of the
// walking one.

// The word at a time copy is only taken when both pointers share the low two
// bits. The zero byte test is the usual (w - 0x01010101) & 0x80808080.
#define ONES  0x01010101
#define HIGHS 0x80808080

typedef u8 char_map_t[32];
#define set_char_map(map, ch) map[(u8)(ch) >> 3] |= (1 << ((ch) & 7))
#define tst_char_map(map, ch) (map[(u8)(ch) >> 3] & (1 << ((ch) & 7)))

u32 strlen(const char* str)
{
	const char* p = str - 1;
	u32 len       = -1;
	do {
		len++;
	} while (*++p);
	return len;
}

#pragma optimization_level 3
char* strcpy(char* dst, const char* src)
{
	u8* p = (u8*)dst;
	u32 n;

	if (((u32)dst & 3) == ((u32)src & 3)) {
		u32 w;
		n = (u32)src & 3;
		if (n != 0) {
			if ((*p = *src) == 0)
				return dst;
			for (n = 3 - n; n != 0; n--)
				if ((*++p = *++src) == 0)
					return dst;
			++p;
			++src;
		}
		w = *(u32*)src;
		if (((w - ONES) & HIGHS) == 0) {
			p -= 4;
			do {
				*(u32*)(p += 4) = w;
				src += 4;
				w = *(u32*)src;
			} while (((w - ONES) & HIGHS) == 0);
			p += 4;
		}
	}

	if ((*p = *src) == 0)
		return dst;
	while ((*++p = *++src) != 0)
		;
	return dst;
}
#pragma optimization_level reset

char* strncpy(char* dst, const char* src, u32 n)
{
	const char* s = src - 1;
	u8* p         = (u8*)dst - 1;

	n++;
	while (--n) {
		if ((*++p = *++s) == 0) {
			while (--n)
				*++p = 0;
			return dst;
		}
	}
	return dst;
}

char* strcat(char* dst, const char* src)
{
	const char* s = src - 1;
	u8* p         = (u8*)dst - 1;

	while (*++p)
		;
	--p;
	while ((*++p = *++s) != 0)
		;
	return dst;
}

char* strncat(char* dst, const char* src, u32 n)
{
	const char* s = src - 1;
	u8* p         = (u8*)dst - 1;

	while (*++p)
		;
	--p;
	n++;
	while (--n) {
		if ((*++p = *++s) == 0) {
			--p;
			break;
		}
	}
	p[1] = 0;
	return dst;
}

int strcmp(const char* str1, const char* str2)
{
	unsigned char* left  = (unsigned char*)str1;
	unsigned char* right = (unsigned char*)str2;
	unsigned int k1, k2, align, l1, r1, x;

	l1 = *left;
	r1 = *right;
	if (l1 - r1) {
		return l1 - r1;
	}

	if ((align = ((int)left & 3)) != ((int)right & 3)) {
		goto bytecopy;
	}
	if (align) {
		if (l1 == 0) {
			return 0;
		}
		for (align = 3 - align; align; align--) {
			l1 = *(++left);
			r1 = *(++right);
			if (l1 - r1) {
				return l1 - r1;
			}
			if (l1 == 0) {
				return 0;
			}
		}
		left++;
		right++;
	}

	k1 = 0x80808080;
	k2 = 0xfefefeff;

	l1 = *(int*)left;
	r1 = *(int*)right;
	x  = l1 + k2;
	if (x & k1) {
		goto adjust;
	}
	while (l1 == r1) {
		l1 = *(++((int*)(left)));
		r1 = *(++((int*)(right)));
		x  = l1 + k2;
		if (x & k1) {
			goto adjust;
		}
	}

	if (l1 > r1) {
		return 1;
	}

	return -1;

adjust:
	l1 = *left;
	r1 = *right;
	if (l1 - r1) {
		return l1 - r1;
	}

bytecopy:
	if (l1 == 0) {
		return 0;
	}

	do {
		l1 = *(++left);
		r1 = *(++right);
		if (l1 - r1) {
			return l1 - r1;
		}
		if (l1 == 0) {
			return 0;
		}
	} while (1);
}

int strncmp(const char* str1, const char* str2, u32 n)
{
	const unsigned char* p1 = (unsigned char*)str1 - 1;
	const unsigned char* p2 = (unsigned char*)str2 - 1;
	unsigned long c1, c2;

	n++;

	while (--n) {
		if ((c1 = *++p1) != (c2 = *++p2)) {
			return (c1 - c2);
		} else if (!c1) {
			break;
		}
	}

	return 0;
}

char* strchr(const char* str, int chr)
{
	const unsigned char* p = (unsigned char*)str - 1;
	unsigned long c        = (chr & 0xff);
	unsigned long ch;

	while (ch = *++p) {
		if (ch == c)
			return ((char*)p);
	}

	return (c ? 0 : (char*)p);
}

char* strtok(char* str, const char* set)
{
	u8* p;
	u8* n;
	int c;
	static u8* empty   = (u8*)"";
	static u8* s       = (u8*)"";
	char_map_t set_map = { 0 };

	if (str)
		s = (u8*)str;

	p = (u8*)set - 1;
	while (c = *++p)
		set_char_map(set_map, c);

	p = s - 1;
	while (c = *++p)
		if (!tst_char_map(set_map, c))
			break;

	if (!c) {
		s = empty;
		return NULL;
	}

	n = p;

	while (c = *++p)
		if (tst_char_map(set_map, c))
			break;

	if (!c) {
		s = empty;
		return (char*)n;
	}

	s  = p + 1;
	*p = 0;

	return (char*)n;
}

char* strstr(const char* str, const char* pat)
{
	const unsigned char* s1 = (const unsigned char*)str - 1;
	const unsigned char* p1 = (const unsigned char*)pat - 1;
	unsigned long firstc, c1, c2;

	if ((pat == 0) || (!(firstc = *++p1))) {
		return (char*)str;
	}

	while (c1 = *++s1) {
		if (c1 == firstc) {
			const unsigned char* s2 = s1 - 1;
			const unsigned char* p2 = p1 - 1;

			while ((c1 = *++s2) == (c2 = *++p2) && c1)
				;

			if (!c2)
				return (char*)s1;
		}
	}

	return NULL;
}

// __strerror has no body in the DOL: nothing links it, and the linker drops it
// with its switch table. Its messages survive because they share the string
// pool with strtok's "" at 0x8023CC80, so the function is written out here to
// reproduce that pool in order. The cases are alphabetical by errno name,
// which is the order of the surviving messages; the errno values are not
// visible in the binary and are only placeholders.
enum {
	ENOERR,
	E2BIG,
	EACCES,
	EAGAIN,
	EBADF,
	EBUSY,
	ECHILD,
	EDEADLK,
	EDOM,
	EEXIST,
	EFAULT,
	EFBIG,
	EFPOS,
	EILSEQ,
	EINTR,
	EINVAL,
	EIO,
	EISDIR,
	EMFILE,
	EMLINK,
	ENAMETOOLONG,
	ENFILE,
	ENODEV,
	ENOENT,
	ENOEXEC,
	ENOLCK,
	ENOMEM,
	ENOSPC,
	ENOSYS,
	ENOTDIR,
	ENOTEMPTY,
	ENOTTY,
	ENXIO,
	EPERM,
	EPIPE,
	ERANGE,
	EROFS,
	ESIGPARM,
	ESPIPE,
	ESRCH,
	EUNKNOWN,
	EXDEV
};

int sprintf(char* s, const char* format, ...);

char* __strerror(int errnum, char* str)
{
	switch (errnum) {
		case E2BIG:
			strcpy(str, "Argument list too long");
			break;
		case EACCES:
			strcpy(str, "Permission denied");
			break;
		case EAGAIN:
			strcpy(str, "Resource temporarily unavailable");
			break;
		case EBADF:
			strcpy(str, "Bad file descriptor");
			break;
		case EBUSY:
			strcpy(str, "Device busy");
			break;
		case ECHILD:
			strcpy(str, "No child processes");
			break;
		case EDEADLK:
			strcpy(str, "Resource deadlock avoided");
			break;
		case EDOM:
			strcpy(str, "Numerical argument out of domain");
			break;
		case EEXIST:
			strcpy(str, "File exists");
			break;
		case EFAULT:
			strcpy(str, "Bad address");
			break;
		case EFBIG:
			strcpy(str, "File too large");
			break;
		case EFPOS:
			strcpy(str, "File Position Error");
			break;
		case EILSEQ:
			strcpy(str, "Wide character encoding error");
			break;
		case EINTR:
			strcpy(str, "Interrupted system call");
			break;
		case EINVAL:
			strcpy(str, "Invalid argument");
			break;
		case EIO:
			strcpy(str, "Input/output error");
			break;
		case EISDIR:
			strcpy(str, "Is a directory");
			break;
		case EMFILE:
			strcpy(str, "Too many open files");
			break;
		case EMLINK:
			strcpy(str, "Too many links");
			break;
		case ENAMETOOLONG:
			strcpy(str, "File name too long");
			break;
		case ENFILE:
			strcpy(str, "Too many open files in system");
			break;
		case ENODEV:
			strcpy(str, "Operation not supported by device");
			break;
		case ENOENT:
			strcpy(str, "No such file or directory");
			break;
		case ENOERR:
			strcpy(str, "No error detected");
			break;
		case ENOEXEC:
			strcpy(str, "Exec format error");
			break;
		case ENOLCK:
			strcpy(str, "No locks available");
			break;
		case ENOMEM:
			strcpy(str, "Cannot allocate memory");
			break;
		case ENOSPC:
			strcpy(str, "No space left on device");
			break;
		case ENOSYS:
			strcpy(str, "Function not implemented");
			break;
		case ENOTDIR:
			strcpy(str, "Not a directory");
			break;
		case ENOTEMPTY:
			strcpy(str, "Directory not empty");
			break;
		case ENOTTY:
			strcpy(str, "Inappropriate ioctl for device");
			break;
		case ENXIO:
			strcpy(str, "Device not configured");
			break;
		case EPERM:
			strcpy(str, "Operation not permitted");
			break;
		case EPIPE:
			strcpy(str, "Broken pipe");
			break;
		case ERANGE:
			strcpy(str, "Result too large");
			break;
		case EROFS:
			strcpy(str, "Read-only file system");
			break;
		case ESIGPARM:
			strcpy(str, "Signal error");
			break;
		case ESPIPE:
			strcpy(str, "Illegal seek");
			break;
		case ESRCH:
			strcpy(str, "No such process");
			break;
		case EUNKNOWN:
			strcpy(str, "Unknown error");
			break;
		case EXDEV:
			strcpy(str, "Cross-device link");
			break;
		default:
			sprintf(str, "Unknown Error (%d)", errnum);
			break;
	}

	return str;
}
