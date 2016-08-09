#include "DLLMain.h"
#include <Rpc.h>
#include <ctime>
#pragma comment(lib, "Rpcrt4.lib")

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD catchReason, LPVOID lpResrv)
{
    switch (catchReason)
    {
	case DLL_PROCESS_ATTACH:

		PE_Patch();
		SetDefaultConstants();
		DoLimitofPlayers();
		break;

	case DLL_PROCESS_DETACH:
		FreeLibrary(hInstDLL);
		break;
    }

    return TRUE;
}