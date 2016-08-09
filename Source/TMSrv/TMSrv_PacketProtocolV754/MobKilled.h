#ifndef __MOB_KILLED_H__
#define __MOB_KILLED_H__

#include <Windows.h>
#include "DLLMain.h"
#include "../NativeFunctions.h"

void HKD_MobKilled_DropGold(INT32 index, UINT32 gold);
void __stdcall HKD_MobKilled_EventDead(INT32 killed, INT32 killer);
void __stdcall HKD_MobKilled_ControlDropItem(INT32 clientid, st_Item* item);

#endif // __MOB_KILLED_H__