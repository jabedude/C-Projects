#ifndef _COMMON_H_
#define _COMMON_H_

#define SCFUNC __attribute__((section("sccode")))

// Macro to inline an ascii string
// unfortunately I don't have a nice way to do this with a wide
// character string w/o a custom preprocessor step
#define INLINE_STR(name, str) \
    const char * name;          \
    asm(                        \
        "call 1f\n"             \
        ".asciz \"" str "\"\n"  \
        "1:\n"                  \
        "pop %0\n"              \
        : "=r" (name)           \
    );


// tolower macro
#define C_TOLOWER(c) \
    ( ((c) >= 'A' && (c) <= 'Z') ? (((c) - 'A') + 'a') : (c) )

// stringification
#define xstr(x) str(s)
#define str(s) #s

// these little libc stubs borrowed from
// http://research.microsoft.com/en-us/um/redmond/projects/invisible/src/crt/strcmp.c.htm
extern int scW2Anicmp(const wchar_t *pStr1, const char *pStr2, size_t Count);
extern int scStrcmp(const char *pStr1, const char *pStr2);
extern size_t scStrlen(const char *pStr);

#endif /* _COMMON_H_ */

