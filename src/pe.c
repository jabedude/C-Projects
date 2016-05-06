#include <intrin.h>
#include <windows.h>

#include "common.h"
#include "pe.h"

SCFUNC PVOID scGetModuleBase(const char *moduleName)
{
    PPEB pPeb;
    PLIST_ENTRY head, entry;
    PLDR_DATA_TABLE_ENTRY module;

#if defined(_M_IX86)
    pPeb = (PPEB) __readfsdword(0x30);
#elif defined(_M_X64)
    pPeb = (PPEB) __readgsqword(0x60);
#endif

    head = &pPeb->Ldr->InLoadOrderModuleList;
    entry = head->Flink;

    while (entry != head)
    {
        module = CONTAINING_RECORD(entry, LDR_DATA_TABLE_ENTRY, InLoadOrderModuleList);
        if (scW2Anicmp(module->BaseDllName.Buffer, moduleName, scStrlen(moduleName)) == 0)
            return module->DllBase;
        entry = entry->Flink;
    }

    return NULL;
}

SCFUNC PVOID scGetProcAddr(PVOID modBase, const char *exportName)
{
    LPVOID pFunc = NULL;
    PBYTE pMod = (PBYTE)modBase;
    PIMAGE_NT_HEADERS pNt = GET_NT_HEADERS(pMod);
    PIMAGE_DATA_DIRECTORY pDir = &GET_DIRECTORY(pNt, IMAGE_DIRECTORY_ENTRY_EXPORT);
    PIMAGE_EXPORT_DIRECTORY pExportDir;
    WORD *pOrdinal;
    DWORD *pName;
    DWORD *pFuncs;
    DWORD i;

    // get the export directory
    pExportDir = (PIMAGE_EXPORT_DIRECTORY)(pMod + pDir->VirtualAddress);

    // sanity check the export directory
    if (pDir->Size == 0 || pExportDir->NumberOfFunctions == 0 || pExportDir->NumberOfNames == 0)
        return NULL;

    // iterate the exported names
    pName = (DWORD *) (pMod + pExportDir->AddressOfNames);
    pOrdinal = (WORD *) (pMod + pExportDir->AddressOfNameOrdinals);

    // hi EMET!
    pFuncs = (DWORD *) (pMod + pExportDir->AddressOfFunctions);

    for (i = 0; i < pExportDir->NumberOfNames; i++, pName++, pOrdinal++)
    {
        if (scStrcmp(exportName, (const char *)(pMod + *pName)) == 0)
        {
            // found the name, get the function
            pFunc =  pMod + pFuncs[*pOrdinal];
            break;
        }
    }

    return pFunc;
}

