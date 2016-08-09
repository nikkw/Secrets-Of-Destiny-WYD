// ---
// by ptr0x
// ---

#include "DLLMain.h"

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD catchReason, LPVOID lpResrv)
{
    switch (catchReason)
    {
	case DLL_PROCESS_ATTACH:

		CreateConsole();
		ReadPlugin();

		break;

	case DLL_PROCESS_DETACH:
		FreeLibrary(hInstDLL);
		break;
    }

    return TRUE;
}