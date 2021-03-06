// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include<Windows.h>
#include "detours.h"
#include "dll.h"
#include <cstdio>
#include<stdlib.h>
#include<sstream>
#include<tchar.h>
#include<string.h>
#include<iostream>
#include <time.h>
#undef UNICODE
using namespace std;
std::stringstream ss;
#pragma warning(suppress : 4996)

HANDLE (WINAPI *pCreateFileW) (
	LPCWSTR                lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
) = CreateFileW ;


HANDLE	WINAPI MyCreateFileW(
	LPCWSTR                lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
)  ;

HANDLE	WINAPI MyCreateFileW(
	LPCWSTR                lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
)
{
	return INVALID_HANDLE_VALUE;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)pCreateFileW, MyCreateFileW);
		if (DetourTransactionCommit() == NO_ERROR)
		break;

    /*case DLL_THREAD_ATTACH:
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)pCreateFileW, MyCreateFileW);
		break;
    case DLL_THREAD_DETACH:
		DisableThreadLibraryCalls(hModule);
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)pCreateFileW, MyCreateFileW);
		break;*/

    case DLL_PROCESS_DETACH:
		DisableThreadLibraryCalls(hModule);
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)pCreateFileW, MyCreateFileW);
		break;
    }
	
    return TRUE;
}



