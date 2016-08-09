// ---
// by ptr0x
// ---

#ifndef __PE_PATCH_H__
#define __PE_PATCH_H__

#include "../../Common/PE_Hook.h"
#include "../../Common/DefaultEncDecInfoV754.h"
#include "PacketEncDec.h"
#include "DLLMain.h"

#define MAX_PLAYER 1000

void PE_Patch();
void PATCH_SetEncDec();
void TranslateClassFiles();
void NKD_AddMessage();
void NKD_ReadMessage();
void NKD_AddAccount_CreateAccount();
void DoLimitofPlayers();

static void (*BASE_GetFirstKey)(char* source, char *dest) = (void (__cdecl*)(char*, char *)) 0x004082B0; // Lib: Basedef.obj Class : (null)

#endif // __PE_PATCH_H__