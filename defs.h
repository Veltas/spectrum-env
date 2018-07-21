#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#if   defined __SDCC
#	define FAST_CALL __z88dk_fastcall
#endif

typedef unsigned char Byte;

enum {
	AssertType_audit = 0,
	AssertType_release
};

void AssertFail(
	const char *message,
	const char *filename,
	unsigned   line,
	Byte       type
);

#ifdef NAUDIT
#	define AuditAssert(cond)
#else
#	define AuditAssert(cond) {\
		if (!(cond)) {\
			AssertFail(#cond, __FILE__, __LINE__, AssertType_audit);\
		}\
	}
#endif

#define ReleaseAssert(cond, message) {\
	if (!(cond)) {\
		AssertFail(message, __FILE__, __LINE__, AssertType_release);\
	}\
}

#endif // DEFS_H_INCLUDED
