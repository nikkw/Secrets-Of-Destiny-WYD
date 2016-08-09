//---
// Secrets Of Destiny TEAM
//---

#ifndef __DLL_MAIN_H__
#define __DLL_MAIN_H__

#include <stdio.h>
#include <time.h>
#include <iostream>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "functions.h"
#include "..\..\Source\Common\st_Base.h"
#include "pe_hook.h"

#define ptrdat 0x684BB0
#define color_addr 0x049099b

extern GuildInfos Guild;
void LoadHooks();

void PacketControl(PacketHeader* Header);

#endif