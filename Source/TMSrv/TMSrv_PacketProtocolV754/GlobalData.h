// ---
// by ptr0x
// ---

#ifndef __GLOBAL_DATA_H__
#define __GLOBAL_DATA_H__

#include <Windows.h>
#include "../../Common/st_Base.h"

extern st_MountData mountBuffer[50];
extern st_ItemList ItemList[6500];

st_MountData *GetMountBuffer();

#endif // __GLOBAL_DATA_H__