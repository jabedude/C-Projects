#include <stdio.h>
#include <windows.h>

#include "common.h"
#include "pe.h"

typedef UINT (WINAPI * WinExec_t)(LPCSTR lpCmdLine, UINT uCmdShow);

SCFUNC void scMain(void)
{
    INLINE_STR(kernel32, "kernel32");
    INLINE_STR(winexec, "WinExec");
    INLINE_STR(calc, "calc");

    PVOID pKernel32 = scGetModuleBase(kernel32);
    WinExec_t pWinExec = (WinExec_t) scGetProcAddr(pKernel32, winexec);
    if (pWinExec != NULL)
        pWinExec(calc, 0);
}


int main(int argc, char* argv[])
{
    scMain();
    return 0;
}

