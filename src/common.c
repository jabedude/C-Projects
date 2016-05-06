#include "wchar.h"
#include "common.h"

// these little libc stubs borrowed from
// http://research.microsoft.com/en-us/um/redmond/projects/invisible/src/crt/strcmp.c.htm

SCFUNC int scW2Anicmp(const wchar_t *pStr1, const char *pStr2, size_t Count)
{
    wchar_t c1;
    char c2;
    int v;

    if (Count == 0)
        return 0;

    do {
        c1 = *pStr1++;
        c2 = *pStr2++;
        /* the casts are necessary when pStr1 is shorter & char is signed */
        v = (unsigned int) C_TOLOWER(c1) - (unsigned int) C_TOLOWER(c2);
    } while ((v == 0) && (c1 != '\0') && (--Count > 0));

    return v;
}

SCFUNC int scStrcmp(const char *pStr1, const char *pStr2)
{
    char c1, c2;
    int v;

    do {
        c1 = *pStr1++;
        c2 = *pStr2++;
        /* the casts are necessary when pStr1 is shorter & char is signed */
        v = (unsigned int)c1 - (unsigned int)c2;
    } while ((v == 0) && (c1 != '\0'));

    return v;
}

SCFUNC size_t scStrlen(const char *pStr)
{
    const char *pEnd;

    for (pEnd = pStr; *pEnd != '\0'; pEnd++)
        continue;

    return pEnd - pStr;
}

