#ifndef _SOCKAPI_H_
#define _SOCKAPI_H_

//
// winsock api definitions
//
typedef int (WINAPI * WSAStartup_t)(
    WORD wVersionRequested,
    LPWSADATA lpWSAData
);

typedef SOCKET (WINAPI * WSASocketA_t)(
    int af,
    int type,
    int protocol,
    LPWSAPROTOCOL_INFOA lpProtocolInfo,
    GROUP g,
    DWORD dwFlags
);

typedef int (WINAPI * bind_t)(
    SOCKET s,
    const struct sockaddr * name,
    int namelen
);

typedef int (WINAPI * listen_t)(
    SOCKET s,
    int backlog
);

typedef SOCKET (WINAPI * accept_t)(
    SOCKET s,
    struct sockaddr * addr,
    int * addrlen
);

typedef PVOID (WINAPI *LoadLibraryA_t)(const char *libraryName);
typedef PVOID (WINAPI *CloseHandle_t)(HANDLE hObj);
typedef PVOID (WINAPI *WaitForSingleObject_t)(HANDLE hObj, DWORD ms);

typedef BOOL (WINAPI *CreateProcessA_t)(
    LPCSTR lpApplicationName,
    LPSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCSTR lpCurrentDirectory,
    LPSTARTUPINFOA lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
);

#endif /* _SOCKAPI_H_ */

