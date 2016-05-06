#ifndef _PE_H_
#define _PE_H_

#define GET_NT_HEADERS(pBase)       (PIMAGE_NT_HEADERS)( ((PBYTE)(pBase)) + ((PIMAGE_DOS_HEADER)(pBase))->e_lfanew );
#define GET_DIRECTORY(pNt, idx)     (pNt->OptionalHeader.DataDirectory[(idx)])

// Internal structures defined here as the ones in winternl.h are very
// incomplete.
typedef struct _PEB_LDR_DATA
{
    DWORD dwLength;
    DWORD dwInitialized;
    LPVOID lpSsHandle;
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    LPVOID lpEntryInProgress;
}
PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct __PEB
{
    BYTE bInheritedAddressSpace;
    BYTE bReadImageFileExecOptions;
    BYTE bBeingDebugged;
    BYTE bSpareBool;
    LPVOID lpMutant;
    LPVOID lpImageBaseAddress;
    PPEB_LDR_DATA Ldr;
    // omitting what is below
}
PEB, *PPEB;

typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR Buffer;
}
UNICODE_STRING, *PUNICODE_STRING;

typedef struct _LDR_DATA_TABLE_ENTRY
{
    LIST_ENTRY InLoadOrderModuleList;
    LIST_ENTRY InMemoryOrderModuleList;
    LIST_ENTRY InInitializationOrderModuleList;
    PVOID DllBase;
    PVOID EntryPoint;
    ULONG SizeOfImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    ULONG Flags;
    SHORT LoadCount;
    SHORT TlsIndex;
    LIST_ENTRY HashTableEntry;
    ULONG TimeDateStamp;
}
LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;


// functions
extern PVOID scGetModuleBase(const char *moduleName);
extern PVOID scGetProcAddr(PVOID modBase, const char *exportName);

#endif /* _PE_H_ */
