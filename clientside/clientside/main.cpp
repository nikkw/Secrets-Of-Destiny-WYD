//---
// Secrets Of Destiny TEAM
//---

#include "main.h"

GuildInfos Guild;

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD catchReason, LPVOID lpResrv)
{
    switch (catchReason)
    {
        case DLL_PROCESS_ATTACH:
		{
			//if(IsDebuggerPresent())
			  //  ExitProcess(1);

			memset(&Guild, 0, sizeof GuildInfos);

			LoadHooks();
			break;
		}
        case DLL_PROCESS_DETACH:
		{
			FreeLibrary(hInstDLL);
			break;
		}
    }
    return TRUE;
}